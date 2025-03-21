# Program name
NAME =			pipex
BONUS_NAME =	pipex_bonus

# Directories
INC_DIR =	inc/
SRC_DIR =	src/
OBJ_DIR =	obj/
LIBFT_DIR =	libft/

# Header files
INC =				$(INC_DIR)pipex.h

# Source files
SRC = \
					$(SRC_DIR)exec/exec_ast_utils.c \
					$(SRC_DIR)exec/exec_ast.c \
					$(SRC_DIR)exec/exec_command_setup_redir.c \
					$(SRC_DIR)exec/exec_command.c \
					$(SRC_DIR)exec/exec_pipe.c \
					$(SRC_DIR)exec/executable_path_utils.c \
					$(SRC_DIR)exec/executable_path.c \
					$(SRC_DIR)here_doc/cmp_limiter.c \
					$(SRC_DIR)here_doc/expand_var_here_doc.c \
					$(SRC_DIR)here_doc/parse_limiter.c \
					$(SRC_DIR)here_doc/proc_here_doc.c \
					$(SRC_DIR)here_doc/set_here_doc_path.c \
					$(SRC_DIR)here_doc/utils.c \
					$(SRC_DIR)init/check_argc.c \
					$(SRC_DIR)init/init_data.c \
					$(SRC_DIR)init/parse_ast_utils.c \
					$(SRC_DIR)init/parse_ast.c \
					$(SRC_DIR)init/parse_envs.c \
					$(SRC_DIR)utils/envs_utils.c \
					$(SRC_DIR)utils/exit_pipex.c \
					$(SRC_DIR)utils/free_2d_array.c \
					$(SRC_DIR)utils/print_err.c \
					$(SRC_DIR)utils/xmalloc.c
MANDATORY_MAIN =	$(SRC_DIR)main/main.c
BONUS_MAIN =		$(SRC_DIR)main/main_bonus.c

# Generate the list of object files in OBJ_DIR from source files in SRC_DIR
OBJ =				$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))
MANDATORY_OBJ =		$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(MANDATORY_MAIN))
BONUS_OBJ =			$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(BONUS_MAIN))

ifdef BONUS
OBJ += $(BONUS_OBJ)
else
OBJ += $(MANDATORY_OBJ)
endif

# Compile
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_LIB = -L ./libft -lft

# Commands
RM = rm -f
AR = ar rcs

# Build rules
all: $(NAME)

bonus:
	@make $(BONUS_NAME) BONUS=1

$(NAME): $(OBJ)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJ) -I$(INC_DIR) -o $@ $(LIBFT_LIB)

$(BONUS_NAME): $(OBJ)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJ) -I$(INC_DIR) -o $@ $(LIBFT_LIB)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME) $(BONUS_NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re bonus