/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:23:22 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/20 07:57:14 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// Only handling errno 'ENOEXEC 8 Exec format error'
// as idk what else could make execve fail
// void	exec_error(t_args *arg, char **cmd_args, int *pid)
// {
// 	free_str_array(cmd_args);
// 	free(arg);
// 	free(pid);
// 	if (errno == ENOEXEC)
// 		exit(EXIT_NO_PERM);
// 	exit(EXIT_FAILURE);
// }

void	dup2_error(t_cmd *cmd, t_minishell *mini)
{
	perror("redirection error: cannot duplicate fd:");
	free_and_exit(cmd, mini, EXIT_FAILURE);
}

int	pipe_error(int fd_in)
{
	if (fd_in != -1)
		close(fd_in);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	return (get_empty_pipe_out());
}

int	fork_error(t_cmd *cmd, int fd[2], int fd_in)
{
	if (cmd->next_cmd)
		(close(fd[0]), close(fd[1]));
	if (fd_in != -1)
		close(fd_in);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	return (get_empty_pipe_out());
}
