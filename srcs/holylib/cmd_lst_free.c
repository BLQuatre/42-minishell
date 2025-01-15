/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:23:50 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/15 12:08:51 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "holylib.h"

void	cmd_free(t_cmd *to_free)
{
	redir_free_lst(to_free->redirs);
	free_str_array(to_free->cmd_args);
	free(to_free);
}

void	cmd_free_lst(t_cmd *lst_to_free)
{
	t_cmd	*nxt ;

	if (!lst_to_free)
		return ;
	nxt = lst_to_free->next_cmd ;
	while (nxt)
	{
		cmd_free(lst_to_free);
		lst_to_free = nxt ;
		nxt = lst_to_free->next_cmd ;
	}
	cmd_free(lst_to_free);
}
