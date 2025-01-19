/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_to_str_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 21:08:03 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/19 18:30:48 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "holylib.h"

char	**env_lst_to_str_array(t_env *env)
{
	char	**res ;
	int		i ;
	size_t	key_len ;
	size_t	val_len ;

	res = malloc((env_lst_get_nb(env) + 1) * sizeof(char *));
	i = 0 ;
	while (env)
	{
		key_len = ft_strlen(env->key);
		val_len = ft_strlen(env->val);
		res[i] = malloc((key_len + 1 + val_len + 1) * sizeof(char));
		ft_strlcpy(res[i], env->key, key_len + 1);
		ft_strlcat(res[i], "=", key_len + 2);
		ft_strlcat(res[i], env->val, key_len + 1 + val_len + 1);
		i++ ;
		env = env->next ;
	}
	res[i] = NULL ;
	return (res);
}
