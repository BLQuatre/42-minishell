/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_to_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:03:35 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/21 17:23:22 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*local_cmd(char *cmd)
{
	bool	found_cmd ;

	found_cmd = false ;
	if (check_perm(cmd, &found_cmd))
		return (ft_strdup(cmd));
	if (found_cmd)
		errno = EACCES ;
	return (NULL);
}

static char	*get_path_cmd(char *path, char *cmd)
{
	char	*res ;

	res = ft_calloc(ft_strlen(path) + ft_strlen(cmd) + 2, 1);
	ft_strlcpy(res, path, ft_strlen(path) + 1);
	ft_strlcat(res, "/", ft_strlen(res) + 2);
	ft_strlcat(res, cmd, ft_strlen(res) + ft_strlen(cmd) + 1);
	return (res);
}

static char	*non_local_cmd(char *cmd, t_minishell *mini)
{
	char	**paths ;
	int		i ;
	char	*res ;
	bool	found_cmd ;

	found_cmd = false ;
	paths = get_all_paths(mini);
	i = -1 ;
	while (paths && paths[++i])
	{
		res = get_path_cmd(paths[i], cmd);
		if (check_perm(res, &found_cmd))
			return (free_str_array(paths), (res));
		else
			free(res);
	}
	if (found_cmd)
		errno = EACCES ;
	free_str_array(paths);
	return (NULL);
}

static char	*get_valid_path_cmd(char *cmd, t_minishell *mini)
{
	if (ft_strchr(cmd, '/'))
		return (local_cmd(cmd));
	else
		return (non_local_cmd(cmd, mini));
}

void	add_path_to_cmd(t_cmd *cmd, t_minishell *mini)
{
	char	*tmp ;

	tmp = get_valid_path_cmd(cmd->cmd_args[0], mini);
	if (!tmp)
	{
		if (!errno)
			errno = ENOENT ;
		perror(cmd->cmd_args[0]);
		(free_str_array(cmd->cmd_args), cmd->cmd_args = NULL);
		return ;
	}
	free(cmd->cmd_args[0]);
	cmd->cmd_args[0] = tmp ;
}
