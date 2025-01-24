/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:26:58 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/24 04:41:54 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	handle_input(char *input, t_minishell *mini)
{
	bool	in_quotes[2];
	char	andor[3];

	ft_bzero(in_quotes, sizeof(bool) * 2);
	// if (DEBUG) debug("INPUT", BLUE, "Received: `%s`", input);
	if (!is_valid_input(input))
		return ;
	// if (DEBUG) debug("INPUT", GREEN, "Valid: `%s`", input);
	while (*input)
	{
		andor[0] = 0;
		check_quotes(&in_quotes, *input);
		if (is_in_quotes(in_quotes))
			continue ;
		check_quotes(&in_quotes, *input);
		while (*input && !is_in_quotes(in_quotes) && (*input == ')'
				|| *input == ' ' || ft_strncmp(input, "&&", 2) == 0
				|| ft_strncmp(input, "||", 2) == 0))
		{
			if (ft_strncmp(input, "&&", 2) == 0
				|| ft_strncmp(input, "||", 2) == 0)
			{
				ft_strlcpy(andor, input, 3);
				input++;
			}
			input++;
		}
		input += handle_cmd(input, mini, andor);
	}
}
