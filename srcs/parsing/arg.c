/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:26:33 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/25 23:27:47 by cauvray          ###   ########.fr       */
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

// static bool	is_arg_end(char *input, int *i, bool in_quotes[2])
// {
// 	if (in_quotes[S_QUOTE] || in_quotes[D_QUOTE])
// 		return (false);
// 	if (input[*i] == '>' || input[*i] == '<' || input[*i] == '|'
// 		|| input[*i] == ' ' || input[*i] == '&')
// 	{
// 		if (*i == 0)
// 			(*i)++;
// 		return (true);
// 	}
// 	return (false);
// }

static bool	is_arg_end(char *input, int *i, bool in_quotes[2])
{
	if (in_quotes[S_QUOTE] || in_quotes[D_QUOTE])
		return (false);
	if (input[*i] == '>' || input[*i] == '<' || input[*i] == '|'
		|| input[*i] == ' ' || input[*i] == '&')
	{
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
		if (is_arg_end(input, &i, in_quotes))
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
	return (ft_substr(input, 0, i));
}
