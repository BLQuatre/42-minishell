/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:26:33 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/23 05:34:53 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// char	*parse_arg(char *input, int *len)
// {
// 	int		i;
// 	char	last_quote;

// 	i = 0;
// 	last_quote = 0;
// 	debug("ARG", RED, "Parsing arg: `%s`", input);
// 	while (input[i])
// 	{
// 		if (last_quote == 0 && (input[i] != ' '))
// 		{
// 			if (input[i] == '\'' || input[i] == '"')
// 			{
// 				last_quote = input[i];
// 				i++;
// 			}
// 			else
// 				last_quote = ' ';
// 		}
// 		while (input[i] && last_quote != 0 && input[i] != last_quote && input[i] != '>' && input[i] != '<')
// 		{
// 			printf("Value `%s`\n", input + i);
// 			i++;
// 		}
// 		if (input[i] == last_quote && input[i] != ' ')
// 			i++;
// 		if (input[i] && (input[i] == ' ' || input[i] == '>' || input[i] == '<'))
// 		{
// 			// if (ft_strncmp(input + i, "&&", 2) == 0
// 			// 	|| ft_strncmp(input + i, "||", 2) == 0)
// 			// 	i++;
// 			break ;
// 		}
// 	}
// 	(*len) += i;
// 	return (ft_substr(input, 0, i));
// }

char	*parse_arg(char *input, int *len)
{
	bool	in_quotes[2];
	int		i;

	debug("ARG", RED, "Parsing arg: `%s`", input);
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
