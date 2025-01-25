/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:07:43 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/25 23:23:18 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
t_cmd	*handle_pipe(char *input, t_minishell *mini)
{
	int		i;
	bool	in_quotes[2];
	int		parentheses;
	t_cmd	*cmd;
	char	*tmp;

	ft_bzero(&in_quotes, sizeof(bool) * 2);
	cmd = NULL;
	i = 0;
	parentheses = 0;
	while (input[i])
	{
		check_quotes(&in_quotes, input[i]);
		if (!in_quotes[S_QUOTE] && !in_quotes[D_QUOTE] && input[i] == '(')
			parentheses++;
		if (!in_quotes[S_QUOTE] && !in_quotes[D_QUOTE] && input[i] == ')')
			parentheses--;
		if ((input[i] == '|' || !input[i + 1]) && parentheses == 0
			&& !in_quotes[S_QUOTE] && !in_quotes[D_QUOTE])
		{
			if (!input[i + 1])
				i++;
			tmp = ft_substr(input, 0, i);
			cmd_lstadd_back(&cmd, parse_cmd(tmp, mini));
			free(tmp);
			if (input[i] == '|')
				i++;
			input += i;
			i = 0;
		}
		else
			i++;
	}
	if (cmd && cmd->cmd_args == NULL)
	{
		cmd->cmd_args = malloc(sizeof(char *));
		cmd->cmd_args[0] = NULL;
	}
	return (cmd);
}
*/

static int	calc_parentheses_depth(int actual_depth, bool in_quotes[2], char c)
{
	if (!in_quotes[S_QUOTE] && !in_quotes[D_QUOTE] && c == '(')
		actual_depth++;
	if (!in_quotes[S_QUOTE] && !in_quotes[D_QUOTE] && c == ')')
		actual_depth--;
	return (actual_depth);
}

static void	add_cmd(char **input, int *index, t_cmd **cmd, t_minishell *mini)
{
	char	*tmp;

	tmp = ft_substr(*input, 0, *index);
	cmd_lstadd_back(cmd, parse_cmd(tmp, mini));
	free(tmp);
	if ((*input)[*index] == '|')
		(*index)++;
	*input += *index;
	*index = 0;
}

static void	cmd_secure(t_cmd *cmd)
{
	if (cmd && cmd->cmd_args == NULL)
	{
		cmd->cmd_args = malloc(sizeof(char *));
		cmd->cmd_args[0] = NULL;
	}
}

t_cmd	*handle_pipe(char *input, t_minishell *mini)
{
	int		i;
	bool	in_quotes[2];
	int		parentheses;
	t_cmd	*cmd;

	ft_bzero(&in_quotes, sizeof(bool) * 2);
	cmd = NULL;
	i = 0;
	parentheses = 0;
	while (input[i])
	{
		check_quotes(&in_quotes, input[i]);
		parentheses = calc_parentheses_depth(parentheses, in_quotes, input[i]);
		if ((input[i] == '|' || !input[i + 1]) && parentheses == 0
			&& !in_quotes[S_QUOTE] && !in_quotes[D_QUOTE])
		{
			if (!input[i + 1])
				i++;
			add_cmd(&input, &i, &cmd, mini);
		}
		else
			i++;
	}
	cmd_secure(cmd);
	return (cmd);
}
