/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:37:12 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/16 18:53:07 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "holylib.h"

# include <stdbool.h>

# define SHELL_PROMPT "\033[1;35mHolyShell > \033[0m"

typedef struct s_minishell
{
	struct s_env	*env;
	int				exit_code;
}	t_minishell;

typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	struct s_redir	*redirs;
	char			**cmd_args;
	bool			is_subshell;
	int				exit_code;
	struct s_cmd	*next_cmd;
	struct s_cmd	*prev_cmd;
}	t_cmd;

typedef enum redir_type
{
	IN,
	HERE_DOC,
	OUT_TRUNC,
	OUT_APP
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

#endif
