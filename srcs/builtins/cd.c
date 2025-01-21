/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:33:48 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/21 01:09:19 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	*get_target(t_cmd *cmd, t_minishell *mini, int argc)
{
	char	*target ;
	t_env	*home ;

	if (argc == 1)
	{
		home = env_lstget_by_key(mini->env, "HOME");
		if (!home)
		{
			write(STDERR_FILENO, "cd: HOME not set\n", 18);
			cmd->exit_code = 1 ;
			return (NULL);
		}
		target = home->val ;
	}
	if (argc == 2)
		target = cmd->cmd_args[1];
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
		write(STDERR_FILENO, "cd: too many arguments\n", 23);
		cmd->exit_code = 1 ;
		return ;
	}
	target = get_target(cmd, mini, argc);
	if (!target)
		return ;
	ft_bzero(oldpwd_buf, BUFFER_SIZE) ;
	if (!getcwd(oldpwd_buf, BUFFER_SIZE))
		oldpwd_buf[0] = '\0' ;
	if (chdir(target) != 0)
	{
		(write(STDERR_FILENO, "cd: ", 4), perror(target));
		cmd->exit_code = 1 ;
		return ;
	}
	update_oldpwd_env(mini, oldpwd_buf);
	update_pwd_env(mini);
}


// #include "builtins.h"
// #include <readline/readline.h>

// #define COLOR "\e[0;32m"
// #define END "\e[0m"

// int main()
// {
// 	t_minishell	*mini = minishell_new() ;
// 	t_cmd		*cmd = cmd_lstnew() ;
// 	char *line;
// 	while (true)
// 	{
// 		t_env	*PWD = env_lstget_by_key(mini->env, "PWD");
// 		if (PWD)
// 			printf("PWD = %s \n", PWD->val);
// 		t_env	*OLDPWD = env_lstget_by_key(mini->env, "OLDPWD");
// 		if (OLDPWD)
// 			printf("OLDPWD = %s \n", OLDPWD->val);

// 		line = readline(COLOR"WildShell $ "END);
// 		if (!line || !*line)
// 			continue ;
// 		cmd->cmd_args = ft_split(line, ' ');
// 		if (ft_strcmp(cmd->cmd_args[0], "pwd") == 0)
// 			pwd(cmd);
// 		else if (ft_strcmp(cmd->cmd_args[0], "cd") == 0)
// 			cd(cmd, mini);
// 		else if (ft_strcmp(cmd->cmd_args[0], "env") == 0)
// 			env(mini);
// 		else if (ft_strcmp(cmd->cmd_args[0], "echo") == 0)
// 			echo(cmd);
// 		else if (ft_strcmp(cmd->cmd_args[0], "exit") == 0)
// 			my_exit(cmd, mini);
// 		else if (ft_strcmp(cmd->cmd_args[0], "export") == 0)
// 			export(cmd, mini);
// 		else if (ft_strcmp(cmd->cmd_args[0], "unset") == 0)
// 			unset(cmd, mini);
// 		free_str_array(cmd->cmd_args);
// 	}
// 	minishell_free(mini);
// 	cmd_free_lst_from_start(cmd);
// }
