/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   holylib.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:20:05 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/15 06:25:19 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOLYLIB_H
# define HOLYLIB_H

# include "minishell.h"
# include "libft.h"

# include <stdlib.h>

// ENV

t_env	*env_lstnew(char *var);
t_env	*env_lstlast(t_env *lst);
void	env_lstadd_back(t_env **lst, t_env *new);

// CMD

t_cmd	*cmd_lstnew(void);
t_cmd	*cmd_lstlast(t_cmd *lst);
void	cmd_lstadd_back(t_cmd **lst, t_cmd *new);

// REDIR

t_redir	*redir_lstnew(t_redir_type redir_type, char *file);
t_redir	*redir_lstlast(t_redir *lst);
void	redir_lstadd_back(t_redir **lst, t_redir *new);

#endif
