/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:10:56 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/23 05:44:14 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_redir_type	get_redir_type(char *input, int *len)
{
	if (ft_strncmp(input, ">>", 2) == 0)
	{
		*len = 2;
		return (OUT_APP);
	}
	else if (ft_strncmp(input, "<<", 2) == 0)
	{
		*len = 2;
		return (HERE_DOC);
	}
	else if (input[0] == '>')
	{
		*len = 1;
		return (OUT_TRUNC);
	}
	else if (input[0] == '<')
	{
		*len = 1;
		return (IN);
	}
	return (OUT_APP);
}

t_redir	*parse_redir(char *input, int *len)
{
	int				redir_len;
	t_redir_type	redir_type;

	redir_len = 0;
	redir_type = get_redir_type(input, &redir_len);
	debug("REDIR", BRIGHT_CYAN, "Redirection: `%s`", input);
	input += redir_len;
	(*len) += redir_len;
	while (*input && *input == ' ')
	{
		(*len)++;
		input++;
	}
	return (redir_lstnew(redir_type, parse_arg(input, len)));
}
