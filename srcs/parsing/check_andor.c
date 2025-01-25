/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_andor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 01:28:08 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/25 01:38:58 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_valid_andor(char	*input)
{
	int		i;
	bool	in_quotes[2];
	bool	andor_flag;

	i = -1;
	andor_flag = false;
	ft_bzero(in_quotes, sizeof(bool) * 2);
	while (input[++i])
	{
		check_quotes(&in_quotes, input[i]);
		if (in_quotes[S_QUOTE] || in_quotes[D_QUOTE])
			continue ;
		if ((ft_strncmp(input + i, "&&", 2) == 0
				|| ft_strncmp(input + i, "||", 2) == 0) && !andor_flag)
		{
			if (input[i + 1] && !input[i + 2])
				return (printf(INVALID_TOKEN, ": andor"), false);
			andor_flag = true;
			i++;
			continue ;
		}
		if (input[i] == ' ' && andor_flag)
		{
			if (!input[i + 1])
				return (printf(INVALID_TOKEN, ": andor"), false);
			continue ;
		}
		if (andor_flag && (input[i] == '&' || input[i] == '|'))
			return (printf(INVALID_TOKEN, ": andor"), false);
		andor_flag = false;
	}
	return (true);
}
