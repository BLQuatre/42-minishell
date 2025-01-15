/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:59:49 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/15 12:10:15 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "holylib.h"

extern char	**environ ;

t_env	*copy_env(void)
{
	t_env	*head ;
	int		i ;

	if (!environ)
		return (NULL);
	head = NULL ;
	i = -1 ;
	while (environ[++i])
		env_lstadd_back(&head, env_lstnew(environ[i]));
	return (head);
}
