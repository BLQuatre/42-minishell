/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:17:07 by cauvray           #+#    #+#             */
/*   Updated: 2025/02/23 18:38:24 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	process_dollar(char **input, char *res, t_minishell *mini,
	bool in_quotes[2])
{
	(*input)++;
	if (!(**input))
	{
		*res = '$';
		return (1);
	}
	if ((**input) == '?')
		return (process_env_exit_code(input, res, mini->exit_code));
	if (!in_quotes[D_QUOTE] && ((**input) == '\'' || (**input) == '"'))
		return (0);
	if (!is_valid_env_char(**input))
	{
		*res = '$';
		return (1);
	}
	return (proccess_env_var(input, res, mini->env));
}

char	*parse_env(char *input, t_minishell *mini)
{
	bool	in_quotes[2];
	char	*res;
	int		i;

	ft_bzero(&in_quotes, sizeof(bool) * 2);
	res = ft_calloc((get_buffer_size_env(input, mini) + 1), sizeof(char));
	i = 0;
	while (*input)
	{
		check_quotes(in_quotes, *input);
		if (*input == '$' && !in_quotes[S_QUOTE])
			i += process_dollar(&input, res + i, mini, in_quotes);
		else
			res[i++] = *(input++);
	}
	return (res);
}

void	handle_env(t_cmd *cmd, t_minishell *mini)
{
	int		i;
	char	*tmp;
	t_redir	*tmp_redir;

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
	tmp_redir = cmd->redirs;
	while (tmp_redir)
	{
		tmp = tmp_redir->file;
		tmp_redir->file = parse_env(tmp, mini);
		free(tmp);
		tmp_redir = tmp_redir->next;
	}
}
