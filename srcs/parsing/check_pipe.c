/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 01:26:33 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/25 01:37:33 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_valid_pipe(char *input)
{
	int		i;
	bool	in_quotes[2];
	bool	pipe_flag;

	i = -1;
	pipe_flag = false;
	ft_bzero(in_quotes, sizeof(bool) * 2);
	while (input[++i])
	{
		check_quotes(&in_quotes, input[i]);
		if (in_quotes[S_QUOTE] || in_quotes[D_QUOTE])
			continue ;
		if (input[i] == '|' && input[i + 1] != '|' && !pipe_flag)
		{
			if (!input[i + 1])
				return (printf(INVALID_TOKEN, ": pipe"), false);
			pipe_flag = true;
			continue ;
		}
		if (input[i] == ' ' && pipe_flag)
		{
			if (!input[i + 1])
				return (printf(INVALID_TOKEN, ": pipe"), false);
			continue ;
		}
		if (pipe_flag && (input[i] == '&' || input[i] == '|'))
			return (printf(INVALID_TOKEN, ": pipe"), false);
		pipe_flag = false;
	}
	return (true);
}
