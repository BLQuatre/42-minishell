/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:20:57 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/15 09:33:25 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "holylib.h"

void	env_free(t_env *to_free)
{
	free(to_free->key);
	free(to_free->val);
	free(to_free);
}

void	env_free_lst(t_env *lst_to_free)
{
	t_env	*nxt ;

	if (!lst_to_free)
		return ;
	nxt = lst_to_free->next ;
	while (nxt)
	{
		env_free(lst_to_free);
		lst_to_free = nxt ;
		nxt = lst_to_free->next ;
	}
	env_free(lst_to_free);
}
