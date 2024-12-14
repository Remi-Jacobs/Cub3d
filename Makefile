NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -I./mlx -I./includes
LDFLAGS = -lm -lz
MLXFLAGS = -L./mlx -lmlx -L/usr/lib/X11 -lXext -lX11
MINILIBX = ./mlx/
SRC_DIR = ./src
OBJ_DIR = ./obj
FT_PRINT_DIR = ./comb_libft
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILES:.c=.o)))
LIBFT = $(FT_PRINT_DIR)/libftprintf.a
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT)
	@echo "$(GREEN)Building $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) $(MLXFLAGS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)Build successful!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(GREEN)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@echo "$(GREEN)Building libftprintf.a...$(RESET)"
	@make -C $(FT_PRINT_DIR)

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make -C $(FT_PRINT_DIR) clean

fclean: clean
	@echo "$(RED)Removing $(NAME) and libft.a...$(RESET)"
	@rm -f $(NAME)
	@make -C $(FT_PRINT_DIR) fclean

re: fclean all

leak: re
	valgrind --leak-check=full ./$(NAME) maps/mapping.cub

val: re
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) maps/mapping.cub

.PHONY: all clean fclean re leak
