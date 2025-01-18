/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:33:48 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/18 03:00:01 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	*get_target(t_cmd *cmd, int argc)
{
	char	*target ;

	if (argc == 1)
	{
		target = getenv("HOME");
		if (!target)
		{
			write(STDERR_FILENO, "cd: HOME not set\n", 18);
			cmd->exit_code = 1 ;
			return (NULL);
		}
	}
	if (argc == 2)
		target = cmd->cmd_args[1];
	return (target);
}

static void	update_oldpwd_env(t_minishell *mini)
{
	t_env	*old_pwd ;
	t_env	*pwd ;

	pwd = env_lstget_by_key(mini->env, "PWD");
	if (!pwd)
		return ;
	old_pwd = env_lstget_by_key(mini->env, "OLDPWD");
	if (!old_pwd)
	{
		old_pwd = env_lstnew("OLDPWD=");
		if (!old_pwd)
			return ;
		env_lstadd_back(&mini->env, old_pwd);
	}
	free(old_pwd->val);
	old_pwd->val = ft_strdup(pwd->val);
}

static void	update_pwd_env(t_minishell *mini)
{
	t_env	*pwd ;
	char	cwd[BUFFER_SIZE];

	if (!getcwd(cwd, BUFFER_SIZE))
		return ;
	pwd = env_lstget_by_key(mini->env, "PWD");
	if (!pwd)
	{
		pwd = env_lstnew("PWD=");
		if (!pwd)
			return ;
		env_lstadd_back(&mini->env, pwd);
	}
	free(pwd->val);
	pwd->val = ft_strdup(cwd);
}

void	cd(t_cmd *cmd, t_minishell *mini)
{
	char	*target ;
	int		argc ;

	argc = get_argc(cmd->cmd_args);
	if (argc > 2)
	{
		write(STDERR_FILENO, "cd: too many arguments\n", 23);
		cmd->exit_code = 1 ;
		return ;
	}
	target = get_target(cmd, argc);
	if (!target)
		return ;
	if (chdir(target) != 0)
	{
		(write(STDERR_FILENO, "cd: ", 4), perror(target));
		cmd->exit_code = 1 ;
		return ;
	}
	update_oldpwd_env(mini);
	update_pwd_env(mini);
}
