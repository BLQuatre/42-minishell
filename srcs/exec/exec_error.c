/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:23:22 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/25 04:55:52 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ambiguous_redirect_error(t_cmd *cmd, t_minishell *mini, char *redir)
{
	while (ft_strchr(redir, - '*'))
		*ft_strchr(redir, - '*') = '*' ;
	ft_putstr_fd(redir, STDERR_FILENO);
	ft_putstr_fd(AMOGUS, STDERR_FILENO);
	free(redir);
	return (exit_from_child(cmd, mini, 1));
}

void	dup_error(t_cmd *cmd, t_minishell *mini)
{
	perror(DUP_FD);
	exit_from_child(cmd, mini, EXIT_FAILURE);
}

void	dup2_error(t_cmd *cmd, t_minishell *mini)
{
	ft_putstr_fd(REDIR_ERROR, STDERR_FILENO);
	perror(DUP_FD);
	exit_from_child(cmd, mini, EXIT_FAILURE);
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
