/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:56:12 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/15 06:50:44 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "holylib.h"

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

	// printf("start: `%c` - end: `%c`\n", msg[start], msg[end]);
	if (msg[i] == start_chr && msg[i + j] == end_chr)
		return ft_substr(msg, i + 1, i + j - 1);
	return (ft_strdup("sale merde"));
}



// void	handle_input(char *msg, char start_chr, char end_chr)
// {
// 	int quotes;


// 	quotes = 0;

// 	int i;

// 	int j;


// 	char *test = NULL;

// 	i = 0;
// 	while (msg[i])
// 	{
// 		j = 1;
// 		if (msg[i] == start_chr && !quotes)
// 		{
// 			quotes = !quotes;
// 			while (msg[i + j] && msg[i + j] != end_chr)
// 				j++;
// 			if (msg[i + j] == end_chr)
// 				test = ft_substr(msg, i, i + j + 1);
// 			else
// 				printf("PROBLEM QUOTES\n");
// 		}
// 		i++;
// 	}
// 	if (test)
// 		printf("Test quotes value: `%s`\n", test);

// 	free(test);
// }

void	handle_input(char *msg)
{
	if (!is_valid_input(msg))
		return;
	printf("[DEBUG] [GOOD] readline: `%s`\n", msg);
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
