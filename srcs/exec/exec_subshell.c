/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 01:55:00 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/26 01:58:00 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"

void	exec_subshell(t_cmd *cmd, t_minishell *mini)
{
	char	*tmp ;

	tmp = ft_strdup(cmd->cmd_args[0]);
	cmd_free_lst_from_start(cmd);
	handle_input(tmp, mini);
	free_and_exit(NULL, mini, mini->exit_code);
}
