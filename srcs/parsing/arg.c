/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:26:33 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/24 23:42:54 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// char	*parse_arg(char *input, int *len, bool *subshell)
// {
// 	bool	in_quotes[2];
// 	char	*arg;
// 	int		i;

// 	if (DEBUG) debug("ARG", RED, "Parsing arg: `%s`", input);
// 	ft_bzero(&in_quotes, sizeof(bool) * 2);
// 	i = 0;
// 	while (input[i])
// 	{
// 		check_quotes(&in_quotes, input[i]);
// 		if (in_quotes[S_QUOTE] || in_quotes[D_QUOTE])
// 		{
// 			i++;
// 			continue ;
// 		}
// 		if (input[i] == '(')
// 		{
// 			arg = parse_subshell(input, &i);
// 			(*len) += i;
// 			if (subshell)
// 				(*subshell) = true;
// 			return (arg);
// 		}
// 		if (input[i] == '>' || input[i] == '<' || input[i] == '|'
// 			|| input[i] == ' ' || input[i] == '&')
// 		{
// 			if (i == 0)
// 				i++;
// 			break ;
// 		}
// 		i++;
// 	}
// 	(*len) += i;
// 	arg = ft_substr(input, 0, i);
// 	return (arg);
// }

static bool	process_arg(char *input, bool in_quotes[2], int *i)
{
	if (in_quotes[S_QUOTE] || in_quotes[D_QUOTE])
	{
		(*i)++;
		return (false);
	}
	if (input[*i] == '>' || input[*i] == '<' || input[*i] == '|'
		|| input[*i] == ' ' || input[*i] == '&')
	{
		if (*i == 0)
			(*i)++;
		return (true);
	}
	return (false);
}

char	*parse_arg(char *input, int *len, bool *subshell)
{
	bool	in_quotes[2];
	char	*arg;
	int		i;

	ft_bzero(&in_quotes, sizeof(bool) * 2);
	i = 0;
	while (input[i])
	{
		check_quotes(&in_quotes, input[i]);
		if (process_arg(input, in_quotes, &i))
			break ;
		if (input[i] == '(')
		{
			arg = parse_subshell(input, &i);
			(*len) += i;
			if (subshell)
				*subshell = true;
			return (arg);
		}
		i++;
	}
	(*len) += i;
	arg = ft_substr(input, 0, i);
	return (arg);
}
