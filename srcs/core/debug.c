/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:46:08 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/22 00:34:39 by cauvray          ###   ########.fr       */
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
	printf("%s[DEBUG / %5.5s] \033[0m%s\n", colors[color], tag, buffer);
	va_end(args);
}

void	show_cmd(t_cmd *cmd)
{
	int	i;

	printf("t_cmd: (%p)\n", cmd);
	if (!cmd)
		return ;
	printf("{\n");
	if (cmd->redirs)
	{
		printf("\tredirs: (%p)\n\t{\n", cmd->redirs);
		while (cmd->redirs)
		{
			printf("\t\tredirs: `%s %s`\n", redirs_type[cmd->redirs->type], cmd->redirs->file);
			cmd->redirs = cmd->redirs->next;

		}
		printf("\t}\n");
	}
	else
		printf("\tredirs: (nil)\n");

	if (cmd->cmd_args)
	{
		printf("\tcmd_args: (%p)\n\t{\n", cmd->cmd_args);
		i = -1;
		while (cmd->cmd_args[++i])
			printf("\t\tcmd_args[%d]: `%s`\n", i, cmd->cmd_args[i]);
		printf("\t}\n");
	}
	else
		printf("\tcmd_args: (nil)\n");

	printf("\texit_code: `%d`\n", cmd->exit_code);
	printf("\tnext_cmd: `%p`\n", cmd->next_cmd);
	printf("\tprev_cmd: `%p`\n}\n", cmd->prev_cmd);

	if (cmd->next_cmd)
		show_cmd(cmd->next_cmd);
}
