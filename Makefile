NAME = cub3d
CC = cc
CFLAGS = -I.
INCLUDE = ./parsing/parsing.h
SRC_DIR = ./parsing
OBJ_DIR = obj
FT_PRINT_DIR = ./comb_libft
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(addprefix $(OBJ_DIR)/,$(notdir $(SRC_FILES:.c=.o)))
LIBFT = $(FT_PRINT_DIR)/libftprintf.a

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all: $(LIBFT) $(NAME)

# Compile the main executable
$(NAME): $(OBJ_FILES) $(LIBFT)
	@echo "$(GREEN)Building $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) $(LIBFT)
	@echo "$(GREEN)Build successful!$(RESET)"

# Rule to compile object files from SRC_DIR
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE) | $(OBJ_DIR)
	@echo "$(GREEN)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Create obj directory if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Build the libft.a library in FT_PRINT_DIR
$(LIBFT):
	@echo "$(GREEN)Building libftprintf.a...$(RESET)"
	@make -C $(FT_PRINT_DIR)

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make -C $(FT_PRINT_DIR) clean  # Clean up libft objects

fclean: clean
	@echo "$(RED)Removing $(NAME) and libft.a...$(RESET)"
	@rm -f $(NAME)
	@make -C $(FT_PRINT_DIR) fclean

re: fclean all

leak: re
		valgrind --leak-check=full ./$(NAME) mapping.cub

.PHONY: all clean fclean re