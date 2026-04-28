NAME			=	minishell

CC				=	cc
# CFLAGS			=	-Wall -Wextra -Werror -I $(HEADER_DIR) -I $(LIBFT_DIR)
CFLAGS			=	-I $(HEADER_DIR) -I $(LIBFT_DIR)
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
					signals/signals.c \

SRCS			=	$(addprefix $(SRC_DIR)/, $(SRC))

HEADER_DIR		=	includes
HEADERS			=	$(HEADER_DIR)/minishell.h

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
