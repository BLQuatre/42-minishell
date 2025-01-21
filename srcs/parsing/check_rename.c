/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rename.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 05:17:23 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/21 16:24:07 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	is_valid_parentheses(char *input)
{
	int		i;
	int		count;
	bool	in_quotes[2];

	i = -1;
	count = 0;
	ft_bzero(in_quotes, sizeof(bool) * 2);
	while (input[++i])
	{
		if (input[i] == '\'' && !in_quotes[D_QUOTE])
			in_quotes[S_QUOTE] = !in_quotes[S_QUOTE];
		if (input[i] == '"' && !in_quotes[S_QUOTE])
			in_quotes[D_QUOTE] = !in_quotes[D_QUOTE];
		if (input[i] == '(' && !in_quotes[S_QUOTE] && !in_quotes[D_QUOTE])
			count++;
		if (input[i] == ')' && !in_quotes[S_QUOTE] && !in_quotes[D_QUOTE])
			count--;
		if (count < 0)
			break ;
	}
	return (count);
}

static bool	is_valid_quote(char *input, t_quote_type quote_type)
{
	int		i;
	bool	in_quotes[2];

	i = -1;
	ft_bzero(in_quotes, sizeof(bool) * 2);
	while (input[++i])
	{
		if (input[i] == '\'' && !in_quotes[D_QUOTE])
			in_quotes[S_QUOTE] = !in_quotes[S_QUOTE];
		if (input[i] == '"' && !in_quotes[S_QUOTE])
			in_quotes[D_QUOTE] = !in_quotes[D_QUOTE];
	}
	return (!in_quotes[quote_type]);
}

bool	is_valid_input(char *input)
{
	int	parentheses_result;

	parentheses_result = is_valid_parentheses(input);
	if (parentheses_result > 0)
		return (printf(INVALID_TOKEN, "unexpected token \"(\""), false);
	else if (parentheses_result < 0)
		return (printf(INVALID_TOKEN, "unexpected token \")\""), false);
	if (!is_valid_quote(input, S_QUOTE))
		return (printf(INVALID_TOKEN, "unexpected token \"'\""), false);
	if (!is_valid_quote(input, D_QUOTE))
		return (printf(INVALID_TOKEN, "unexpected token '\"'"), false);
	return (true);
}
