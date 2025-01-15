/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lstdel_by_key.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:00:40 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/15 12:11:07 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "holylib.h"

void	env_lstdel_by_key(t_env **lst, char *key)
{
	t_env	*cur ;
	t_env	*nxt ;

	if (!lst || !*lst)
		return ;
	cur = *lst ;
	if (ft_strcmp(cur->key, key) == 0)
	{
		*lst = cur->next ;
		return (env_free(cur));
	}
	nxt = cur->next ;
	while (nxt)
	{
		if (ft_strcmp(nxt->key, key) == 0)
		{
			cur->next = nxt->next ;
			return (env_free(nxt));
		}
		cur = nxt ;
		nxt = cur->next ;
	}
}
