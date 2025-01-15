/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:33:48 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/15 04:12:20 by anoteris         ###   ########.fr       */
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

// TODO: Update the PWD env variable
void	cd(t_cmd *cmd)
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
	// modify pwd and oldpwd
	return ;
}

// #include "holylib.h"
// extern char **environ ;
// int main()
// {
// 	t_cmd	*cmd = cmd_lstnew();

// 	char *cmd_args[4];
// 	cmd_args[0] = "cd" ;
// 	cmd_args[1] = "prout" ;
// 	cmd_args[2] = "pipi" ;
// 	cmd_args[3] = NULL ;
// 	cmd->cmd_args = cmd_args;

// 	char *ls = "/bin/ls" ;
// 	char *ls_args[2];
// 	ls_args[0] = ls ;
// 	ls_args[1] = NULL ;

// 	int pid = fork();
// 	if (pid == 0)
// 		execve(ls, ls_args, environ);
// 	wait(NULL);

// 	cd(cmd);
// 	printf("\n %d \n\n", cmd->exit_code);
// 	pid = fork();
// 	if (pid == 0)
// 		execve(ls, ls_args, environ);
// 	wait(NULL);

// 	cmd->cmd_args[2] = NULL ;
// 	cd(cmd);
// 	printf("\n %d \n\n", cmd->exit_code);
// 	pid = fork();
// 	if (pid == 0)
// 		execve(ls, ls_args, environ);
// 	wait(NULL);

// 	cmd->cmd_args[1] = "srcs" ;
// 	cd(cmd);
// 	printf("\n %d \n\n", cmd->exit_code);
// 	pid = fork();
// 	if (pid == 0)
// 		execve(ls, ls_args, environ);
// 	wait(NULL);

// 	cmd->cmd_args[1] = NULL ;
// 	cd(cmd);
// 	printf("\n %d \n\n", cmd->exit_code);
// 	pid = fork();
// 	if (pid == 0)
// 		execve(ls, ls_args, environ);
// 	wait(NULL);
// }