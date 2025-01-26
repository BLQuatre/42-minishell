/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 22:30:18 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/26 00:49:52 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @param input must start by dollar
 */
int	proccess_env_var(char **input, char *res, t_env *env)
{
	char	*env_key;
	t_env	*found_env;
	int		env_value_len;

	env_key = ft_substr(*input, 0, get_env_len(*input));
	found_env = env_lstget_by_key(env, env_key);
	free(env_key);
	env_value_len = process_env_len(input, env, false);
	if (!found_env)
		return (0);
	ft_memcpy(res, found_env->val, env_value_len);
	return (env_value_len);
}

/**
 * @param input must start by dollar
 * @param str the adress of the char to start copy the exit code
 */
int	process_env_exit_code(char **input, char *res, int exit_code)
{
	char	*exit_code_str;
	int		exit_code_len;

	exit_code_str = ft_itoa(exit_code);
	exit_code_len = ft_strlen(exit_code_str);
	ft_memcpy(res, exit_code_str, exit_code_len);
	free(exit_code_str);
	(*input)++;
	return (exit_code_len);
}
