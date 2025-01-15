/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lstget_by_key.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 08:49:59 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/15 08:59:13 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "holylib.h"

t_env	*env_lstget_by_key(t_env *lst, char *key)
{
	while (lst)
	{
		if (ft_strcmp(lst->key, key) == 0)
			return (lst);
		lst = lst->next ;
	}
	return (NULL);
}
