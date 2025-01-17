/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 06:37:34 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/17 06:46:52 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "holylib.h"

t_minishell	*minishell_new(void)
{
	t_minishell	*mini ;

	mini = malloc(sizeof(t_minishell));
	if (!mini)
		return (NULL);
	mini->env = env_copy();
	mini->exit_code = 0 ;
	return (mini);
}

void	minishell_free(t_minishell *to_free)
{
	env_free_lst(to_free->env);
	free(to_free);
}
