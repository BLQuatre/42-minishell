# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/25 10:30:46 by cauvray           #+#    #+#              #
#    Updated: 2025/01/18 21:12:09 by anoteris         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell
CC				= cc
CFLAGS			= -Wall -Wextra -Werror
LFLAGS			= -lreadline

LIBFT_URL		= https://github.com/ft-NotArt/0_Libft
LIBFT_DIR		= libft
LIBFT_FILE		= libft.a
LIBFT_LIB		= $(addprefix $(LIBFT_DIR)/, $(LIBFT_FILE))

CORE_FILES		=
PARSER_FILES	=
EXEC_FILES		=
HOLY_LIB_FILES	=	minishell_struct.c									\
\
					cmd_lstadd_back.c cmd_lstlast.c cmd_lstnew.c		\
					cmd_lst_free.c cmd_lstfirst.c cmd_lst_get_nb.c		\
\
					env_lstadd_back.c env_lstlast.c env_lstnew.c		\
					env_copy.c											\
					env_lstget_by_key.c env_lstdel_by_key.c				\
					env_lst_free.c										\
					env_lst_get_nb.c									\
\
					redir_lstadd_back.c redir_lstlast.c redir_lstnew.c	\
					redir_lst_free.c									\
					free_and_exit.c										\
\

SRCS_FILES		= $(CORE_FILES) $(HOLY_LIB_FILES) $(PARSE_FILES) $(EXEC_FILES)

SRCS_DIR		= srcs
OBJS_DIR		= objs
OBJS_FILES		= $(SRCS_FILES:.c=.o)
OBJS			= $(addprefix $(OBJS_DIR)/, $(OBJS_FILES))

INC_DIR			= includes
INC_FLAGS		= -I $(INC_DIR) -I $(LIBFT_DIR)

GREEN			= \033[0;32m
CYAN			= \033[0;36m
RESET			= \033[0m
GRAY			= \033[90m

SUCCESS			= $(GREEN)[SUCCESS]$(RESET)
INFO			= $(CYAN)[INFO]$(RESET)

all: $(NAME)

$(OBJS_DIR):
	@if [ ! -d ./$(OBJS_DIR) ]; then \
		echo "$(INFO) Creating $(OBJS_DIR) directory..."; \
		echo "$(GRAY)mkdir -p $(OBJS_DIR)"; \
		mkdir -p $(OBJS_DIR); \
	fi

$(OBJS_DIR)/%.o: $(SRCS_DIR)/**/%.c | $(OBJS_DIR)
	@echo "$(INFO) Compiling $<...$(GRAY)"
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

lib:
	@if [ -d "./$(LIBFT_DIR)" ]; then \
		echo "$(INFO) Updating $(LIBFT_DIR) with git pull...$(GRAY)"; \
		echo "$(GRAY)cd $(LIBFT_DIR) && git pull"; \
		cd $(LIBFT_DIR) && git pull; \
	else \
		echo "$(INFO) Cloning $(LIBFT_DIR)...$(GRAY)"; \
		echo "$(GRAY)git clone $(LIBFT_URL) $(LIBFT_DIR)"; \
		git clone $(LIBFT_URL) $(LIBFT_DIR); \
	fi
	@echo "$(INFO) Compiling $(LIBFT_DIR)...$(GRAY)"
	@make -C $(LIBFT_DIR)
	@echo "$(SUCCESS) $(LIBFT_DIR) compiled."

$(NAME): lib $(OBJS)
	@echo "$(INFO) Compiling $(NAME)... $(GRAY)"
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) $(LIBFT_LIB) -o $(NAME)
	@echo "$(SUCCESS) $(NAME) compiled."

clean:
	@echo "$(INFO) Removing $(LIBFT_DIR)...$(GRAY)";
	rm -rf $(LIBFT_DIR);
	@echo "$(INFO) Removing $(OBJS_DIR)...$(GRAY)";
	rm -rf $(OBJS_DIR);
	@echo "$(SUCCESS) Objects and libs removed."

fclean: clean
	@echo "$(INFO) Removing $(NAME)...$(GRAY)"
	rm -f $(NAME)
	@echo "$(SUCCESS) $(NAME) removed."

re: fclean all

.PHONY: all lib clean fclean re

# DEBUG
norm:
	@echo "Norminette de $(NAME)..."
	@if norminette --use-gitignore | grep -v "OK!" | grep -q "Error!"; then \
		norminette --use-gitignore | grep -v "OK!" | \
		while read line; do \
			if echo $$line | grep -q "Error!"; then \
				echo "\033[0;31m$$line\033[0m"; \
			else \
				echo "$$line"; \
			fi; \
		done; \
	else \
		echo "\033[0;32mAll files are norminette friendly !\033[0m"; \
	fi

.PHONY: norm
