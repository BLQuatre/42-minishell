/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigaction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 06:11:36 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/24 07:21:25 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

volatile sig_atomic_t	g_signal = 0;

static void sig_handler(int _)
{
	(void) _;
	write(1, "\n", 1);
	if (g_signal == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_sigaction()
{
	// struct sigaction	sa;

	// sa.sa_flags = 0;
	// sa.sa_handler = sigaction_handler;
	// sigemptyset(&sa.sa_mask);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
	// if (sigaction(SIGINT, &sa, NULL) == -1) {
	// 	perror("Error setting up SIGINT handler");
	// 	exit(EXIT_FAILURE);
	// }
}
