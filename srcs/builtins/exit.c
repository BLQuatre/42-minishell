/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 05:55:54 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/18 15:57:43 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	my_exit(t_cmd *cmd, t_minishell *mini)
{
	int	exit_code ;

	if (!cmd->cmd_args[1])
		exit_code = mini->exit_code ;
	else
	{
		exit_code = ft_atoi(cmd->cmd_args[1]);
		if (exit_code < 0 || exit_code > 255)
			exit_code = 1 ;
	}
	free_and_exit(cmd, mini, exit_code);
}
