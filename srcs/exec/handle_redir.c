/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:15:44 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/20 06:24:06 by anoteris         ###   ########.fr       */
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

static void	handle_redir_in(t_redir *redir, t_cmd *cmd, t_minishell *mini,
	int fd_cpy[2])
{
	int	fd ;

	if (redir->type == IN)
		fd = open(redir->file, O_RDONLY);
	else
		fd = read_here_doc(redir);
	if (fd < 0)
	{
		perror(redir->file);
		(close(fd_cpy[0]), close(fd_cpy[1]));
		free_and_exit(cmd, mini, EXIT_FAILURE);
	}
	if (dup2(fd, fd_cpy[0]) == -1)
	{
		perror("redirection error: cannot duplicate fd:");
		(close(fd_cpy[0]), close(fd_cpy[1]));
		free_and_exit(cmd, mini, EXIT_FAILURE);
	}
	close(fd);
}

static void	handle_redir_out(t_redir *redir, t_cmd *cmd, t_minishell *mini,
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
		perror(redir->file);
		(close(fd_cpy[0]), close(fd_cpy[1]));
		free_and_exit(cmd, mini, EXIT_FAILURE);
	}
	if (dup2(fd, fd_cpy[1]) == -1)
	{
		perror("redirection error: cannot duplicate fd:");
		(close(fd_cpy[0]), close(fd_cpy[1]));
		free_and_exit(cmd, mini, EXIT_FAILURE);
	}
	close(fd);
}

void	handle_redir(t_cmd *cmd, t_minishell *mini, int fd_cpy[2])
{
	t_redir	*cur ;

	cur = cmd->redirs ;
	while (cur)
	{
		if (cur->type == IN || cur->type == HERE_DOC)
			handle_redir_in(cur, cmd, mini, fd_cpy);
		if (cur->type == OUT_TRUNC || cur->type == OUT_APP)
			handle_redir_out(cur, cmd, mini, fd_cpy);
		cur = cur->next ;
	}
}
