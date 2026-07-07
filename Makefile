NAME			=	minishell

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -I $(HEADER_DIR) -I $(LIBFT_DIR)
RM				=	rm -rf

SRC_DIR			=	src

SRC				=	\
					main/main.c \
					main/shell_init.c \
					main/shell.c \
					garbage_collector/garbage_collector.c \
					lexer/lexer.c \
					lexer/lexer_utils.c \
					lexer/lexer_word.c \
					parser/parser.c \
					parser/parser_utils.c \
					parser/parser_redir.c \
					parser/parser_debug.c \
					signals/signals.c \
					env/env_init.c \
					env/env_utils.c \
					env/env_mutation.c \
					env/env_identifier.c \
					expand/expand.c \
					expand/expand_string.c \
					expand/expand_utils.c \
					expand/expand_var.c \
					expand/expand_heredoc.c \
					expand/quote_utils.c \
					builtins/builtins.c \
					builtins/builtin_echo.c \
					builtins/builtin_pwd.c \
					builtins/builtin_env.c \
					builtins/builtin_exit.c \
					builtins/builtin_exit_parse.c \
					builtins/builtin_cd.c \
					builtins/builtin_export.c \
					builtins/builtin_export_print.c \
					builtins/builtin_unset.c \
					exec/exec.c \
					exec/exec_path.c \
					exec/exec_redir.c \
					exec/exec_stdio.c \
					exec/exec_pipeline.c \
					exec/exec_pipeline_child.c \
					exec/exec_heredoc.c \
					exec/exec_heredoc_file.c \
					utils/free_split.c \


SRCS			=	$(addprefix $(SRC_DIR)/, $(SRC))

HEADER_DIR		=	includes
HEADERS			=	$(wildcard $(HEADER_DIR)/*.h)

OBJ_DIR			=	obj
OBJS			=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

LIBFT_DIR		=	./libft
LIBFT			=	$(LIBFT_DIR)/libft.a

READLINE		=	-lreadline

# **************************************************************************** #

all:			$(NAME)

$(NAME):		$(LIBFT) $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(READLINE)

# **************************************************************************** #

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(HEADERS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR) all

# **************************************************************************** #

clean:
	make -C $(LIBFT_DIR) clean
	$(RM) $(OBJ_DIR)

fclean:			clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
