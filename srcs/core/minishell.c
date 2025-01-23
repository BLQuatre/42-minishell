/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:56:12 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/23 19:49:35 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	main(int argc, char *argv[])
{
	char		*msg;
	t_minishell	*mini;

	mini = minishell_new();

	// FIXME: Remove when finished
	if (argc > 1)
	{
		while (--argc > 0)
			handle_input(argv[argc], mini);
		return (0);
	}
	// END FIXME

	while (true)
	{
		msg = readline(SHELL_PROMPT);
		if (msg == NULL)
		{
			// TODO: Change this to better
			printf("exit\n");
			break;
		}
		if (ft_strlen(msg) == 0)
			continue;
		add_history(msg);
		handle_input(msg, mini);
		free(msg);
	}
	return (0);
}
