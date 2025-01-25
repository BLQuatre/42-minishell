/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 04:17:12 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/25 04:48:38 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	pwd(t_cmd *cmd)
{
	char	buf[BUFFER_SIZE];

	ft_bzero(buf, BUFFER_SIZE);
	if (!getcwd(buf, BUFFER_SIZE))
	{
		perror(PWD);
		cmd->exit_code = 1 ;
		return ;
	}
	ft_putstr_fd(buf, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}
