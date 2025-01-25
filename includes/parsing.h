/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:32:27 by cauvray           #+#    #+#             */
/*   Updated: 2025/01/25 23:49:05 by cauvray          ###   ########.fr       */
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

/*** CMD */
int		handle_cmd(char *input, t_minishell *mini, char andor[3]);
t_cmd	*parse_cmd(char *input, t_minishell *mini);

/*** PIPE */
t_cmd	*handle_pipe(char *input, t_minishell *mini);

/*** SUBSHELL */
char	*parse_subshell(char *input, int *len);

/*** ARG */
char	*parse_arg(char *input, int *len, bool *subshell);

/*** REDIR */
t_redir	*parse_redir(char *input, int *len);

/*** ENV */
// UTILS
bool	is_valid_env_char(char c);
int		get_env_len(char *input);
int		process_env_len(char **input, t_env *env, bool s_quote);
int		get_buffer_size_env(char *input, t_minishell *mini);
// PROCESS
int		proccess_env_var(char **input, char *res, t_env *env);
int		process_env_exit_code(char **input, char *res, int exit_code);
// HANDLER
void	handle_env(t_cmd *cmd, t_minishell *mini);

/*** WILDCARD */
void	handle_wildcard(t_cmd *cmd);

/*** QUOTES */
// UTILS
void	check_quotes(bool (*in_quotes)[2], char curr_chr);
bool	is_in_quotes(bool in_quotes[2]);
// HANDLER
void	handle_quotes(t_cmd *cmd);

/*** CHECK */
void	print_token_error(char token);
bool	is_valid_input(char *input);
bool	is_valid_andor(char	*input);
bool	is_valid_parentheses(char *input);
bool	is_valid_pipe(char *input);
bool	is_valid_redir(char *input);
bool	is_valid_quote(char *input, t_quote_type quote_type);

/*** PARENTHESES */
int		calc_parentheses_depth(int actual_depth, bool in_quotes[2], char c);

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
