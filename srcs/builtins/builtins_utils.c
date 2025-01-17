/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 03:18:58 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/17 05:16:10 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	get_argc(char *argv[])
{
	int	res ;

	res = 0 ;
	while (argv[res])
		res++ ;
	return (res);
}

void	display_environment(t_minishell *mini, char *prompt)
{
	t_env	*cur_env ;

	cur_env = mini->env ;
	while (cur_env)
	{
		printf("%s%s=%s\n", prompt, cur_env->key, cur_env->val);
		cur_env = cur_env->next ;
	}
}
