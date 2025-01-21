/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:12:08 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/21 16:12:26 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	check_quotes(bool (*in_quotes)[2], char curr_chr)
{
	if (curr_chr == '\'' && !(*in_quotes)[D_QUOTE])
		(*in_quotes)[S_QUOTE] = !(*in_quotes)[S_QUOTE];
	if (curr_chr == '"' && !(*in_quotes)[S_QUOTE])
		(*in_quotes)[D_QUOTE] = !(*in_quotes)[D_QUOTE];
}

bool	is_in_quotes(bool in_quotes[2])
{
	return (in_quotes[S_QUOTE] || in_quotes[D_QUOTE]);
}
