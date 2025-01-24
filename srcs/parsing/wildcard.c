/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 00:51:46 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/25 00:02:31 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	parse_wildcard(char *input)
{
	int		i;
	bool	in_quotes[2];

	i = 0;
	ft_bzero(&in_quotes, sizeof(bool) * 2);
	if (DEBUG) debug("WILDC", BRIGHT_YELLOW, "Parsing wildcard in: `%s`", input);
	while (input[i])
	{
		check_quotes(&in_quotes, input[i]);
		if (input[i] == '*' && !in_quotes[S_QUOTE] && !in_quotes[D_QUOTE])
			input[i] *= -1;
		i++;
	}
}

void	handle_wildcard(t_cmd *cmd)
{
	int		i;
	t_redir	*tmp_redir;

	if (cmd->cmd_args)
	{
		i = -1;
		while (cmd->cmd_args[++i])
			parse_wildcard(cmd->cmd_args[i]);
	}
	tmp_redir = cmd->redirs;
	while (tmp_redir)
	{
		parse_wildcard(tmp_redir->file);
		tmp_redir = tmp_redir->next;
	}
}
