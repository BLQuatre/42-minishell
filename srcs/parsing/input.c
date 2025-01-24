/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:26:58 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/24 00:43:59 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	handle_input(char *input, t_minishell *mini)
{
	bool	in_quotes[2];

	ft_bzero(in_quotes, sizeof(bool) * 2);
	// if (DEBUG) debug("INPUT", BLUE, "Received: `%s`", input);
	if (!is_valid_input(input))
		return ;
	// if (DEBUG) debug("INPUT", GREEN, "Valid: `%s`", input);
	while (*input)
	{
		check_quotes(&in_quotes, *input);
		if (is_in_quotes(in_quotes))
			continue ;
		// if (*input == '(')
		// 	input += handle_subshell(input, mini);
		check_quotes(&in_quotes, *input);
		while (*input && !is_in_quotes(in_quotes) && (*input == ')'
				|| *input == ' ' || ft_strncmp(input, "&&", 2) == 0
				|| ft_strncmp(input, "||", 2) == 0))
		{
			if (ft_strncmp(input, "&&", 2) == 0
				|| ft_strncmp(input, "||", 2) == 0)
				input++;
			input++;
		}
		input += handle_cmd(input, mini);
	}
}
