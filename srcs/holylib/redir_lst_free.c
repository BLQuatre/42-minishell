/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_lst_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:03:56 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/15 12:05:37 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "holylib.h"

void	redir_free(t_redir *to_free)
{
	free(to_free->file);
	free(to_free);
}

void	redir_free_lst(t_redir *lst_to_free)
{
	t_redir	*nxt ;

	if (!lst_to_free)
		return ;
	nxt = lst_to_free->next ;
	while (nxt)
	{
		redir_free(lst_to_free);
		lst_to_free = nxt ;
		nxt = lst_to_free->next ;
	}
	redir_free(lst_to_free);
}
