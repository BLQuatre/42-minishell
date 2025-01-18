/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:32:27 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/17 12:38:37 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdbool.h>
# include "libft.h"
# include "minishell.h"
# include "holylib.h"

//*** MESSAGES */
# define INVALID_TOKEN "😂 invalid token ! %s\n"

# define QUOTES_BOOL_SIZE sizeof(bool) * 2

typedef enum e_quote_type
{
	S_QUOTE,
	D_QUOTE
}	t_quote_type;

void	check_quotes(bool (*in_quotes)[2], char curr_chr);
bool	is_in_quotes(bool in_quotes[2]);
int get_close_par_index(char *input);
bool	is_valid_input(char *input);
int	handle_parentheses(char *input);
void	handle_input(char *input);

//*** DEBUG */
typedef enum e_color
{
	BLACK,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE,
	BRIGHT_BLACK,
	BRIGHT_RED,
	BRIGHT_GREEN,
	BRIGHT_YELLOW,
	BRIGHT_BLUE,
	BRIGHT_MAGENTA,
	BRIGHT_CYAN,
	BRIGHT_WHITE
}	t_color;

void	debug(const char *tag, t_color color, const char *format, ...);
void	show_cmd(t_cmd *cmd);

#endif
