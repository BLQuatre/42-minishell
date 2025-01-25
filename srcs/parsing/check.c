/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 05:17:23 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/25 04:43:19 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_token_error(char token)
{
	ft_putstr_fd(INVALID_TOKEN, 2);
	ft_putstr_fd(INVALID_TOKEN_QUOTE, 2);
	ft_putchar_fd(token, 2);
	ft_putendl_fd(INVALID_TOKEN_QUOTE, 2);
}

bool	is_valid_input(char *input)
{
	if (!is_valid_parentheses(input))
		return (false);
	if (!is_valid_quote(input, S_QUOTE))
		return (false);
	if (!is_valid_quote(input, D_QUOTE))
		return (false);
	if (!is_valid_redir(input))
		return (false);
	if (!is_valid_pipe(input))
		return (false);
	if (!is_valid_andor(input))
		return (false);
	return (true);
}
