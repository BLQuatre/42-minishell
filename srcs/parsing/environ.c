/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:17:07 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/24 05:14:07 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	get_buffer_size_env(char *input, t_minishell *mini)
{
	int		size;
	int		env_len;
	char	*env_key;
	t_env	*finded_env;

	size = 0;
	while (*input)
	{
		if (*input && *input == '"')
			input++;
		else if (*input && *input == '$')
		{
			input++;
			env_len = 0;
			if (*input && *input == '?')
			{
				size += ft_intlen(mini->exit_code);
				continue ;
			}
			if (!(*input) || (*input && !ft_isalnum(*input) && *input != '_'))
			{
				size++;
				continue ;
			}
			while (input[env_len] && ft_isalnum(input[env_len]))
				env_len++;
			env_key = ft_substr(input, 0, env_len);
			// if (DEBUG) debug("ENV", BRIGHT_MAGENTA, "Find key : %s", env_key);
			finded_env = env_lstget_by_key(mini->env, env_key);
			free(env_key);
			if (finded_env)
				size += ft_strlen(finded_env->val); // if (DEBUG) debug("ENV", BRIGHT_MAGENTA, "Find key value : %s (Size: %d)", finded_env->val, ft_strlen(finded_env->val));
			input += env_len;
		}
		else
		{
			input++;
			size++;
		}
	}
	return (size);
}

static char	*parse_env(char *input, t_minishell *mini)
{
	int		input_i;
	int		str_i;
	int		len;
	char	*str;
	char	*env_key;
	t_env	*finded_env;
	bool	in_quotes[2];

	if (DEBUG) debug("ENV", BRIGHT_RED, "Parsing env in: `%s`", input);
	ft_bzero(&in_quotes, sizeof(bool) * 2);
	str = ft_calloc((get_buffer_size_env(input, mini) + 1), sizeof(char));
	input_i = 0;
	str_i = 0;
	while (input[input_i])
	{
		check_quotes(&in_quotes, input[input_i]);
		if (input[input_i] && input[input_i] == '$' && !in_quotes[S_QUOTE])
		{
			len = 1;
			if (input[input_i + len] && input[input_i + len] == '?')
			{
				env_key = ft_itoa(mini->exit_code);
				ft_memcpy(str + str_i, env_key, ft_strlen(env_key));
				str_i += ft_strlen(env_key);
				input_i += len + 1;
				continue ;
			}
			if (!input[input_i + len] || (input[input_i + len] && !ft_isalnum(input[input_i + len]) && input[input_i + len] != '_'))
			{
				str[str_i++] = input[input_i++];
				continue ;
			}
			while (input[input_i + len] && (ft_isalnum(input[input_i + len]) || input[input_i + len] == '_'))
				len++;
			env_key = ft_substr(input + input_i + 1, 0, len - 1);
			if (DEBUG) debug("ENV", BRIGHT_MAGENTA, "Find key : `%s`", env_key);
			finded_env = env_lstget_by_key(mini->env, env_key);
			free(env_key);
			if (finded_env)
			{
				if (DEBUG) debug("ENV", BRIGHT_MAGENTA, "Find key value : `%s` (Size: %d)", finded_env->val, ft_strlen(finded_env->val));
				ft_memcpy(str + str_i, finded_env->val, ft_strlen(finded_env->val));
				str_i += ft_strlen(finded_env->val);
			}
			input_i += len;
		}
		else
			str[str_i++] = input[input_i++];
	}
	return (str);
}

void	handle_env(t_cmd *cmd, t_minishell *mini)
{
	int		i;
	char	*tmp;

	if (!cmd)
		return ;
	while (cmd)
	{
		if (cmd->cmd_args)
		{
			i = -1;
			while (cmd->cmd_args[++i])
			{
				tmp = cmd->cmd_args[i];
				cmd->cmd_args[i] = parse_env(cmd->cmd_args[i], mini);
				free(tmp);
			}
		}
		cmd = cmd->next_cmd;
	}
}
