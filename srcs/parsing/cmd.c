/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 07:04:32 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/23 05:46:23 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

// t_cmd	*parse_cmd(char *input, t_minishell *mini)
// {
// 	int		i;
// 	t_cmd	*cmd;

// 	i = 0;
// 	if (!input[i])
// 		return (NULL);
// 	cmd = cmd_lstnew();
// 	debug("PARSE", YELLOW, "Parsing: `%s`", input);
// 	while (input[i])
// 	{
// 		while (input[i] == ' ')
// 			i++;
// 		if (input[i] == 0)
// 			break ;
// 		// printf("input: ²%s²\n", input + (i));
// 		if ((input + i)[0] == '>' || (input + i)[0] == '<')
// 			redir_lstadd_back(&(cmd->redirs), parse_redir(input + i, &i));
// 		else if (*(input + i) == '|')
// 			break ;
// 		else
// 			cmd->cmd_args = cmd_add_args(cmd->cmd_args, parse_arg(input + i, &i));
// 			// int test = 0;

// 		// debug("PARSE", RED, "i: %d", i);
// 	}
// 	if (*(input + i) == '|')
// 	{
// 		debug("PARSE", YELLOW, "Sending pipe: `%s`", input + (++i));
// 		cmd->next_cmd = parse_cmd(input + i, mini);
// 		// printf("ptr: %p\n", cmd->next_cmd);
// 	}
// 	handle_env(cmd, mini);
// 	show_cmd(cmd);
// 	return (cmd);
// }

t_cmd	*parse_cmd(char *input, t_minishell *mini)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	if (!input[i])
		return (NULL);
	cmd = cmd_lstnew();
	debug("PARSE", YELLOW, "Parsing: `%s`", input);
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (input[i] == 0)
			break ;
		// printf("input: ²%s²\n", input + i);
		if ((input + i)[0] == '>' || (input + i)[0] == '<')
			redir_lstadd_back(&(cmd->redirs), parse_redir(input + i, &i));
		else
			cmd->cmd_args = cmd_add_args(cmd->cmd_args, parse_arg(input + i, &i));
		// debug("PARSE", RED, "i: %d", i);
	}
	handle_env(cmd, mini);
	handle_wildcard(cmd);
	handle_quotes(cmd);
	// show_cmd(cmd);
	return (cmd);
}

int	handle_cmd(char *input, t_minishell *mini)
{
	bool	in_quotes[2];
	int		i;
	t_cmd	*cmd;
	char	*cmd_str;

	debug("HNDLG", BLUE, "Handling input: `%s`", input);
	ft_bzero(in_quotes, sizeof(bool) * 2);
	i = 0;
	while (is_in_quotes(in_quotes) || (input[i] && input[i] != '(' && input[i] != ')' && ft_strncmp(input + i, "&&", 2) != 0 && ft_strncmp(input + i, "||", 2) != 0))
	{
		check_quotes(&in_quotes, input[i]);
		i++;
	}
	cmd_str = ft_substr(input, 0, i);
	debug("HNDLG", BRIGHT_BLUE, "Handling cmd: `%s`", cmd_str);
	cmd = handle_pipe(cmd_str, mini);
	show_cmd(cmd);
	return (i);
}
