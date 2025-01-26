/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:07:43 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/26 05:42:58 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
	return (cmd);
}
