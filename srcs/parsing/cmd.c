/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 07:04:32 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/26 01:43:53 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "exec.h"

/**
 * @note arg param must be malloc
 */
static char	**cmd_add_args(char **cmd_args, char *arg)
{
	int		i;
	char	**new_cmd_args;

	i = 0;
	while (cmd_args && cmd_args[i])
		i++;
	new_cmd_args = (char **) malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (cmd_args && cmd_args[i])
	{
		new_cmd_args[i] = cmd_args[i];
		i++;
	}
	new_cmd_args[i++] = arg;
	new_cmd_args[i] = NULL;
	free(cmd_args);
	return (new_cmd_args);
}

static void	handle_sub(t_cmd *cmd, t_minishell *mini)
{
	if (!cmd)
		return ;
	cmd = cmd_lstfirst(cmd);
	while (cmd)
	{
		handle_env(cmd, mini);
		handle_wildcard(cmd);
		handle_quotes(cmd);
		cmd = cmd->next_cmd;
	}
}

// if (DEBUG) debug("PARSE", YELLOW, "Parsing: `%s`", input);
t_cmd	*parse_cmd(char *input, t_minishell *mini)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	if (!input[i])
		return (NULL);
	cmd = cmd_lstnew();
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (input[i] == 0)
			break ;
		if (input[i] == '>' || input[i] == '<')
			redir_lstadd_back(&(cmd->redirs), parse_redir(input + i, &i));
		else
			cmd->cmd_args = cmd_add_args(cmd->cmd_args,
					parse_arg(input + i, &i, &cmd->is_subshell));
	}
	handle_sub(cmd, mini);
	return (cmd);
}

int	handle_cmd(char *input, t_minishell *mini, char andor[3], char *input_save)
{
	bool	in_quotes[2];
	int		par_depth;
	int		i;
	t_cmd	*cmd;
	char	*cmd_str;

	(ft_bzero(in_quotes, sizeof(bool) * 2), i = 0, par_depth = 0);
	while (is_in_quotes(in_quotes) || par_depth > 0 || (input[i]
			&& ft_strncmp(input + i, "&&", 2) != 0
			&& ft_strncmp(input + i, "||", 2) != 0))
	{
		check_quotes(&in_quotes, input[i]);
		par_depth = calc_parentheses_depth(par_depth, in_quotes, input[i]);
		i++;
	}
	cmd_str = ft_substr(input, 0, i);
	cmd = handle_pipe(cmd_str, mini);
	free(cmd_str);
	if (cmd && !((ft_strncmp(andor, "&&", 2) == 0 && mini->exit_code != 0)
			|| (ft_strncmp(andor, "||", 2) == 0 && mini->exit_code == 0)))
		exec(mini, cmd, input_save);
	else
		cmd_free_lst_from_start(cmd);
	return (i);
}

// int	handle_cmd(char *input, t_minishell *mini, char andor[3])
// {
// 	bool	in_quotes[2];
// 	int		i;
// 	t_cmd	*cmd;
// 	char	*cmd_str;

// 	if (DEBUG) debug("HNDLG", BLUE, "Handling input: `%s`", input);
// 	ft_bzero(in_quotes, sizeof(bool) * 2);
// 	i = 0;
// 	while (is_in_quotes(in_quotes) || (input[i]
// 			&& ft_strncmp(input + i, "&&", 2) != 0
// 			&& ft_strncmp(input + i, "||", 2) != 0))
// 	{
// 		check_quotes(&in_quotes, input[i]);
// 		i++;
// 	}
// 	if (DEBUG) debug("HNDLG", BLUE, "Handling suite: `%s`", input + i);
// 	cmd_str = ft_substr(input, 0, i);
// 	if (DEBUG) debug("HNDLG", BRIGHT_BLUE, "Handling cmd: `%s`", cmd_str);
// 	cmd = handle_pipe(cmd_str, mini);
// 	free(cmd_str);
// 	if (DEBUG) debug_show_cmd(cmd);
// 	if (cmd && !((ft_strncmp(andor, "&&", 2) == 0 && mini->exit_code != 0)
// 			|| (ft_strncmp(andor, "||", 2) == 0 && mini->exit_code == 0)))
// 		exec(mini, cmd);
// 	return (i);
// }
