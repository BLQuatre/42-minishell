/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:08:55 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/23 22:44:38 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static bool	is_flag_n(char *flag)
{
	int	i ;

	if (!flag || flag[0] != '-' || flag[1] != 'n')
		return (false);
	i = 0 ;
	while (flag[++i])
		if (flag[i] != 'n')
			return (false);
	return (true);
}

void	echo(t_cmd *cmd)
{
	bool	flag_n ;
	int		i ;

	flag_n = is_flag_n(cmd->cmd_args[1]);
	if (get_argc(cmd->cmd_args) > 1)
	{
		i = flag_n ;
		while (cmd->cmd_args[++i])
		{
			ft_putstr_fd(cmd->cmd_args[i], STDOUT_FILENO);
			if (cmd->cmd_args[i + 1])
				ft_putstr_fd(" ", STDOUT_FILENO);
		}
	}
	if (!flag_n)
		ft_putstr_fd("\n", STDOUT_FILENO);
	cmd->exit_code = 0 ;
}
