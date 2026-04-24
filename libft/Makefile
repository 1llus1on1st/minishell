#Name of the compiled application
NAME				=	libft.a

#Compiler used
CC					=	cc
#Flags used
CFLAGS				=	-Wall -Wextra -Werror
#Archiver used
AR					=	ar
# Archiver flags
ARFLAGS				=	rcs
# Removing command
RM					=	rm -rf

#Name of all the source files that need to be compiled
SRC					=	\
						ft_atoi \
						ft_atol \
						ft_bzero \
						ft_calloc \
						ft_isalnum \
						ft_isalpha \
						ft_isascii \
						ft_isdigit \
						ft_isprint \
						ft_itoa \
						ft_memchr \
						ft_memcmp \
						ft_memcpy \
						ft_memmove \
						ft_memset \
						ft_putchar_fd \
						ft_putendl_fd \
						ft_putnbr_fd \
						ft_putstr_fd \
						ft_split \
						ft_strchr \
						ft_strdup \
						ft_striteri \
						ft_strjoin \
						ft_strlcat \
						ft_strlcpy \
						ft_strlen \
						ft_strmapi \
						ft_strncmp \
						ft_strnstr \
						ft_strrchr \
						ft_strtrim \
						ft_substr \
						ft_tolower \
						ft_toupper \
						\
						ft_printf \
						\
						check \
						ft_htoa \
						ft_uitoa \
						ft_puthex \
						print_char_to_integer \
						print_hex_to_percent \
						\
						ft_lstadd_back_bonus \
						ft_lstadd_front_bonus \
						ft_lstclear_bonus \
						ft_lstdelone_bonus \
						ft_lstiter_bonus \
						ft_lstlast_bonus \
						ft_lstnew_bonus \
						ft_lstsize_bonus \
						ft_lstmap_bonus
SRCS				=	$(addsuffix .c, $(SRC))

#Name of all the object files (files containing compiled object code) preceded by the source directory
OBJ_DIR				=	obj
OBJS				=	$(SRCS:%.c=$(OBJ_DIR)/%.o)

#Rule to turn source files into object files used in the OBJS name.
#The -c flag tells the C compiler to compile only and skip linking
#The $< is replaced with the name of the corresponding .c file
#The -o flag specifies the output file that follows
#the $@ is replaced by the name of the output file
$(OBJ_DIR)/%.o:			%.c
						$(CC) $(CFLAGS) -c $< -o $@

#Default action when "make" is run
#1.Runs the NAME rule (compiles all source files into object files, then links them all together and compiles the full application)
all: 					$(NAME)

#Creates an archive using ar with the flags rcs (replace files / create archive / write an index for the archive)
$(NAME):				$(OBJ_DIR) $(OBJS)
						$(AR) $(ARFLAGS) $(NAME) $(OBJS)

#Creates object file directory
$(OBJ_DIR):
						mkdir -p $(OBJ_DIR)

#Removes all object files
clean:
						$(RM) $(OBJ_DIR)

#Removes all object files + the compiled application
fclean: 				clean
						$(RM) $(NAME)

#Rule for rebuilding the project from scratch i.e. remove all object files and compiled application before recompilling everything
re:						fclean all

#List of targets which are not files but are actions performable by Makefile e.g. prevents issues if there is a file called "all"
.PHONY:					all clean fclean re