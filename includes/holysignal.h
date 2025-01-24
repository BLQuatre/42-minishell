/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   holysignal.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 23:34:32 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/24 23:38:16 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOLYSIGNAL_H
# define HOLYSIGNAL_H

# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>

// extern volatile sig_atomic_t	g_signal;
bool	active_command(int whether);
void	handle_sigaction(void);

#endif