/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:16:46 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/23 05:44:33 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// TODO: Remove debug when finished

static int	get_close_par_index(char *input)
{
	int		i;
	int		depth;
	bool	in_quotes[2];

	i = -1;
	depth = 0;
	ft_bzero(in_quotes, sizeof(bool) * 2);
	while (input[++i])
	{
		check_quotes(&in_quotes, input[i]);
		if (is_in_quotes(in_quotes))
			continue ;
		if (input[i] == '(')
			depth++;
		if (input[i] == ')')
		{
			depth--;
			if (depth == 0)
				return (i);
		}
	}
	return (-1);
}

int	handle_parentheses(char *input, t_minishell *mini)
{
	int	cl_par;

	cl_par = get_close_par_index(input);
	debug("SHELL", MAGENTA, "Creating subshell with: `%s`",
		ft_substr(input, 1, cl_par - 1));
	handle_input(ft_substr(input, 1, cl_par - 1), mini);
	debug("SHELL", MAGENTA, "Ending subshell with: `%s`",
		ft_substr(input, 1, cl_par - 1));
	return (cl_par);
}
