/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_lstlast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:57:19 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/15 00:58:03 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "holylib.h"

t_redir	*redir_lstlast(t_redir *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
