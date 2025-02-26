/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:49:33 by cauvray           #+#    #+#             */
/*   Updated: 2025/02/23 18:38:21 by cauvray          ###   ########.fr       */
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

	len = 0;
	while (input[len] && (is_valid_env_char(input[len])))
		len++;
	return (len);
}

/***
 * @param input name of env var without dollar
 */
int	process_env_len(char **input, t_env *env, bool s_quote)
{
	int		env_len;
	char	*env_key;
	t_env	*found_env;
	int		size;

	env_len = get_env_len(*input);
	if (s_quote)
		return (env_len);
	size = 0;
	env_key = ft_substr(*input, 0, env_len);
	found_env = env_lstget_by_key(env, env_key);
	free(env_key);
	if (found_env)
		size += ft_strlen(found_env->val);
	*input += env_len;
	return (size);
}

static int	process_dollar_len(char **input, t_minishell *mini,
	bool in_quotes[2])
{
	(*input)++;
	if (!(**input))
		return (1);
	if (**input == '?')
	{
		(*input)++;
		return (ft_intlen(mini->exit_code));
	}
	if (!in_quotes[D_QUOTE] && ((**input) == '\'' || (**input) == '"'))
		return (0);
	if (!is_valid_env_char(**input))
		return (1);
	return (process_env_len(input, mini->env, in_quotes[S_QUOTE]));
}

int	get_buffer_size_env(char *input, t_minishell *mini)
{
	int		size;
	bool	in_quotes[2];

	size = 0;
	ft_bzero(in_quotes, sizeof(bool) * 2);
	while (*input)
	{
		check_quotes(in_quotes, *input);
		if (*input == '$' && !in_quotes[S_QUOTE])
			size += process_dollar_len(&input, mini, in_quotes);
		else
		{
			size++;
			input++;
		}
	}
	return (size);
}
