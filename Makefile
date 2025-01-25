# COLORS

BEIGE			=	\x1b[0m\x1b[38;2;213;186;152m
LIGHT_BEIGE		=	\x1b[0m\x1b[38;2;230;214;193m
DARK_BEIGE		=	\x1b[1m\x1b[38;2;149;130;106m

# TARGET

NAME			=	minishell

LIBFT			=	libft.a
LIBFT_DIR		=	libft
LIBFT_PATH		=	$(LIBFT_DIR)/$(LIBFT)

# FLAGS

MAKEFLAGS		+=	-s
CFLAGS			=	-Wall -Werror -Wextra -g									\
					-Iincludes -I$(LIBFT_DIR) -I$(LIBFT_DIR)/gnl
LFLAGS			=	-lreadline

ARFLAGS			=	rcs

# FILES

CORE_FILES		=	minishell													\
					signals														\
					debug														\
\

CORE_SRC		=	$(addprefix core/, $(CORE_FILES))
CORE_OBJ		=	$(addprefix core/, $(CORE_FILES))

HOLY_LIB_FILES	=	minishell_struct											\
\
					cmd_lstnew cmd_lstadd_back									\
					cmd_lstfirst cmd_lstlast cmd_lst_get_nb						\
					cmd_lst_free												\
\
					env_lstnew env_lstadd_back									\
					env_copy env_lst_to_str_array								\
					env_lstlast env_lst_get_nb									\
					env_lstget_by_key env_lstdel_by_key							\
					env_lst_free												\
\
					redir_lstadd_back redir_lstlast redir_lstnew				\
					redir_lst_free												\
					free_and_exit												\
					is_builtin													\
\

HOLY_LIB_SRC	=	$(addprefix holylib/, $(HOLY_LIB_FILES))
HOLY_LIB_OBJ	=	$(addprefix holylib/, $(HOLY_LIB_FILES))

PARSING_FILES	=	input arg cmd											\
					check check_andor check_parentheses						\
					check_pipe check_quotes check_redir						\
					envp env_process env_utils								\
					pipe redir subshell										\
					quotes quotes_utils										\
					wildcard												\
					parentheses												\
\

PARSING_SRC		=	$(addprefix parsing/, $(PARSING_FILES))
PARSING_OBJ		=	$(addprefix parsing/, $(PARSING_FILES))

EXEC_FILES		=	exec														\
					globstar													\
					handle_fd handle_redir										\
					path_to_cmd													\
					exec_error exec_utils										\
\

EXEC_SRC		=	$(addprefix exec/, $(EXEC_FILES))
EXEC_OBJ		=	$(addprefix exec/, $(EXEC_FILES))

BUILT_IN_FILES	=	echo														\
					cd pwd														\
					export unset env											\
					exit														\
					builtins_utils												\
\

BUILT_IN_SRC	=	$(addprefix builtins/, $(BUILT_IN_FILES))
BUILT_IN_OBJ	=	$(addprefix builtins/, $(BUILT_IN_FILES))

FILES			=	$(CORE_SRC) $(HOLY_LIB_SRC) $(PARSING_SRC) $(EXEC_SRC) $(BUILT_IN_SRC)

SRC				=	$(addprefix srcs/, $(addsuffix .c, $(FILES)))
OBJ				=	$(addprefix srcs/, $(addsuffix .o, $(FILES)))

# RULES

all				:	$(NAME)

$(LIBFT_PATH)	:
					$(MAKE) -C $(LIBFT_DIR) $(LIBFT) -j $$(nproc)

$(NAME)			:	$(OBJ) | $(LIBFT_PATH)
					$(CC) $(CFLAGS) $^ $(LIBFT_PATH) $(LFLAGS) -o $@
					echo -e '$(LIGHT_BEIGE) \tCompiled$(DARK_BEIGE) $@'

clean			:
					$(RM) $(OBJ)
					$(MAKE) -C $(LIBFT_DIR) f$@
					echo -e '$(LIGHT_BEIGE) \tCleaned$(BEIGE) $(OBJ)'

fclean			:	clean
					$(RM) $(NAME)
					echo -e '$(LIGHT_BEIGE) \tCleaned$(DARK_BEIGE) $(NAME)'

re				:	fclean all

.PHONY			=	all clean fclean re
