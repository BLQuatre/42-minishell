/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:56:12 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/16 04:27:29 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "assert.h"

int get_open_chr_index(char *input, char open_chr, char close_chr, int depth)
{
	bool	in_quotes[2];
	int		i;
	int		i_depth;

	i = -1;
	i_depth = 0;
	ft_bzero(in_quotes, sizeof(bool) * 2);
	while (input[++i])
	{
		if (input[i] == '\'' && !in_quotes[D_QUOTE])
			in_quotes[S_QUOTE] = !in_quotes[S_QUOTE];
		if (input[i] == '"' && !in_quotes[S_QUOTE])
			in_quotes[D_QUOTE] = !in_quotes[D_QUOTE];
		if (input[i] == open_chr && !in_quotes[S_QUOTE] && !in_quotes[D_QUOTE])
		{
			if (i_depth == depth)
				return (i);
			i_depth++;
		}
		if (input[i] == close_chr && !in_quotes[S_QUOTE] && !in_quotes[D_QUOTE])
			i_depth--;
	}
	return (-1);
}

int get_close_chr_index(char *input, char open_chr, char close_chr, int depth)
{
	bool	in_quotes[2];
	int		i;
	int		i_depth;

	i = -1;
	i_depth = 0;
	ft_bzero(in_quotes, sizeof(bool) * 2);
	while (input[++i])
	{
		if (input[i] == '\'' && !in_quotes[D_QUOTE])
			in_quotes[S_QUOTE] = !in_quotes[S_QUOTE];
		if (input[i] == '"' && !in_quotes[S_QUOTE])
			in_quotes[D_QUOTE] = !in_quotes[D_QUOTE];
		if (input[i] == open_chr && !in_quotes[S_QUOTE] && !in_quotes[D_QUOTE])
			i_depth++;
		if (input[i] == close_chr && !in_quotes[S_QUOTE] && !in_quotes[D_QUOTE])
		{
			i_depth--;
			if (i_depth == depth)
				return (i);
		}
	}
	return (-1);
}



char *get_sub_command(char *input)
{
	int		i;
	bool	in_quotes[2];
	int		p_index;
	int		p_start;

	i = -1;
	p_index = 0;
	p_start = 0;
	ft_bzero(in_quotes, sizeof(bool) * 2);
	while (input[++i])
	{
		if (input[i] == '\'' && !in_quotes[D_QUOTE])
			in_quotes[S_QUOTE] = !in_quotes[S_QUOTE];
		if (input[i] == '"' && !in_quotes[S_QUOTE])
			in_quotes[D_QUOTE] = !in_quotes[D_QUOTE];
		if (input[i] == '(' && !in_quotes[S_QUOTE] && !in_quotes[D_QUOTE])
		{
			if (p_start == 0)
				p_start = i;
			p_index++;
		}
		if (input[i] == ')' && !in_quotes[S_QUOTE] && !in_quotes[D_QUOTE])
			break;
	}
	if (p_start == 0 && input[0] != '(')
		return (NULL);
	return (ft_substr(input, p_start + 1, i - p_start - 1));
}



void	handle_input(char *input, int depth)
{
	debug("INPUT", "Received: `%s`", input);
	if (!is_valid_input(input))
		return;
	debug("INPUT", "Valid: `%s`", input);

	int i = get_open_chr_index(input, '(', ')', depth);
	while (i >= 0)
	{
		handle_input(ft_substr(input, i, get_close_chr_index(input, '(', ')', depth) - i), depth + 1);
	}

	char *sub = get_sub_command(input);
	if (sub)
	{
		debug("CMD", "Sub command find: `%s`", sub);
		handle_input(sub, depth + 1);
	}
}





void	handle_cmd()
{





}
















int	main(void)
{
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
		printf("OPEN PARENTHESE DEPTH 1 index: %d\n", get_open_chr_index(msg, '(', ')', 1));
		printf("CLOSE PARENTHESE DEPTH 1 index: %d\n", get_close_chr_index(msg, '(', ')', 1));
		printf("OPEN PARENTHESE DEPTH 2 index: %d\n", get_open_chr_index(msg, '(', ')', 2));
		printf("CLOSE PARENTHESE DEPTH 2 index: %d\n", get_close_chr_index(msg, '(', ')', 2));
		// handle_input(msg, 0);
		free(msg);
	}
	return (0);
}

/**
char *get_sub_command_old(char *input)
{
	int		i;
	bool	in_quotes[2];
	int		p_index;
	int		p_start;

	i = -1;
	p_index = 0;
	p_start = 0;
	ft_bzero(in_quotes, sizeof(bool) * 2);
	while (input[++i])
	{
		if (input[i] == '\'' && !in_quotes[D_QUOTE])
			in_quotes[S_QUOTE] = !in_quotes[S_QUOTE];
		if (input[i] == '"' && !in_quotes[S_QUOTE])
			in_quotes[D_QUOTE] = !in_quotes[D_QUOTE];
		if (input[i] == '(' && !in_quotes[S_QUOTE] && !in_quotes[D_QUOTE])
		{
			if (p_start == 0)
				p_start = i;
			p_index++;
		}
		if (input[i] == ')' && !in_quotes[S_QUOTE] && !in_quotes[D_QUOTE])
			break;
	}
	if (p_start == 0 && input[0] != '(')
		return (NULL);
	return (ft_substr(input, p_start + 1, i - p_start - 1));
}
 */

/**
char	*get_str_between(char *msg, char start_chr, char end_chr)
{
	int in_quotes = false;

	int i;
	int j;

	i = 0;
	while ((msg[i] && msg[i] != start_chr) || in_quotes)
	{
		if (isquote(msg[i]))
			in_quotes = !in_quotes;
		i++;
	}

	j = 0;
	while ((msg[i + j] && msg[i + j] != end_chr) || in_quotes)
	{
		if (isquote(msg[i + j]))
			in_quotes = !in_quotes;
		j++;
	}

	// debug("DEBUG", "start: `%c` - end: `%c`\n", msg[start], msg[end]);
	if (msg[i] == start_chr && msg[i + j] == end_chr)
		return ft_substr(msg, i + 1, i + j - 1);
	return (ft_strdup("sale merde"));
}
*/
