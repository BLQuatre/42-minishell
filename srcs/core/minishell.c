/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:56:12 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/15 07:45:36 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "holylib.h"

// char	*get_str_between(char *msg, char start_chr, char end_chr)
// {
// 	int in_quotes = false;

// 	int i;
// 	int j;

// 	i = 0;
// 	while ((msg[i] && msg[i] != start_chr) || in_quotes)
// 	{
// 		if (isquote(msg[i]))
// 			in_quotes = !in_quotes;
// 		i++;
// 	}

// 	j = 0;
// 	while ((msg[i + j] && msg[i + j] != end_chr) || in_quotes)
// 	{
// 		if (isquote(msg[i + j]))
// 			in_quotes = !in_quotes;
// 		j++;
// 	}

// 	// printf("start: `%c` - end: `%c`\n", msg[start], msg[end]);
// 	if (msg[i] == start_chr && msg[i + j] == end_chr)
// 		return ft_substr(msg, i + 1, i + j - 1);
// 	return (ft_strdup("sale merde"));
// }






char *get_sub_command(char *input)
{
	int i = 0;
	int in_quotes[2];
	int parentheses_index = 0;
	int parenthese_start = 0;

	ft_bzero(in_quotes, sizeof(bool) * 2);
	while (input[i])
	{
		printf("input[%d] = `%c`\n", i, input[i]);
		if (input[i] == '\'' && !in_quotes[D_QUOTE])
			in_quotes[S_QUOTE] = !in_quotes[S_QUOTE];
		if (input[i] == '"' && !in_quotes[S_QUOTE])
			in_quotes[D_QUOTE] = !in_quotes[D_QUOTE];
		printf("fuck %d\n", input[i] == '(' && !in_quotes[S_QUOTE] && !in_quotes[D_QUOTE]);
		printf("fuck %d\n", !in_quotes[S_QUOTE]);
		printf("fuck %d\n", !in_quotes[D_QUOTE]);
		if (input[i] == '(' && !in_quotes[S_QUOTE] && !in_quotes[D_QUOTE])
		{
			printf("paaaaaa %d\n", parenthese_start);
			if (parenthese_start == 0)
			{
				parenthese_start = i;
				printf("new value i: `%d`\n", parenthese_start);
			}
			parentheses_index++;
		}
		if (input[i] == ')' && !in_quotes[S_QUOTE] && !in_quotes[D_QUOTE])
		{
			parentheses_index--;
			if (parentheses_index == 0)
				break;
		}
		i++;
	}

	printf("%d %d\n", parenthese_start, i);
	return (NULL);
}







void	handle_input(char *msg)
{
	if (!is_valid_input(msg))
		return;
	printf("[DEBUG] [GOOD] readline: `%s`\n", msg);
	char *sub = get_sub_command(msg);
	if (sub)
		handle_input(sub);
}

int	main(void)
{
	char	*msg;

	// t_cmd	*cmd;
	// cmd = cmd_lstnew();
	// show_cmd(cmd);

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
		printf("[DEBUG] readline: `%s`\n", msg);
		handle_input(msg);
		// printf("Between: `%s`\n", get_str_between(msg, '(', ')'));
		// handle_input(msg, '"', '"');
		// handle_input(msg, '(', ')');
		free(msg);
	}
	return (0);
}
