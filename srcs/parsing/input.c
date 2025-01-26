/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:26:58 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/26 04:15:22 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// void	handle_input(char *input, t_minishell *mini)
// {
// 	bool	in_quotes[2];
// 	char	andor[3];

// 	if (!is_valid_input(input))
// 		return ;
// 	ft_bzero(in_quotes, sizeof(bool) * 2);
// 	while (*input)
// 	{
// 		andor[0] = 0;
// 		check_quotes(&in_quotes, *input);
// 		if (is_in_quotes(in_quotes))
// 			continue ;
// 		check_quotes(&in_quotes, *input);
// 		while (*input && !is_in_quotes(in_quotes) && (*input == ')'
// 				|| *input == ' ' || ft_strncmp(input, "&&", 2) == 0
// 				|| ft_strncmp(input, "||", 2) == 0))
// 		{
// 			if (ft_strncmp(input, "&&", 2) == 0
// 				|| ft_strncmp(input, "||", 2) == 0)
// 			{
// 				ft_strlcpy(andor, input, 3);
// 				input++;
// 			}
// 			input++;
// 		}
// 		input += handle_cmd(input, mini, andor);
// 	}
// }

static int	process_input(char *input, char *andor, bool *in_quotes)
{
	int	i;

	i = 0;
	while (input[i] && !is_in_quotes(in_quotes) && (input[i] == ')'
			|| input[i] == ' ' || ft_strncmp(input + i, "&&", 2) == 0
			|| ft_strncmp(input + i, "||", 2) == 0))
	{
		if (ft_strncmp(input + i, "&&", 2) == 0
			|| ft_strncmp(input + i, "||", 2) == 0)
		{
			ft_strlcpy(andor, input + i, 3);
			i++;
		}
		i++;
	}
	return (i);
}

/***
 * @param input is freed thus should be malloc'd and
 * not accessed afterward
 */
void	handle_input(char *input, t_minishell *mini)
{
	bool	in_quotes[2];
	char	andor[3];
	char	*input_save ;

	input_save = input ;
	if (!is_valid_input(input))
		return (mini->exit_code = 2, free(input_save));
	ft_bzero(in_quotes, sizeof(bool) * 2);
	while (*input)
	{
		andor[0] = 0;
		check_quotes(&in_quotes, *input);
		if (is_in_quotes(in_quotes))
			continue ;
		input += process_input(input, andor, in_quotes);
		input += handle_cmd(input, mini, andor, input_save);
	}
	free(input_save);
}
