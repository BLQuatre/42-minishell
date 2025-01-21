/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 22:05:37 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/21 04:01:16 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

extern char	**environ ;

static void	child_exec(t_cmd *cmd, t_minishell *mini)
{
	add_path_to_cmd(cmd);
	if (!cmd->cmd_args)
	{
		if (errno == EACCES)
			free_and_exit(cmd, mini, EXIT_NO_PERM);
		free_and_exit(cmd, mini, EXIT_CMD_NOT_FOUND);
	}
	execve(cmd->cmd_args[0], cmd->cmd_args, environ);
	// TODO: check that
	// exec_error(arg, cmd_args, pid);
}

static int	recursive_pipex(t_cmd *cmd, t_minishell *mini, int *pid)
{
	static int	fd[2];
	int			fd_in;
	int			cmd_index;

	cmd_index = cmd_lst_get_nb(cmd) - 1 ;
	fd_in = -1 ;
	if (cmd->prev_cmd)
		fd_in = recursive_pipex(cmd->prev_cmd, mini, pid);

	if (cmd->next_cmd && pipe(fd) == -1)
		return (pipe_error(fd_in));
	pid[cmd_index] = fork();
	if (pid[cmd_index] < 0)
		return (fork_error(cmd, fd, fd_in));
	if (pid[cmd_index] == 0)
	{
		/* CHILD */
		free(pid);
		child_fd(cmd, mini, fd, fd_in);
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
		waitpid(pid[i], &cur->exit_code, 0);
		if (WIFEXITED(cur->exit_code))
			cur->exit_code = (WEXITSTATUS(cur->exit_code));
		else
			cur->exit_code = 0 ;
		cur = cur->next_cmd ;
	}
	free(pid);

	mini->exit_code = cmd_lstlast(cmd)->exit_code ;
	cmd_free_lst_from_start(cmd);
	return (mini->exit_code);
}
