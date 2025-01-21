/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 22:05:37 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/21 17:21:37 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	builtin_exec(t_cmd *cmd, t_minishell *mini)
{
	if (ft_strcmp(cmd->cmd_args[0], "echo") == 0)
		echo(cmd);
	if (ft_strcmp(cmd->cmd_args[0], "cd") == 0)
		cd(cmd, mini);
	if (ft_strcmp(cmd->cmd_args[0], "pwd") == 0)
		pwd(cmd);
	if (ft_strcmp(cmd->cmd_args[0], "export") == 0)
		export(cmd, mini);
	if (ft_strcmp(cmd->cmd_args[0], "unset") == 0)
		unset(cmd, mini);
	if (ft_strcmp(cmd->cmd_args[0], "env") == 0)
		env(mini);
	if (ft_strcmp(cmd->cmd_args[0], "exit") == 0)
		my_exit(cmd, mini);
}

static void	alone_builtin_exec(t_cmd *cmd, t_minishell *mini)
{
	int	fd_save[2];

	fd_save[0] = dup(STDIN_FILENO);
	if (fd_save[0] == -1)
		return (dup_error(cmd, mini));
	fd_save[1] = dup(STDOUT_FILENO);
	if (fd_save[1] == -1)
		return (close(fd_save[0]), dup_error(cmd, mini));
	handle_fd(cmd, mini, NULL, -1);
	if (cmd->exit_code == 0)
		builtin_exec(cmd, mini);
	if (dup2(fd_save[0], STDIN_FILENO) == -1)
		return (close(fd_save[0]), close(fd_save[1]), dup2_error(cmd, mini));
	dup2(fd_save[1], STDOUT_FILENO);
		return (close(fd_save[1]), dup2_error(cmd, mini));
}

static void	child_exec(t_cmd *cmd, t_minishell *mini)
{
	if (is_builtin(cmd->cmd_args[0]))
	{
		builtin_exec(cmd, mini);
		exit(cmd->exit_code);
	}
	add_path_to_cmd(cmd, mini);
	if (!cmd->cmd_args)
	{
		if (errno == EACCES)
			free_and_exit(cmd, mini, EXIT_NO_PERM);
		free_and_exit(cmd, mini, EXIT_CMD_NOT_FOUND);
	}
	execve(cmd->cmd_args[0], cmd->cmd_args, env_lst_to_str_array(mini->env));
	if (errno == ENOEXEC)
		free_and_exit(cmd, mini, EXIT_NO_PERM);
	free_and_exit(cmd, mini, EXIT_FAILURE);
}

static int	recursive_pipex(t_cmd *cmd, t_minishell *mini, int *pid)
{
	static int	fd[2];
	int			fd_in;
	int			cmd_index;

	fd_in = -1 ;
	if (cmd->prev_cmd)
		fd_in = recursive_pipex(cmd->prev_cmd, mini, pid);

	if (cmd->next_cmd && pipe(fd) == -1)
		return (pipe_error(fd_in));
	cmd_index = cmd_lst_get_nb(cmd) - 1 ;
	if (IS_ALONE_BUILTIN)
		return (alone_builtin_exec(cmd, mini), 0);
	pid[cmd_index] = fork();
	if (pid[cmd_index] < 0)
		return (fork_error(cmd, fd, fd_in));
	if (pid[cmd_index] == 0)
	{
		/* CHILD */
		free(pid);
		handle_fd(cmd, mini, fd, fd_in);
		child_exec(cmd, mini);
	}
	if (fd_in != -1)
		close(fd_in);
	if (cmd->next_cmd)
		return (close(fd[1]), fd[0]);
	return (0);
}

int	exec(t_minishell *mini, t_cmd *cmd)
{
	pid_t	*pid ;
	t_cmd	*cur ;
	int		cmd_nb ;
	int		i;

	cmd_nb = cmd_lst_get_nb(cmd) ;
	pid = malloc((cmd_nb) * sizeof(pid_t));
	ft_memset(pid, -1, (cmd_nb) * sizeof(pid_t));

	recursive_pipex(cmd_lstlast(cmd), mini, pid);

	i = -1 ;
	cur = cmd ;
	while (++i < cmd_nb)
	{
		if (pid[i] != -1)
		{
			waitpid(pid[i], &cur->exit_code, 0);
			if (WIFEXITED(cur->exit_code))
				cur->exit_code = (WEXITSTATUS(cur->exit_code));
			else
				cur->exit_code = 1 ;
		}
		else if (!IS_ALONE_BUILTIN)
				cmd->exit_code = 1 ;
		cur = cur->next_cmd ;
	}
	free(pid);

	mini->exit_code = cmd_lstlast(cmd)->exit_code ;
	cmd_free_lst_from_start(cmd);
	return (mini->exit_code);
}
