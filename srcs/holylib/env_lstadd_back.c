/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:18:56 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/15 00:51:18 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "holylib.h"

void	env_lstadd_back(t_env **lst, t_env *new)
{
	if (!lst)
		return ;
	if (!*lst)
		*lst = new ;
	else
		env_lstlast(*lst)->next = new ;
}
