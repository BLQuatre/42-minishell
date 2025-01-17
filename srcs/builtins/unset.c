/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 02:58:49 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/17 03:43:43 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	unset(t_cmd *cmd, t_minishell *mini)
{
	int	i ;

	i = 0 ;
	while (argv[++i])
		env_lstdel_by_key(mini->env, argv[i]);
}
