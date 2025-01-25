/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 01:33:30 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/25 04:43:46 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_valid_quote(char *input, t_quote_type quote_type)
{
	int		i;
	bool	in_quotes[2];

	i = -1;
	ft_bzero(in_quotes, sizeof(bool) * 2);
	while (input[++i])
		check_quotes(&in_quotes, input[i]);
	if (in_quotes[quote_type])
	{
		if (quote_type == S_QUOTE)
			return (print_token_error('\''), false);
		if (quote_type == D_QUOTE)
			return (print_token_error('"'), false);
	}
	return (true);
}
