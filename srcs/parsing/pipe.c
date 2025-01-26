/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:07:43 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/26 04:37:06 by anoteris         ###   ########.fr       */
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

static void	shift_up_cmd_args(t_cmd *cmd)
{
	int	i ;

	i = 0 ;
	while (cmd->cmd_args[i + 1])
	{
		free(cmd->cmd_args[i]);
		cmd->cmd_args[i] = ft_strdup(cmd->cmd_args[i + 1]);
		i++ ;
	}
	free(cmd->cmd_args[i]);
	cmd->cmd_args[i] = NULL ;
}

static void	cmd_secure(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd && cmd->cmd_args == NULL)
		{
			cmd->cmd_args = malloc(sizeof(char *));
			cmd->cmd_args[0] = NULL;
		}
		else
		{
			while (cmd->cmd_args[0] && ft_strlen(cmd->cmd_args[0]) == 0)
				shift_up_cmd_args(cmd);
		}
		cmd = cmd->next_cmd ;
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
			&& !is_in_quotes(in_quotes))
		{
			if (!input[i + 1])
				i++;
			add_cmd(&input, &i, &cmd, mini);
		}
		else
			i++;
	}
	cmd_secure(cmd_lstfirst(cmd));
	return (cmd);
}
