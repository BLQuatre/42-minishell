/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:26:33 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/21 21:32:07 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*parse_arg(char *input, int *len)
{
	int		i;
	char	last_quote;

	i = 0;
	last_quote = 0;
	debug("PARSE", RED, "Parsing arg: `%s`", input);
	while (input[i])
	{
		if (last_quote == 0 && (input[i] != ' '))
		{
			if (input[i] == '\'' || input[i] == '"')
			{
				last_quote = input[i];
				i++;
			}
			else
				last_quote = ' ';
		}
		while (input[i] && last_quote != 0 && input[i] != last_quote)
			i++;
		if (input[i] == last_quote && input[i] != ' ')
			i++;
		if (input[i] && (input[i] == ' ' || input[i] == '>' || input[i] == '<'))
		{
			if (ft_strncmp(input + i, "&&", 2) == 0
				|| ft_strncmp(input + i, "||", 2) == 0)
				i++;
			break ;
		}
	}
	(*len) += i;
	return (ft_substr(input, 0, i));
}
