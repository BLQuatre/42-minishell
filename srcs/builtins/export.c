/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 05:12:58 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/25 04:51:49 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static bool	is_valid_env_key(char *arg)
{
	int	i ;

	if (arg[0] == '=')
		return (false);
	i = 0 ;
	while (arg[i] && arg[i] != '=')
	{
		if (!(ft_isalnum(arg[i]) || arg[i] == '_'))
			return (false);
		i++ ;
	}
	return (true);
}

static void	replace_or_add(char *cmd_args, t_minishell *mini)
{
	t_env	*env ;
	char	*key ;
	long	equal_pos;

	equal_pos = ft_strchr(cmd_args, '=') - cmd_args;
	key = ft_substr(cmd_args, 0, equal_pos);
	env = env_lstget_by_key(mini->env, key);
	free(key);
	if (env)
	{
		free(env->val);
		env->val = ft_substr(cmd_args, equal_pos + 1,
				ft_strlen(cmd_args + equal_pos + 1));
	}
	else
		env_lstadd_back(&mini->env, env_lstnew(cmd_args));
}

void	export(t_cmd *cmd, t_minishell *mini)
{
	int		argc ;
	int		i ;

	argc = get_argc(cmd->cmd_args);
	if (argc == 1)
	{
		display_environment(mini, "declare -x ");
		return ;
	}
	i = 0 ;
	while (cmd->cmd_args[++i])
	{
		if (!is_valid_env_key(cmd->cmd_args[i]))
		{
			ft_putstr_fd(EXPORT, STDERR_FILENO);
			ft_putstr_fd(cmd->cmd_args[i], STDERR_FILENO);
			ft_putstr_fd(NOT_VALID_ID, STDERR_FILENO);
			cmd->exit_code = 1 ;
		}
		else if (ft_strchr(cmd->cmd_args[i], '='))
			replace_or_add(cmd->cmd_args[i], mini);
	}
}
