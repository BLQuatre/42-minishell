/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 06:11:36 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/25 01:13:57 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "holysignal.h"

volatile sig_atomic_t	g_signal = 0 ;

// Tells wether a cmd is active when calling with negative value passed as arg
// Modify returned value to arg when calling with positive value passed as arg
bool	active_command(int whether)
{
	static bool	active_cmd = 0;

	if (whether >= 0)
		active_cmd = whether;
	return (active_cmd);
}

static void sigint_handler(int signal)
{
	g_signal = signal ;
	write(STDERR_FILENO, "\n", 1);
	if (!active_command(-1))
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_sigaction(void)
{
	struct sigaction	sigquit_sa ;
	struct sigaction	sigint_sa ;

	sigquit_sa.sa_handler = SIG_IGN ;
	sigemptyset(&sigquit_sa.sa_mask);
	sigquit_sa.sa_flags = 0;
	if (sigaction(SIGQUIT, &sigquit_sa, NULL) == -1) {
		perror("Error setting up SIGQUIT handler");
		exit(EXIT_FAILURE);
	}
	sigint_sa.sa_handler = sigint_handler;
	sigemptyset(&sigint_sa.sa_mask);
	sigint_sa.sa_flags = 0;
	if (sigaction(SIGINT, &sigint_sa, NULL) == -1) {
		perror("Error setting up SIGINT handler");
		exit(EXIT_FAILURE);
	}
}
