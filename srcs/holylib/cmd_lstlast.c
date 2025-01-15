/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lstlast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:50:19 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/15 00:50:57 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "holylib.h"

t_cmd	*cmd_lstlast(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next_cmd)
		lst = lst->next_cmd;
	return (lst);
}
