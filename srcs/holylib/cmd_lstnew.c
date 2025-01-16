/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:39:17 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/16 18:53:19 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "holylib.h"

t_cmd	*cmd_lstnew(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->redirs = NULL ;
	cmd->cmd_args = NULL ;
	cmd->is_subshell = false ;
	cmd->exit_code = 0 ;
	cmd->next_cmd = NULL ;
	cmd->prev_cmd = NULL ;
	return (cmd);
}
