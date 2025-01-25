/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parentheses.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 01:27:20 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/25 04:45:24 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_valid_parentheses(char *input)
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
	if (count > 0)
		return (print_token_error('('), false);
	if (count < 0)
		return (print_token_error(')'), false);
	return (true);
}
