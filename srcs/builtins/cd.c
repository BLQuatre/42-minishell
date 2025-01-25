/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:33:48 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/25 05:35:29 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	*get_target_by_env(t_cmd *cmd, t_minishell *mini, char *key)
{
	t_env	*env ;

	env = env_lstget_by_key(mini->env, key);
	if (!env)
	{
		ft_putstr_fd(CD, STDERR_FILENO);
		ft_putstr_fd(key, STDERR_FILENO);
		ft_putstr_fd(NOT_SET, STDERR_FILENO);
		cmd->exit_code = 1 ;
		return (NULL);
	}
	return (env->val);
}

static char	*get_target(t_cmd *cmd, t_minishell *mini, int argc)
{
	char	*target ;

	target = NULL ;
	if (argc == 1)
		target = get_target_by_env(cmd, mini, "HOME");
	else if (argc == 2)
	{
		if (ft_strcmp(cmd->cmd_args[1], "-") == 0)
			target = get_target_by_env(cmd, mini, "OLDPWD");
		else
			target = cmd->cmd_args[1];
	}
	return (target);
}

static void	update_oldpwd_env(t_minishell *mini, char oldpwd_buf[BUFFER_SIZE])
{
	t_env	*old_pwd ;

	old_pwd = env_lstget_by_key(mini->env, "OLDPWD");
	if (!old_pwd)
	{
		old_pwd = env_lstnew("OLDPWD=");
		if (!old_pwd)
			return ;
		env_lstadd_back(&mini->env, old_pwd);
	}
	free(old_pwd->val);
	old_pwd->val = ft_strdup(oldpwd_buf);
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
	char	oldpwd_buf[BUFFER_SIZE];

	argc = get_argc(cmd->cmd_args);
	if (argc > 2)
	{
		ft_putstr_fd(CD, STDERR_FILENO);
		ft_putstr_fd(TOO_MANY_ARG, STDERR_FILENO);
		cmd->exit_code = 1 ;
		return ;
	}
	target = get_target(cmd, mini, argc);
	if (!target)
		return ;
	ft_bzero(oldpwd_buf, BUFFER_SIZE);
	if (!getcwd(oldpwd_buf, BUFFER_SIZE))
		oldpwd_buf[0] = '\0' ;
	if (chdir(target) != 0)
	{
		(ft_putstr_fd(CD, STDERR_FILENO), perror(target));
		cmd->exit_code = 1 ;
		return ;
	}
	(update_oldpwd_env(mini, oldpwd_buf), update_pwd_env(mini));
}
