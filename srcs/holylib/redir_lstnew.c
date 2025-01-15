/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_lstnew.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:55:43 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/15 01:03:56 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "holylib.h"

t_redir	*redir_lstnew(t_redir_type redir_type, char *file)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = redir_type;
	redir->file = file;
	redir->next = NULL;
	return (redir);
}
