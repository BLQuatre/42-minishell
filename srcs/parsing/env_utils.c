/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:49:33 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/24 23:10:55 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_valid_env_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	get_env_len(char *input)
{
	int	len;

	len = 1;
	while (input[len] && (is_valid_env_char(input[len])))
		len++;
	return (len);
}

static int	process_env_size(char **input, t_minishell *mini, bool s_quote)
{
	int		env_len;
	char	*env_key;
	t_env	*found_env;
	int		size;

	env_len = 0;
	size = 0;
	if (s_quote)
	{
		while ((*input)[env_len] && is_valid_env_char((*input)[env_len]))
			env_len++;
		*input += env_len;
		return (env_len);
	}
	while ((*input)[env_len] && is_valid_env_char((*input)[env_len]))
		env_len++;
	env_key = ft_substr(*input, 0, env_len);
	found_env = env_lstget_by_key(mini->env, env_key);
	free(env_key);
	if (found_env)
		size += ft_strlen(found_env->val);
	*input += env_len;
	return (size);
}

static int	process_dollar(char **input, t_minishell *mini, bool in_squote)
{
	int	size;

	size = 0;
	if (!in_squote)
	{
		(*input)++;
		if (**input == '?')
		{
			size += ft_intlen(mini->exit_code);
			(*input)++;
		}
		else if (!(**input) || !is_valid_env_char(**input))
			size++;
		else
			size += process_env_size(input, mini, in_squote);
	}
	else
	{
		size++;
		(*input)++;
	}
	return (size);
}

int	get_buffer_size_env(char *input, t_minishell *mini)
{
	int		size;
	bool	in_quotes[2];

	size = 0;
	ft_bzero(&in_quotes, sizeof(bool) * 2);
	while (*input)
	{
		check_quotes(&in_quotes, *input);
		if (*input == '$')
			size += process_dollar(&input, mini, in_quotes[S_QUOTE]);
		else
		{
			size++;
			input++;
		}
	}
	return (size);
}
