/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 01:26:57 by cauvray           #+#    #+#             */
/*   Updated: 2025/02/23 18:38:15 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	is_arg_after_redir(char *input)
{
	int		i;
	bool	in_quotes[2];

	i = -1;
	if (ft_strncmp(input, ">>", 2) == 0 || ft_strncmp(input, "<<", 2) == 0)
		i += 2;
	else
		i++;
	ft_bzero(in_quotes, sizeof(bool) * 2);
	while (input[++i])
	{
		check_quotes(in_quotes, input[i]);
		if (input[i] && (in_quotes[S_QUOTE] || in_quotes[D_QUOTE]))
			continue ;
		while (input[i] && input[i] == ' ')
			i++;
		if (input[i] != '|' && input[i] != '&'
			&& input[i] != '<' && input[i] != '>')
			return (true);
		return (false);
	}
	return (true);
}

bool	is_valid_redir(char *input)
{
	int		i;
	bool	in_quotes[2];

	i = -1;
	ft_bzero(in_quotes, sizeof(bool) * 2);
	while (input[++i])
	{
		check_quotes(in_quotes, input[i]);
		if (input[i] && (in_quotes[S_QUOTE] || in_quotes[D_QUOTE]))
			continue ;
		if (input[i] == '>' || input[i] == '<'
			|| ft_strncmp(input + i, ">>", 2) == 0
			|| ft_strncmp(input + i, "<<", 2) == 0)
		{
			if (!is_arg_after_redir(input + i))
				return (print_token_error(input[i]), false);
		}
	}
	return (true);
}
