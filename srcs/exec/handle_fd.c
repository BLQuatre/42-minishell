/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 04:31:13 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/21 16:41:22 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// Returns -1 on dup2 failure, indicating the need to exit
static int	dup2_pipe(int fd[2], int fd_cpy[2], int fd_in)
{
	close(fd[0]);
	if (dup2(fd[1], fd_cpy[1]) == -1)
	{
		if (fd_in != -1)
			close(fd_in);
		(close(fd[1]), close(fd_cpy[0]), close(fd_cpy[1]));
		return (-1);
	}
	close(fd[1]);
	return (0);
}

// Returns -1 on dup2 failure, indicating the need to exit
static int	dup2_fd_in(int fd_cpy[2], int fd_in)
{
	if (dup2(fd_in, fd_cpy[0]) == -1)
	{
		(close(fd_in), close(fd_cpy[0]), close(fd_cpy[1]));
		return (-1);
	}
	close(fd_in);
	return (0);
}

void	handle_fd(t_cmd *cmd, t_minishell *mini, int fd[2], int fd_in)
{
	int	fd_cpy[2];

	fd_cpy[0] = dup(STDIN_FILENO);
	if (fd_cpy[0] == -1)
		return (dup_error(cmd, mini));
	fd_cpy[1] = dup(STDOUT_FILENO);
	if (fd_cpy[1] == -1)
		return (close(fd_cpy[0]), dup_error(cmd, mini));
	if (cmd->next_cmd)
		if (dup2_pipe(fd, fd_cpy, fd_in) == -1)
			return (dup2_error(cmd, mini));
	if (fd_in != -1)
		if (dup2_fd_in(fd_cpy, fd_in) == -1)
			return (dup2_error(cmd, mini));
	if (handle_redir(cmd, mini, fd_cpy) == -1)
		return ;
	restore_std_fd(fd_cpy, cmd, mini);
}
