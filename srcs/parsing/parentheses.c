/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 23:48:20 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/25 23:48:30 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	calc_parentheses_depth(int actual_depth, bool in_quotes[2], char c)
{
	if (!in_quotes[S_QUOTE] && !in_quotes[D_QUOTE] && c == '(')
		actual_depth++;
	if (!in_quotes[S_QUOTE] && !in_quotes[D_QUOTE] && c == ')')
		actual_depth--;
	return (actual_depth);
}
