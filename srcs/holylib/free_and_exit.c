/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:44:55 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/23 08:38:30 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "holylib.h"

void	free_and_exit(t_cmd *cmd, t_minishell *mini, int exit_code)
{
	minishell_free(mini);
	cmd_free_lst_from_start(cmd);
	exit(exit_code);
}

// The sole purpose of this function is to be called by both child processes
// and alone builtins in a general way
void	exit_from_child(t_cmd *cmd, t_minishell *mini, int exit_code)
{
	if (IS_ALONE_BUILTIN)
		cmd->exit_code = exit_code ;
	else
		free_and_exit(cmd, mini, exit_code);
}
