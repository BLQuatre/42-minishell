/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 04:31:13 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/20 07:54:27 by anoteris         ###   ########.fr       */
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

void	child_fd(t_cmd *cmd, t_minishell *mini, int fd[2], int fd_in)
{
	int	fd_cpy[2];

	fd_cpy[0] = dup(STDIN_FILENO);
	fd_cpy[1] = dup(STDOUT_FILENO);
	if (cmd->next_cmd)
		if (dup2_pipe(fd, fd_cpy, fd_in) == -1)
			dup2_error(cmd, mini);
	if (fd_in != -1)
		if (dup2_fd_in(fd_cpy, fd_in) == -1)
			dup2_error(cmd, mini);
	handle_redir(cmd, mini, fd_cpy);
	restore_std_fd(fd_cpy, cmd, mini);
}

int	get_empty_pipe_out(void)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (-1);
	close(fd[1]);
	return (fd[0]);
}
