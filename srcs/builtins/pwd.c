/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 04:17:12 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/23 22:45:03 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	pwd(t_cmd *cmd)
{
	char	buf[BUFFER_SIZE];

	ft_bzero(buf, BUFFER_SIZE);
	if (!getcwd(buf, BUFFER_SIZE))
	{
		perror("pwd");
		cmd->exit_code = 1 ;
		return ;
	}
	ft_putstr_fd(buf, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}
