/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:46:08 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/23 19:48:04 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

const char *colors[] = {
	"\033[30m",
	"\033[31m",
	"\033[32m",
	"\033[33m",
	"\033[34m",
	"\033[35m",
	"\033[36m",
	"\033[37m",
	"\033[90m",
	"\033[91m",
	"\033[92m",
	"\033[93m",
	"\033[94m",
	"\033[95m",
	"\033[96m",
	"\033[97m"
};

const char *redirs_type[] = {
	"<",
	"<<",
	">",
	">>"
};

void	debug(const char *tag, t_color color, const char *format, ...)
{
	char	buffer[1024];
	va_list	args;
	va_start(args, format);
	vsnprintf(buffer, sizeof(buffer), format, args);
	dprintf(2, "%s[DEBUG / %5.5s] \033[0m%s\n", colors[color], tag, buffer);
	va_end(args);
}

void	show_cmd(t_cmd *cmd)
{
	int	i;

	debug("CMD", GREEN, "t_cmd: (%p)", cmd);
	if (!cmd)
		return ;
	debug("CMD", GREEN, "{");
	if (cmd->redirs)
	{
		debug("CMD", GREEN, "\tredirs: (%p)\n\t{", cmd->redirs);
		while (cmd->redirs)
		{
			debug("CMD", GREEN, "\t\tredirs: `%s %s`", redirs_type[cmd->redirs->type], cmd->redirs->file);
			cmd->redirs = cmd->redirs->next;

		}
		debug("CMD", GREEN, "\t}");
	}
	else
		debug("CMD", GREEN, "\tredirs: (nil)");

	if (cmd->cmd_args)
	{
		debug("CMD", GREEN, "\tcmd_args: (%p)", cmd->cmd_args);
		debug("CMD", GREEN, "\t{");
		i = -1;
		while (cmd->cmd_args[++i])
			debug("CMD", GREEN, "\t\tcmd_args[%d]: `%s`", i, cmd->cmd_args[i]);
		debug("CMD", GREEN, "\t}");
	}
	else
		debug("CMD", GREEN, "\tcmd_args: (nil)");

	debug("CMD", GREEN, "\texit_code: `%d`", cmd->exit_code);
	debug("CMD", GREEN, "\tnext_cmd: `%p`", cmd->next_cmd);
	debug("CMD", GREEN, "\tprev_cmd: `%p`", cmd->prev_cmd);
	debug("CMD", GREEN, "}");

	if (cmd->next_cmd)
		show_cmd(cmd->next_cmd);
}
