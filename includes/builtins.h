/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 03:14:28 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/17 00:38:07 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "libft.h"

# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>

# define BUFFER_SIZE 5000

// Utils

int		get_argc(char *argv[]);

// Builtins

void	echo(t_cmd *cmd);
void	cd(t_cmd *cmd, t_minishell *mini);
void	pwd(t_cmd *cmd);
void	export(t_cmd *cmd, t_minishell *mini);

#endif