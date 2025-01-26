/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:26:33 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/26 05:43:30 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	is_arg_end(char *input, int *i, bool in_quotes[2])
{
	if (is_in_quotes(in_quotes))
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
		if (input[i] == '(' && !is_in_quotes(in_quotes))
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
