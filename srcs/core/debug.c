/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:46:08 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/15 03:47:50 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	show_cmd(t_cmd *cmd)
{
	int	i;
	printf("t_cmd: (%p)\n{\n", cmd);
	printf("\tredirs: SOON\n");
	if (cmd->cmd_args)
	{
		printf("\tcmd_args: (%p) {", cmd->cmd_args);
		i = -1;
		while (cmd->cmd_args[++i])
			printf("\t\tcmd_args[%d]: `%s`\n", i, cmd->cmd_args[i]);
		printf("\t}\n");
	}
	else
		printf("\tcmd_args: (nil)\n");

	printf("\texit_code: `%d`\n", cmd->exit_code);
	printf("\tnext_cmd: `%p`\n", cmd->prev_cmd);
	printf("\tprev_cmd: `%p`\n}\n", cmd->next_cmd);
}
