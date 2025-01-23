/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:12:08 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/23 05:39:39 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	check_quotes(bool (*in_quotes)[2], char curr_chr)
{
	if (curr_chr == '\'' && !(*in_quotes)[D_QUOTE])
		(*in_quotes)[S_QUOTE] = !(*in_quotes)[S_QUOTE];
	if (curr_chr == '"' && !(*in_quotes)[S_QUOTE])
		(*in_quotes)[D_QUOTE] = !(*in_quotes)[D_QUOTE];
}

bool	is_in_quotes(bool in_quotes[2])
{
	return (in_quotes[S_QUOTE] || in_quotes[D_QUOTE]);
}

static int	count_useless_quotes(char *input)
{
	bool	in_quotes[2];
	int		count;

	ft_bzero(&in_quotes, sizeof(bool) * 2);
	count = 0;
	while (*input)
	{
		check_quotes(&in_quotes, *input);
		if ((*input == '"' && !in_quotes[S_QUOTE]) || (*input == '\'' && !in_quotes[D_QUOTE]))
			count++;
		input++;
	}
	return (count);
}

static char	*remove_quotes(char *input)
{
	bool	in_quotes[2];
	char	*str;
	int		str_i;

	ft_bzero(&in_quotes, sizeof(bool) * 2);
	str = malloc((ft_strlen(input) - count_useless_quotes(input) + 1) * sizeof(char));
	str_i = 0;
	while (*input)
	{
		check_quotes(&in_quotes, *input);
		if ((*input == '"' && !in_quotes[S_QUOTE]) || (*input == '\'' && !in_quotes[D_QUOTE]))
			input++;
		else
		{
			str[str_i++] = *input++;
		}
	}
	str[str_i] = '\0';
	return (str);
}

void	handle_quotes(t_cmd *cmd)
{
	int		i;

	cmd = cmd_lstfirst(cmd);
	while (cmd)
	{
		i = -1;
		while (cmd->cmd_args[++i])
			cmd->cmd_args[i] = remove_quotes(cmd->cmd_args[i]);
		cmd = cmd->next_cmd;
	}
}
