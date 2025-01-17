/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 05:55:54 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/17 07:08:05 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	my_exit(t_cmd *cmd, t_minishell *mini)
{
	int	exit_code ;

	if (!cmd->cmd_args[1])
	{
		exit_code = mini->exit_code ;
		minishell_free(mini);
		cmd_free_lst_from_start(cmd);
		exit(exit_code);
	}
	exit_code = ft_atoi(cmd->cmd_args[1]);
	if (exit_code < 0 || exit_code > 255)
		exit_code = 1 ;
	minishell_free(mini);
	cmd_free_lst_from_start(cmd);
	exit(exit_code);
}
