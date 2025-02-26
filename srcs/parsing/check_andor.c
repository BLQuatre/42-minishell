/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_andor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 01:28:08 by cauvray           #+#    #+#             */
/*   Updated: 2025/02/23 18:37:50 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	get_last_andor(char *input)
{
	int	len;

	len = ft_strlen(input) - 1;
	while (input[len] && input[len] != '&' && input[len] != '|')
		len--;
	return (input[len]);
}

bool	check_andor_conditions(char *input, int *i, bool *andor_flag)
{
	if ((ft_strncmp(input + *i, "&&", 2) == 0
			|| ft_strncmp(input + *i, "||", 2) == 0) && !*andor_flag)
	{
		if (input[*i + 1] && !input[*i + 2])
			return (print_token_error(input[*i + 1]), false);
		*andor_flag = true;
		(*i)++;
		return (true);
	}
	if (input[*i] == ' ' && *andor_flag)
	{
		if (!input[*i + 1])
			return (print_token_error(get_last_andor(input)), false);
		return (true);
	}
	if (*andor_flag && (input[*i] == '&' || input[*i] == '|'))
		return (print_token_error(input[*i]), false);
	*andor_flag = false;
	return (true);
}

bool	is_valid_andor(char *input)
{
	int		i;
	bool	in_quotes[2];
	bool	andor_flag;

	i = -1;
	andor_flag = false;
	ft_bzero(in_quotes, sizeof(bool) * 2);
	while (input[++i])
	{
		check_quotes(in_quotes, input[i]);
		if (in_quotes[S_QUOTE] || in_quotes[D_QUOTE])
			continue ;
		if (!check_andor_conditions(input, &i, &andor_flag))
			return (false);
	}
	return (true);
}
