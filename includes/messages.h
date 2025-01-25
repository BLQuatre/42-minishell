/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 07:34:59 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/25 05:37:10 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

# define SHELL_PROMPT "\033[1;35mHolyShell > \033[0m"

# define SIGQUIT_INIT_ERROR "Error setting up SIGQUIT handler"
# define SIGINT_INIT_ERROR "Error setting up SIGINT handler"

# define INVALID_TOKEN "😂 invalid token ! unexpected token%s\n"

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
