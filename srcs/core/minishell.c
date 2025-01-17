/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:56:12 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/17 03:46:07 by cauvray          ###   ########.fr       */
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

t_cmd	parse_cmd(char *input)
{
	bool	in_quotes[2];

	if (!(*input))
		return;
		ft_bzero(in_quotes, QUOTES_BOOL_SIZE);
	debug("PARSE", YELLOW, "Parsing: `%s`", input);
	// while (*input)
}

int	handle_cmd(char *input)
{
	bool	in_quotes[2];
	int	i;

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
	debug("INPUT", BLUE, "Received: `%s`", input);
	if (!is_valid_input(input))
		return;
	debug("INPUT", GREEN, "Valid: `%s`", input);
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
