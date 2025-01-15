/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:08:55 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/15 03:57:14 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static bool	is_flag_n(char *flag)
{
	int	i ;

	if (!flag || flag[0] != '-')
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
			write(STDOUT_FILENO, cmd->cmd_args[i], ft_strlen(cmd->cmd_args[i]));
			if (cmd->cmd_args[i + 1])
				write(STDOUT_FILENO, " ", 1);
		}
	}
	if (!flag_n)
		write(STDOUT_FILENO, "\n", 1);
	cmd->exit_code = 0 ;
}
