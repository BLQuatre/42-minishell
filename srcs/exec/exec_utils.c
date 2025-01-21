/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:25:10 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/20 07:31:55 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

extern char	**environ ;

void	restore_std_fd(int fd_cpy[2], t_cmd *cmd, t_minishell *mini)
{
	if (dup2(fd_cpy[0], STDIN_FILENO) == -1)
	{
		perror("redirection error: cannot duplicate fd:");
		(close(fd_cpy[0]), close(fd_cpy[1]));
		free_and_exit(cmd, mini, EXIT_FAILURE);
	}
	close(fd_cpy[0]);
	if (dup2(fd_cpy[1], STDOUT_FILENO) == -1)
	{
		perror("redirection error: cannot duplicate fd:");
		close(fd_cpy[1]);
		free_and_exit(cmd, mini, EXIT_FAILURE);
	}
	close(fd_cpy[1]);
}

char	**get_all_paths(void)
{
	char	**paths ;
	int		i ;

	paths = NULL ;
	i = 0;
	while (environ[i] && ft_strncmp(environ[i], "PATH=", 5))
		i++;
	if (environ[i])
		paths = ft_split(&environ[i][5], ':');
	if (!paths)
	{
		paths = malloc(2 * sizeof(char *));
		paths[0] = ft_strdup(".");
		paths[1] = NULL;
	}
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
