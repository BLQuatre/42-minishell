/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 05:17:23 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/25 01:28:34 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_valid_input(char *input)
{
	int	parentheses_result;

	parentheses_result = is_valid_parentheses(input);
	if (parentheses_result > 0)
		return (printf(INVALID_TOKEN, " \"(\""), false);
	else if (parentheses_result < 0)
		return (printf(INVALID_TOKEN, " \")\""), false);
	if (!is_valid_quote(input, S_QUOTE))
		return (printf(INVALID_TOKEN, " \"'\""), false);
	if (!is_valid_quote(input, D_QUOTE))
		return (printf(INVALID_TOKEN, " '\"'"), false);
	if (!is_valid_redir(input))
		return (false);
	if (!is_valid_pipe(input))
		return (false);
	if (!is_valid_andor(input))
		return (false);
	return (true);
}
