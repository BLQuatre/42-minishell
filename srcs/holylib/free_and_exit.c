/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:44:55 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/18 15:47:24 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "holylib.h"

void	free_and_exit(t_cmd *cmd, t_minishell *mini, int exit_code)
{
	minishell_free(mini);
	cmd_free_lst_from_start(cmd);
	exit(exit_code);
}
