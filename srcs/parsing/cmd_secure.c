/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_secure.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 05:27:12 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/26 05:27:37 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	shift_up_cmd_args(t_cmd *cmd)
{
	int	i ;

	i = 0 ;
	while (cmd->cmd_args[i + 1])
	{
		free(cmd->cmd_args[i]);
		cmd->cmd_args[i] = ft_strdup(cmd->cmd_args[i + 1]);
		i++ ;
	}
	free(cmd->cmd_args[i]);
	cmd->cmd_args[i] = NULL ;
}

void	cmd_secure(t_cmd *cmd)
{
	if (cmd && cmd->cmd_args == NULL)
	{
		cmd->cmd_args = malloc(sizeof(char *));
		cmd->cmd_args[0] = NULL;
	}
	else
	{
		while (cmd->cmd_args[0] && ft_strlen(cmd->cmd_args[0]) == 0)
			shift_up_cmd_args(cmd);
	}
}
