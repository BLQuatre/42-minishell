/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:56:12 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/25 04:21:09 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	main(int argc, char *argv[])
{
	char		*msg;
	t_minishell	*mini;

	handle_sigaction();
	rl_outstream = stderr ;
	mini = minishell_new();
	while (true)
	{
		msg = readline(SHELL_PROMPT);
		if (g_signal == SIGINT)
		{
			mini->exit_code = 130 ;
			g_signal = 0 ;
		}
		if (msg == NULL)
			(printf("exit\n"), free_and_exit(NULL, mini, mini->exit_code));
		if (ft_strlen(msg) == 0)
			continue ;
		add_history(msg);
		handle_input(msg, mini);
		free(msg);
	}
	return (0);
}
