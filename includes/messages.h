/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 07:34:59 by cauvray           #+#    #+#             */
/*   Updated: 2025/02/26 04:40:15 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

# define SHELL_PROMPT "\001\033[1;35m\002HolyShell > \001\033[0m\002"

# define SIGQUIT_INIT_ERROR "Error setting up SIGQUIT handler"
# define SIGINT_INIT_ERROR "Error setting up SIGINT handler"

# define INVALID_TOKEN "😂 invalid token ! unexpected token "
# define INVALID_TOKEN_QUOTE "`"

# define CD "cd: "
# define TOO_MANY_ARG "too many arguments\n"
# define NOT_SET " not set\n"
# define PWD "pwd"
# define EXPORT "export: `"
# define NOT_VALID_ID "': not a valid identifier\n"

# define CMD_NOT_FOUND ": command not found\n"
# define REDIR_ERROR "redirection error: "
# define DUP_FD "cannot duplicate fd:"
# define OPENDIR "opendir"
# define READDIR "readdir"
# define AMOGUS ": ambiguous redirect\n"

#endif
