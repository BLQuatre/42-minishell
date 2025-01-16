/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   holylib.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:20:05 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/17 00:54:00 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOLYLIB_H
# define HOLYLIB_H

# include "minishell.h"
# include "libft.h"

# include <stdlib.h>

typedef struct s_minishell	t_minishell;
typedef struct s_env		t_env;
typedef struct s_cmd		t_cmd;
typedef enum redir_type		t_redir_type;
typedef struct s_redir		t_redir;

// ENV

t_env	*env_lstnew(char *var);
t_env	*env_lstlast(t_env *lst);
void	env_lstadd_back(t_env **lst, t_env *new);
t_env	*copy_env(void);
t_env	*env_lstget_by_key(t_env *lst, char *key);
void	env_lstdel_by_key(t_env **lst, char *key);
void	env_free(t_env *to_free);
void	env_free_lst(t_env *lst_to_free);

// CMD

t_cmd	*cmd_lstnew(void);
t_cmd	*cmd_lstfirst(t_cmd *lst);
t_cmd	*cmd_lstlast(t_cmd *lst);
void	cmd_lstadd_back(t_cmd **lst, t_cmd *new);
void	cmd_free(t_cmd *to_free);
void	cmd_free_lst(t_cmd *lst_to_free);

// REDIR

t_redir	*redir_lstnew(t_redir_type redir_type, char *file);
t_redir	*redir_lstlast(t_redir *lst);
void	redir_lstadd_back(t_redir **lst, t_redir *new);
void	redir_free(t_redir *to_free);
void	redir_free_lst(t_redir *lst_to_free);

#endif
