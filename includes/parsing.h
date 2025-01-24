/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:32:27 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/24 04:41:11 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "minishell.h"
# include "holylib.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdbool.h>

typedef enum e_quote_type
{
	S_QUOTE,
	D_QUOTE
}	t_quote_type;

/*** INPUT */
void	handle_input(char *input, t_minishell *mini);

// TODO: Rename
/*** CHECK */
bool	is_valid_input(char *input);

/*** ARG */
char	*parse_arg(char *input, int *len, bool *subshell);

/*** CMD */
int		handle_cmd(char *input, t_minishell *mini, char andor[3]);
t_cmd	*parse_cmd(char *input, t_minishell *mini);

/*** PIPE */
t_cmd	*handle_pipe(char *input, t_minishell *mini);

/*** SUBSHELL */
char	*parse_subshell(char *input, int *len);
/**
 * @param input The input must start with open parenthese
 * @return how many chars skipped before close parenthese
 */
int		handle_subshell(char *input, t_minishell *mini);

/*** QUOTES */
void	check_quotes(bool (*in_quotes)[2], char curr_chr);
bool	is_in_quotes(bool in_quotes[2]);
void	handle_quotes(t_cmd *cmd);

/*** REDIR */
t_redir	*parse_redir(char *input, int *len);

/*** ENV */
void	handle_env(t_cmd *cmd, t_minishell *mini);

/*** WILDCARD */
void	handle_wildcard(t_cmd *cmd);

/*** DEBUG */
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
void	debug_show_cmd(t_cmd *cmd);

#endif
