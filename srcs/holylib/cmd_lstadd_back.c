/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:49:59 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/17 00:44:09 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "holylib.h"

void	cmd_lstadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last ;

	if (!lst)
		return ;
	if (!*lst)
		*lst = new ;
	else
	{
		last = cmd_lstlast(*lst);
		last->next_cmd = new ;
		new->prev_cmd = last ;
	}
}
