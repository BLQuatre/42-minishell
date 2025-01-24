/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 22:30:18 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/24 22:31:58 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	proccess_env_var(char *dest, char *input, t_env *env)
{
	char	*env_key;
	t_env	*found_env;
	int		env_value_len;

	env_key = ft_substr(input + 1, 0, get_env_len(input) - 1);
	found_env = env_lstget_by_key(env, env_key);
	free(env_key);
	if (!found_env)
		return (0);
	env_value_len = ft_strlen(found_env->val);
	ft_memcpy(dest, found_env->val, env_value_len);
	return (env_value_len);
}

/**
 * @param str the adress of the char to start copy the exit code
 */
int	process_env_exit_code(char *dest, int exit_code)
{
	char	*exit_code_str;
	int		exit_core_len;

	exit_code_str = ft_itoa(exit_code);
	exit_core_len = ft_strlen(exit_code_str);
	ft_memcpy(dest, exit_code_str, exit_core_len);
	free(exit_code_str);
	return (exit_core_len);
}
