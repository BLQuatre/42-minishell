/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:07:43 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/24 02:05:05 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
		if (!in_quotes[S_QUOTE] && !in_quotes[D_QUOTE] && input[i] == '(')
			parentheses++;
		if (!in_quotes[S_QUOTE] && !in_quotes[D_QUOTE] && input[i] == ')')
			parentheses--;
		if ((input[i] == '|' || !input[i + 1]) && parentheses == 0
			&& !in_quotes[S_QUOTE] && !in_quotes[D_QUOTE])
		{
			if (!input[i + 1])
				i++;
			cmd_lstadd_back(&cmd, parse_cmd(ft_substr(input, 0, i), mini));
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
