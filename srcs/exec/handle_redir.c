/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:15:44 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/21 10:16:27 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	read_here_doc(t_redir *redir)
{
	char	*line ;
	char	*limiter ;
	int		fd[2];

	if (pipe(fd) == -1)
		return (-1);
	limiter = ft_strjoin(redir->file, "\n");
	line = get_next_line(STDIN_FILENO);
	while (line && ft_strcmp(line, limiter))
	{
		ft_putstr_fd(line, fd[1]);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	free(limiter);
	close(fd[1]);
	return (fd[0]);
}

// Returns -1 on failure, indicating the need to exit
static int	handle_redir_in(t_redir *redir, t_cmd *cmd, t_minishell *mini,
	int fd_cpy[2])
{
	int	fd ;

	if (redir->type == IN)
		fd = open(redir->file, O_RDONLY);
	else
		fd = read_here_doc(redir);
	if (fd < 0)
	{
		(close(fd_cpy[0]), close(fd_cpy[1]));
		perror(redir->file);
		return (exit_from_child(cmd, mini, EXIT_FAILURE), -1);
	}
	if (dup2(fd, fd_cpy[0]) == -1)
	{
		(close(fd_cpy[0]), close(fd_cpy[1]));
		return (dup2_error(cmd, mini), -1);
	}
	close(fd);
	return (0);
}

// Returns -1 on failure, indicating the need to exit
static int	handle_redir_out(t_redir *redir, t_cmd *cmd, t_minishell *mini,
	int fd_cpy[2])
{
	int	fd ;
	int	flags ;

	flags = O_WRONLY | O_CREAT ;
	if (redir->type == OUT_TRUNC)
		flags = flags | O_TRUNC ;
	else
		flags = flags | O_APPEND ;
	fd = open(redir->file, flags, 0644);
	if (fd < 0)
	{
		(close(fd_cpy[0]), close(fd_cpy[1]));
		perror(redir->file);
		return (exit_from_child(cmd, mini, EXIT_FAILURE), -1);
	}
	if (dup2(fd, fd_cpy[1]) == -1)
	{
		(close(fd_cpy[0]), close(fd_cpy[1]), close(fd));
		return (dup2_error(cmd, mini), -1);
	}
	close(fd);
	return (0);
}

// Returns -1 on failure, indicating the need to exit
int	handle_redir(t_cmd *cmd, t_minishell *mini, int fd_cpy[2])
{
	t_redir	*cur ;

	cur = cmd->redirs ;
	while (cur)
	{
		if (cur->type == IN || cur->type == HERE_DOC)
			if (handle_redir_in(cur, cmd, mini, fd_cpy) == -1)
				return (-1);
		if (cur->type == OUT_TRUNC || cur->type == OUT_APP)
			if (handle_redir_out(cur, cmd, mini, fd_cpy) == -1)
				return (-1);
		cur = cur->next ;
	}
	return (0);
}
