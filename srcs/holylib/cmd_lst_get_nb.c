/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst_get_nb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:15:12 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/18 11:21:01 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "holylib.h"

int	cmd_lst_get_nb(t_cmd *cmd)
{
	int	i ;

	i = 0 ;
	while (cmd)
	{
		i++ ;
		cmd = cmd->next_cmd ;
	}
	return (i);
}
