/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:17:07 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/25 00:04:58 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// static int	get_buffer_size_env(char *input, t_minishell *mini)
// {
// 	int		size;
// 	int		env_len;
// 	char	*env_key;
// 	t_env	*found_env;

// 	size = 0;
// 	while (*input)
// 	{
// 		if (*input && *input == '"')
// 			input++;
// 		else if (*input && *input == '$')
// 		{
// 			input++;
// 			env_len = 0;
// 			if (*input && *input == '?')
// 			{
// 				size += ft_intlen(mini->exit_code);
// 				continue ;
// 			}
// 			if (!(*input) || (*input && !ft_isalnum(*input) && *input != '_'))
// 			{
// 				size++;
// 				continue ;
// 			}
// 			while (input[env_len] && ft_isalnum(input[env_len]))
// 				env_len++;
// 			env_key = ft_substr(input, 0, env_len);
// 			found_env = env_lstget_by_key(mini->env, env_key);
// 			free(env_key);
// 			if (found_env)
// 				size += ft_strlen(found_env->val);
// 			input += env_len;
// 		}
// 		else
// 		{
// 			input++;
// 			size++;
// 		}
// 	}
// 	return (size);
// }

/*
static char	*parse_env(char *input, t_minishell *mini)
{
	int		input_i;
	int		str_i;
	int		len;
	char	*str;
	char	*value;
	t_env	*found_env;
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
				value = ft_itoa(mini->exit_code);
				ft_memcpy(str + str_i, value, ft_strlen(value));
				str_i += ft_strlen(value);
				free(value);
				input_i += len + 1;
				continue ;
			}
			if (!input[input_i + len] || (input[input_i + len]
					&& !ft_isalnum(input[input_i + len])
					&& input[input_i + len] != '_'))
			{
				str[str_i++] = input[input_i++];
				continue ;
			}
			while (input[input_i + len] && (ft_isalnum(input[input_i + len])
					|| input[input_i + len] == '_'))
				len++;
			value = ft_substr(input + input_i + 1, 0, len - 1);
			found_env = env_lstget_by_key(mini->env, value);
			free(value);
			if (found_env)
			{
				ft_memcpy(str + str_i, found_env->val,
					ft_strlen(found_env->val));
				str_i += ft_strlen(found_env->val);
			}
			input_i += len;
		}
		else
			str[str_i++] = input[input_i++];
	}
	return (str);
}
*/

static void	handle_dollar(char *dest, int *dest_i, char *input, int *input_i, t_minishell *mini, bool s_quote)
{
	if (s_quote || !input[*input_i + 1] || (get_env_len(input + *input_i) == 1))
	{
		dest[(*dest_i)++] = input[(*input_i)++];
		return ;
	}
	if (input[*input_i + 1] == '?')
	{
		*dest_i += process_env_exit_code(dest + *dest_i, mini->exit_code);
		*input_i += 2;
		return ;
	}
	*dest_i += proccess_env_var(dest + *dest_i, input + *input_i, mini->env);
	*input_i += get_env_len(input + *input_i);
	return ;
}

char	*parse_env(char *input, t_minishell *mini)
{
	char	*dest;
	int		input_i;
	int		dest_i;
	bool	in_quotes[2];

	if (DEBUG) debug("ENV", BRIGHT_RED, "Parsing env in: `%s`", input);
	input_i = 0;
	dest_i = 0;
	ft_bzero(&in_quotes, sizeof(bool) * 2);
	// printf("aaa: %d\n", get_buffer_size_env(input, mini));
	dest = ft_calloc((get_buffer_size_env(input, mini) + 1), sizeof(char));
	while (input[input_i])
	{
		check_quotes(&in_quotes, input[input_i]);
		if (input[input_i] == '$')
			handle_dollar(dest, &dest_i, input, &input_i, mini, in_quotes[S_QUOTE]);
		else
			dest[dest_i++] = input[input_i++];
	}
	dest[dest_i] = '\0';
	return (dest);
}

void	handle_env(t_cmd *cmd, t_minishell *mini)
{
	int		i;
	char	*tmp;

	if (!cmd->cmd_args)
		return ;
	i = -1;
	while (cmd->cmd_args[++i])
	{
		tmp = cmd->cmd_args[i];
		cmd->cmd_args[i] = parse_env(cmd->cmd_args[i], mini);
		free(tmp);
	}
}
