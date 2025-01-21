/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:25:10 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/21 17:13:17 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	restore_std_fd(int fd_cpy[2], t_cmd *cmd, t_minishell *mini)
{
	if (dup2(fd_cpy[0], STDIN_FILENO) == -1)
	{
		(close(fd_cpy[0]), close(fd_cpy[1]));
		return (dup2_error(cmd, mini));
	}
	close(fd_cpy[0]);
	if (dup2(fd_cpy[1], STDOUT_FILENO) == -1)
	{
		close(fd_cpy[1]);
		return (dup2_error(cmd, mini));
	}
	close(fd_cpy[1]);
}

char	**get_all_paths(t_minishell *mini)
{
	t_env	*env ;
	char	**paths ;

	env = env_lstget_by_key(mini->env, "PATH");
	if (!env)
	{
		paths = malloc(2 * sizeof(char *));
		paths[0] = ft_strdup(".");
		paths[1] = NULL;
	}
	else
		paths = ft_split(env->val, ':');
	return (paths);
}

bool	check_perm(char *cmd, bool *found_cmd)
{
	bool	perm;

	perm = !access(cmd, F_OK);
	if (perm)
	{
		*found_cmd = true ;
		perm = !access(cmd, X_OK);
	}
	return (perm);
}

int	get_empty_pipe_out(void)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (-1);
	close(fd[1]);
	return (fd[0]);
}
