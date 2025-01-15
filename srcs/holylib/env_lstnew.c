/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:13:59 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/15 10:55:50 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "holylib.h"

t_env	*env_lstnew(char *var)
{
	t_env	*env;
	long	equal_pos;

	if (!ft_strchr(var, '='))
		return (NULL);
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	equal_pos = ft_strchr(var, '=') - var;
	env->key = ft_substr(var, 0, equal_pos);
	env->val = ft_substr(var, equal_pos + 1, ft_strlen(var + equal_pos + 1));
	env->next = NULL;
	return (env);
}
