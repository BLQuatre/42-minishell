/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:16:50 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/21 17:21:15 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

// Includes

# include "minishell.h"
# include "builtins.h"
# include "libft.h"
# include "get_next_line.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>

// Defines explicit exit codes

# define EXIT_NO_PERM		126
# define EXIT_CMD_NOT_FOUND	127

// EXEC

int		exec(t_minishell *mini, t_cmd *cmd);

// FD

void	handle_fd(t_cmd *cmd, t_minishell *mini, int fd[2], int fd_in);
int		handle_redir(t_cmd *cmd, t_minishell *mini, int fd_cpy[2]);
int		read_here_doc(t_redir *redir);
void	restore_std_fd(int fd_cpy[2], t_cmd *cmd, t_minishell *mini);
int		get_empty_pipe_out(void);

// CMD

void	add_path_to_cmd(t_cmd *cmd, t_minishell *mini);
char	**get_all_paths(t_minishell *mini);
bool	check_perm(char *cmd, bool *found_cmd);

// ERROR

int		pipe_error(int fd_in);
void	dup_error(t_cmd *cmd, t_minishell *mini);
void	dup2_error(t_cmd *cmd, t_minishell *mini);
int		fork_error(t_cmd *cmd, int fd[2], int fd_in);

#endif