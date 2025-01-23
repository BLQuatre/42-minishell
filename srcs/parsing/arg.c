/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:26:33 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/23 21:29:31 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*parse_arg(char *input, int *len)
{
	bool	in_quotes[2];
	int		i;

	if (DEBUG) debug("ARG", RED, "Parsing arg: `%s`", input);
	ft_bzero(&in_quotes, sizeof(bool) * 2);
	i = 0;
	while (input[i])
	{
		check_quotes(&in_quotes, input[i]);
		if (in_quotes[S_QUOTE] || in_quotes[D_QUOTE])
		{
			i++;
			continue ;
		}
		if (input[i] == '>' || input[i] == '<' || input[i] == '|' || input[i] == ' ' || input[i] == '&')
		{
			if (i == 0)
				i++;
			break ;
		}
		i++;
	}
	(*len) += i;
	return (ft_substr(input, 0, i));
}
