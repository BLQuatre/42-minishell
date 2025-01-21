/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:10:56 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/21 16:56:38 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_redir_type	get_redir_type(char *input)
{
	if (ft_strncmp(input, "<<", 2) == 0)
		return (HERE_DOC);
	if (ft_strncmp(input, "<", 1) == 0)
		return (IN);
	if (ft_strncmp(input, ">>", 2) == 0)
		return (OUT_APP);
	if (ft_strncmp(input, ">", 1) == 0)
		return (OUT_TRUNC);
	return (OUT_APP);
}

t_redir	*parse_redir(char *input, int *len)
{
	int		redir_len;
	char	*redir;

	redir_len = 0;
	debug("REDIR", BRIGHT_CYAN, "Redirection: `%s`", input);
	redir = parse_arg(input, &redir_len);
	input += redir_len;
	(*len) += redir_len;
	while (*input && *input == ' ')
	{
		(*len)++;
		input++;
	}
	return (redir_lstnew(get_redir_type(redir), parse_arg(input, len)));
}
