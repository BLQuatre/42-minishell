/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:32:27 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/15 05:54:13 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdbool.h>
# include "libft.h"
# include "minishell.h"

# define INVALID_TOKEN "😂 invalid token ! %s\n"

typedef enum e_quote_type
{
	S_QUOTE,
	D_QUOTE
}	t_quote_type;

bool	is_valid_input(char *input);


//*** DEBUG */
void	show_cmd(t_cmd *cmd);

#endif