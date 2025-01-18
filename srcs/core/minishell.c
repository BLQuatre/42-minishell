/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:56:12 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/18 12:30:09 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "assert.h"

void	check_quotes(bool (*in_quotes)[2], char curr_chr)
{
	if (curr_chr == '\'' && !(*in_quotes)[D_QUOTE])
		(*in_quotes)[S_QUOTE] = !(*in_quotes)[S_QUOTE];
	if (curr_chr == '"' && !(*in_quotes)[S_QUOTE])
		(*in_quotes)[D_QUOTE] = !(*in_quotes)[D_QUOTE];
}

bool	is_in_quotes(bool in_quotes[2])
{
	return (in_quotes[S_QUOTE] || in_quotes[D_QUOTE]);
}

int get_close_par_index(char *input)
{
	int		i;
	int		depth;
	bool	in_quotes[2];

	i = -1;
	depth = 0;
	ft_bzero(in_quotes, QUOTES_BOOL_SIZE);
	while (input[++i])
	{
		check_quotes(&in_quotes, input[i]);
		if (is_in_quotes(in_quotes))
			continue;
		if (input[i] == '(')
			depth++;
		if (input[i] == ')')
		{
			depth--;
			if (depth == 0)
				return (i);
		}
	}
	return (-1);
}
// TODO: add copy env to function parameter
char	*parse_env(char *input, t_env *env)
{
	(void) env;
	if (input[0] == '\'')
		return (ft_substr(input, 1, ft_strlen(input) -2));
	debug("PARSE", BRIGHT_RED,"Parsing env in: `%s`", input);

	// TODO: Do env var
	if (input[0] == '"')
		return (ft_substr(input, 1, ft_strlen(input) -2));
	else
		return (input);
}

char	*parse_arg(char *input, int *len)
{
	int		i;
	char	last_quote;

	i = 0;
	last_quote = 0;
	debug("PARSE", RED, "Parsing arg: `%s`", input);
	while (input[i])
	{
		if (last_quote == 0 && (input[i] != ' '))
		{
			if (input[i] == '\'' || input[i] == '"')
			{
				last_quote = input[i];
				i++;
			}
			else
				last_quote = ' ';
		}
		while (input[i] && last_quote != 0 && input[i] != last_quote)
			i++;
		if (input[i] == last_quote && input[i] != ' ')
			i++;
		if (input[i] && (input[i] == ' ' || input[i] == '>' || input[i] == '<'))
		{
			if (ft_strncmp(input + i, "&&", 2) == 0 || ft_strncmp(input + i, "||", 2) == 0)
				i++;
			break;
		}
	}
	(*len) += i;
	return (parse_env(ft_substr(input, 0, i), env_copy()));
}

char	**cmd_add_args(char **cmd_args, char *arg)
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

t_redir_type get_redir_type(char *input)
{
	if (ft_strncmp(input, "<<", 2) == 0)
		return (HERE_DOC);
	if (ft_strncmp(input, "<", 1) == 0)
		return (IN);
	if (ft_strncmp(input, ">>", 2) == 0)
		return (OUT_APP);
	if (ft_strncmp(input, ">", 1) == 0)
		return (OUT_TRUNC);
	return (-1);
}

t_redir	*parse_redir(char *input, int *len)
{
	int		redir_len;
	char	*redir;

	redir_len = 0;
	debug("REDIR", BRIGHT_CYAN, "Redirection: `%s`", input);
	redir = parse_arg(input, &redir_len);
	input += redir_len;
	(*len) += redir_len;
	while (*input && *input == ' ')
	{
		(*len)++;
		input++;
	}
	// TODO: protect function from < 0 redir type
	return (redir_lstnew(get_redir_type(redir), parse_arg(input, len)));
}

t_cmd	*parse_cmd(char *input)
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
			break;
		// printf("input: ²%s²\n", input + i);
		if ((input + i)[0] == '>' || (input + i)[0] == '<' || (input + i)[0] == '|')
			redir_lstadd_back(&(cmd->redirs), parse_redir(input + i, &i));
		else
			cmd->cmd_args = cmd_add_args(cmd->cmd_args, parse_arg(input + i, &i));
		// debug("PARSE", RED, "i: %d", i);
	}
	show_cmd(cmd);
	return (NULL);
}

int	handle_cmd(char *input)
{
	bool	in_quotes[2];
	int	i;

	debug("HNDLG", BLUE, "Handling cmd: `%s`", input);
	ft_bzero(in_quotes, QUOTES_BOOL_SIZE);
	i = 0;
	while (is_in_quotes(in_quotes) || (input[i] && input[i] != '(' && input[i] != ')' && ft_strncmp(input + i, "&&", 2) != 0 && ft_strncmp(input + i, "||", 2) != 0))
	{
		check_quotes(&in_quotes, input[i]);
		i++;
	}
	parse_cmd(ft_substr(input, 0, i));
	return (i);
}

/**
 * @param input The input must start with open parenthese
 * @return how many chars skipped before close parenthese
 */
int	handle_parentheses(char *input)
{
	int cl_par = get_close_par_index(input);

	debug("SHELL", MAGENTA, "Creating subshell with: `%s`", ft_substr(input, 1, cl_par - 1));
	handle_input(ft_substr(input, 1, cl_par - 1));
	debug("SHELL", MAGENTA, "Ending subshell with: `%s`", ft_substr(input, 1, cl_par - 1));
	return (cl_par);
}

void	handle_input(char *input)
{
	bool	in_quotes[2];

	ft_bzero(in_quotes, QUOTES_BOOL_SIZE);
	// debug("INPUT", BLUE, "Received: `%s`", input);
	if (!is_valid_input(input))
		return;
	// debug("INPUT", GREEN, "Valid: `%s`", input);
	while (*input)
	{
		check_quotes(&in_quotes, *input);
		if (is_in_quotes(in_quotes))
			continue;
		if (*input == '(')
			input += handle_parentheses(input);
		check_quotes(&in_quotes, *input);
		while (*input && !is_in_quotes(in_quotes) && (*input == ')' || *input == ' ' || ft_strncmp(input, "&&", 2) == 0 || ft_strncmp(input, "||", 2) == 0))
		{
			if (ft_strncmp(input, "&&", 2) == 0 || ft_strncmp(input, "||", 2) == 0)
				input++;
			input++;
		}
		input += handle_cmd(input);
	}
}

int	main(int argc, char *argv[])
{
	// FIXME: Remove when finished
	if (argc > 1)
	{
		while (--argc > 0)
			handle_input(argv[argc]);
		return (0);
	}
	// END

	char	*msg;

	while (true)
	{
		msg = readline(SHELL_PROMPT);
		if (msg == NULL)
		{
			printf("exit\n");
			break;
		}
		if (ft_strlen(msg) == 0)
			continue;
		add_history(msg);
		handle_input(msg);
		free(msg);
	}
	return (0);
}
