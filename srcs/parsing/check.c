/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 05:17:23 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/24 17:57:11 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// TODO: Put error on stderr

static int	is_valid_parentheses(char *input)
{
	int		i;
	int		count;
	bool	in_quotes[2];

	i = -1;
	count = 0;
	ft_bzero(in_quotes, sizeof(bool) * 2);
	while (input[++i])
	{
		if (input[i] == '\'' && !in_quotes[D_QUOTE])
			in_quotes[S_QUOTE] = !in_quotes[S_QUOTE];
		if (input[i] == '"' && !in_quotes[S_QUOTE])
			in_quotes[D_QUOTE] = !in_quotes[D_QUOTE];
		if (input[i] == '(' && !in_quotes[S_QUOTE] && !in_quotes[D_QUOTE])
			count++;
		if (input[i] == ')' && !in_quotes[S_QUOTE] && !in_quotes[D_QUOTE])
			count--;
		if (count < 0)
			break ;
	}
	return (count);
}

static bool	is_arg_after_redir(char *input)
{
	int		i;
	bool	in_quotes[2];

	i = -1;
	if (ft_strncmp(input, ">>", 2) == 0 || ft_strncmp(input, "<<", 2) == 0)
		i += 2;
	else
		i++;
	ft_bzero(in_quotes, sizeof(bool) * 2);
	while (input[++i])
	{
		check_quotes(&in_quotes, input[i]);
		if (input[i] && (in_quotes[S_QUOTE] || in_quotes[D_QUOTE]))
			continue ;
		while (input[i] && input[i] == ' ')
			i++;
		if (input[i] != '|' && input[i] != '&'
			&& input[i] != '<' && input[i] != '>')
			return (true);
		return (false);
	}
	return (true);
}

static bool	is_valid_redir(char *input)
{
	int		i;
	bool	in_quotes[2];

	i = -1;
	ft_bzero(in_quotes, sizeof(bool) * 2);
	while (input[++i])
	{
		check_quotes(&in_quotes, input[i]);
		if (input[i] && (in_quotes[S_QUOTE] || in_quotes[D_QUOTE]))
			continue ;
		if (input[i] == '>' || input[i] == '<'
			|| ft_strncmp(input + i, ">>", 2) == 0
			|| ft_strncmp(input + i, "<<", 2) == 0)
		{
			if (!is_arg_after_redir(input + i))
			{
				return (printf(INVALID_TOKEN, ": redir"), false);
			}
		}
	}
	return (true);
}

static bool	is_valid_pipe(char *input)
{
	int		i;
	bool	in_quotes[2];
	bool	pipe_flag;

	i = -1;
	pipe_flag = false;
	ft_bzero(in_quotes, sizeof(bool) * 2);
	while (input[++i])
	{
		check_quotes(&in_quotes, input[i]);
		if (in_quotes[S_QUOTE] || in_quotes[D_QUOTE])
			continue ;
		if (input[i] == '|' && input[i + 1] != '|' && !pipe_flag)
		{
			if (!input[i + 1])
				return (printf(INVALID_TOKEN, ": pipe"), false);
			pipe_flag = true;
			continue;
		}
		if (input[i] == ' ' && pipe_flag)
		{
			if (!input[i + 1])
				return (printf(INVALID_TOKEN, ": pipe"), false);
			continue;
		}
		if (pipe_flag && (input[i] == '&' || input[i] == '|'))
			return (printf(INVALID_TOKEN, ": pipe"), false);
		pipe_flag = false;
	}
	return (true);
}

static bool	is_valid_quote(char *input, t_quote_type quote_type)
{
	int		i;
	bool	in_quotes[2];

	i = -1;
	ft_bzero(in_quotes, sizeof(bool) * 2);
	while (input[++i])
		check_quotes(&in_quotes, input[i]);
	return (!in_quotes[quote_type]);
}

// TODO: Put error on stderr
bool	is_valid_input(char *input)
{
	int	parentheses_result;

	parentheses_result = is_valid_parentheses(input);
	if (parentheses_result > 0)
		return (printf(INVALID_TOKEN, " \"(\""), false);
	else if (parentheses_result < 0)
		return (printf(INVALID_TOKEN, " \")\""), false);
	if (!is_valid_quote(input, S_QUOTE))
		return (printf(INVALID_TOKEN, " \"'\""), false);
	if (!is_valid_quote(input, D_QUOTE))
		return (printf(INVALID_TOKEN, " '\"'"), false);
	if (!is_valid_redir(input))
		return (false);
	if (!is_valid_pipe(input))
		return (false);
	return (true);
}
