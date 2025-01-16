/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lstfirst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 00:46:03 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/17 00:47:54 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "holylib.h"

t_cmd	*cmd_lstfirst(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->prev_cmd)
		lst = lst->prev_cmd ;
	return (lst);
}
