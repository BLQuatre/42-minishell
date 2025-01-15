/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_lstadd_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:58:14 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/15 00:58:30 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "holylib.h"

void	redir_lstadd_back(t_redir **lst, t_redir *new)
{
	if (!lst)
		return ;
	if (!*lst)
		*lst = new ;
	else
		redir_lstlast(*lst)->next = new ;
}
