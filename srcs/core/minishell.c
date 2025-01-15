/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:56:12 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/15 03:54:14 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "holylib.h"

int	main(void)
{
	char	*msg;

	// t_cmd	*cmd;
	// cmd = cmd_lstnew();
	// show_cmd(cmd);

	while (true)
	{
		msg = readline(SHELL_PROMPT);
		if (msg == NULL)
		{
			printf("exit\n");
			break;
		}
		printf("[DEBUG] readline: `%s`\n", msg);
		if (ft_strlen(msg) > 0)
			add_history(msg); // TODO: See if add before with newline and Ctrl+D
		free(msg);
	}
	return (0);
}
