/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:13:59 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/15 06:39:10 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "holylib.h"

t_env	*env_lstnew(char *var)
{
	t_env	*env;
	long	equal_pos;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	equal_pos = ft_strchr(var, '=') - var;
	env->key = ft_substr(var, 0, equal_pos);
	env->val = ft_substr(var, equal_pos + 1, ft_strlen(var + equal_pos + 1));
	env->next = NULL;
	return (env);
}
