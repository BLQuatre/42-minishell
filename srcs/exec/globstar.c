/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globstar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 02:08:46 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/23 08:31:41 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// For logical purpose, both str and entry shouldn't be empty strings
static bool	globstar_match(char *str, char *entry)
{
	int		i ;
	int		j ;

	i = 0 ;
	j = 0 ;
	while ((str[i] && entry[j]) || str[i] == - '*')
	{
		if (str[i] == - '*')
		{
			while (str[i] && str[i] == - '*')
				i++ ;
			if (str[i] == '\0')
				return (true);
			while (entry[j] && entry[j] != str[i])
				j++ ;
		}
		if (str[i] != entry[j])
			return (false);
		i++ ;
		j++ ;
	}
	if (str[i] != entry[j])
		return (false);
	return (true);
}

static bool	globstar_insert_args(t_cmd *cmd, char *str, int index)
{
	DIR				*dir ;
	struct dirent	*entry ;
	bool			inserted ;

	inserted = false ;
	dir = opendir(".");
	if (!dir)
		return (cmd->exit_code = 1, perror("opendir"), inserted);
	errno = 0 ;
	entry = readdir(dir);
	while (entry)
	{
		if (globstar_match(str, entry->d_name)
			&& (!(entry->d_name[0] == '.') || str[0] == '.'))
		{
			cmd->cmd_args = str_array_insert(cmd->cmd_args,
					ft_strdup(entry->d_name), ++index);
			inserted = true ;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	if (errno)
		return (cmd->exit_code = 1, perror("readdir"), inserted);
	return (inserted);
}

void	globstar_args(t_cmd *cmd)
{
	int		i ;

	i = 0 ;
	while (cmd->cmd_args[++i])
	{
		if (ft_strchr(cmd->cmd_args[i], - '*'))
		{
			if (globstar_insert_args(cmd, cmd->cmd_args[i], i))
				str_array_erase(cmd->cmd_args, i);
			else
			{
				while (ft_strchr(cmd->cmd_args[i], - '*'))
					*ft_strchr(cmd->cmd_args[i], - '*') = '*' ;
			}
		}
	}
}

static int	globstar_insert_redirs(t_cmd *cmd, t_redir *redir, char *str)
{
	DIR				*dir ;
	struct dirent	*entry ;
	int				inserted ;

	inserted = 0 ;
	dir = opendir(".");
	if (!dir)
		return (cmd->exit_code = 1, perror("opendir"), inserted);
	errno = 0 ;
	entry = readdir(dir);
	while (entry)
	{
		if (globstar_match(str, entry->d_name)
			&& (!(entry->d_name[0] == '.') || str[0] == '.'))
		{
			(free(redir->file), redir->file = ft_strdup(entry->d_name));
			inserted++ ;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	if (errno)
		return (cmd->exit_code = 1, perror("readdir"), inserted);
	return (inserted);
}

void	globstar_redirs(t_cmd *cmd, t_minishell *mini)
{
	t_redir	*cur ;
	int		inserted ;
	char	*redir_dup ;

	cur = cmd->redirs ;
	while (cur)
	{
		if (ft_strchr(cur->file, - '*'))
		{
			redir_dup = ft_strdup(cur->file);
			inserted = globstar_insert_redirs(cmd, cur, redir_dup);
			if (inserted == 0)
				while (ft_strchr(cur->file, - '*'))
					*ft_strchr(cur->file, - '*') = '*' ;
			else if (inserted >= 2)
				return (ambiguous_redirect_error(cmd, mini, redir_dup));
			free(redir_dup);
		}
		cur = cur->next ;
	}
}
