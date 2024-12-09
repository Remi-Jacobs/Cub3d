# NAME = cub3d
# CC = cc
# CFLAGS = -I. -I./mlx -I./parsing
# INCLUDE = ./parsing/parsing.h

# MLXFLAGS = -L./mlx -lmlx -L/usr/lib/X11 -lXext -lX11

# MINILIBX = ./mlx/

# SRC_DIR = ./parsing
# OBJ_DIR = obj
# FT_PRINT_DIR = ./comb_libft
# SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
# OBJ_FILES = $(addprefix $(OBJ_DIR)/,$(notdir $(SRC_FILES:.c=.o)))
# LIBFT = $(FT_PRINT_DIR)/libftprintf.a

# GREEN = \033[0;32m
# RED = \033[0;31m
# RESET = \033[0m

# all: $(LIBFT) $(NAME) $(MINILIBX)

# # Compile the main executable
# $(NAME): $(OBJ_FILES) $(LIBFT)
# 	@echo "$(GREEN)Building $(NAME)...$(RESET)"
# 	@$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) $(MLXFLAGS) -o $(NAME)
# 	@echo "$(GREEN)Build successful!$(RESET)"

# # Rule to compile object files from SRC_DIR
# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE) | $(OBJ_DIR)
# 	@echo "$(GREEN)Compiling $<...$(RESET)"
# 	@$(CC) $(CFLAGS) -c $< -o $@

# # Create obj directory if it doesn't exist
# $(OBJ_DIR):
# 	@mkdir -p $(OBJ_DIR)

# # Build the libft.a library in FT_PRINT_DIR
# $(LIBFT):
# 	@echo "$(GREEN)Building libftprintf.a...$(RESET)"
# 	@make -C $(FT_PRINT_DIR)
# 	@make -C $(MINILIBX)

# clean:
# 	@echo "$(RED)Cleaning object files...$(RESET)"
# 	@rm -rf $(OBJ_DIR)
# 	@make -C $(FT_PRINT_DIR) clean  # Clean up libft objects

# fclean: clean
# 	@echo "$(RED)Removing $(NAME) and libft.a...$(RESET)"
# 	@rm -f $(NAME)
# 	@make -C $(FT_PRINT_DIR) fclean

# re: fclean all

# leak: re
# 		valgrind --leak-check=full ./$(NAME) mapping.cub

# .PHONY: all clean fclean re



# NAME = cub3d
# CC = cc
# CFLAGS = -I. -I./mlx -I./parsing -lm -lz 
# INCLUDE = ./parsing/parsing.h

# # Adjust the MLXFLAGS to point to the correct path
# MLXFLAGS = -L./mlx -lmlx -L/usr/lib/X11 -lXext -lX11

# MINILIBX = ./mlx/
# LDFLAGS = -lm

# SRC_DIR = ./parsing
# OBJ_DIR = obj
# FT_PRINT_DIR = ./comb_libft
# SRC_FILES = $(wildcard $(SRC_DIR)/*.c) ./raycaster/src/player.c ./raycaster/src/mainn.c # Include main.c explicitly
# # SRC_FILES = $((foreach dir, $(SRC_DIRS), wildcard $(SRC_DIR)/*.c)) # Include main.c explicitly
# # OBJ_FILES = $(addprefix $(OBJ_DIR)/,$(notdir $(SRC_FILES:.c=.o)))
# OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
 
# LIBFT = $(FT_PRINT_DIR)/libftprintf.a

# GREEN = \033[0;32m
# RED = \033[0;31m
# RESET = \033[0m

# all: $(LIBFT) $(NAME) $(MINILIBX)

# # Compile the main executable
# $(NAME): $(OBJ_FILES) $(LIBFT)
# 	@echo "$(GREEN)Building $(NAME)...$(RESET)"
# 	@$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) $(MLXFLAGS) $(LDFLAGS) -o $(NAME)  # Correct order of linking
# 	@echo "$(GREEN)Build successful!$(RESET)"

# # Rule to compile object files from SRC_DIR
# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE) | $(OBJ_DIR)
# 	@echo "$(GREEN)Compiling $<...$(RESET)"
# 	@$(CC) $(CFLAGS) -c $< -o $@

# # Explicit rule to compile main.c (since it is not in SRC_DIR)
# # $(OBJ_DIR)/main.o: ./main.c
# # 	@echo "$(GREEN)Compiling main.c...$(RESET)"
# # 	@$(CC) $(CFLAGS) -c ./main.c -o $(OBJ_DIR)/main.o

# # Create obj directory if it doesn't exist
# $(OBJ_DIR):
# 	@mkdir -p $(OBJ_DIR)

# # Build the libft.a library in FT_PRINT_DIR
# $(LIBFT):
# 	@echo "$(GREEN)Building libftprintf.a...$(RESET)"
# 	@make -C $(FT_PRINT_DIR)

# clean:
# 	@echo "$(RED)Cleaning object files...$(RESET)"
# 	@rm -rf $(OBJ_DIR)
# 	@make -C $(FT_PRINT_DIR) clean  # Clean up libft objects

# fclean: clean
# 	@echo "$(RED)Removing $(NAME) and libft.a...$(RESET)"
# 	@rm -f $(NAME)
# 	@make -C $(FT_PRINT_DIR) fclean

# re: fclean all

# leak: re
# 		valgrind --leak-check=full ./$(NAME) mapping.cub

# .PHONY: all clean fclean re


# NAME = cub3d
# CC = cc
# CFLAGS = -I. -I./mlx -I./includes -lm -lz 
# INCLUDE = ./includes/parsing.h ./includes/game.h

# # Adjust the MLXFLAGS to point to the correct path
# MLXFLAGS = -L./mlx -lmlx -L/usr/lib/X11 -lXext -lX11

# MINILIBX = ./mlx/
# LDFLAGS = -lm

# SRC_DIR = ./src
# OBJ_DIR = obj
# FT_PRINT_DIR = ./comb_libft
# SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
# # SRC_FILES = $((foreach dir, $(SRC_DIRS), wildcard $(SRC_DIR)/*.c)) # Include main.c explicitly
# # OBJ_FILES = $(addprefix $(OBJ_DIR)/,$(notdir $(SRC_FILES:.c=.o)))
# OBJ_FILES = $(notdir $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
 
# LIBFT = $(FT_PRINT_DIR)/libftprintf.a

# GREEN = \033[0;32m
# RED = \033[0;31m
# RESET = \033[0m

# all: $(LIBFT) $(NAME) $(MINILIBX)

# # Compile the main executable
# $(NAME): $(OBJ_FILES) $(LIBFT)
# 	@echo "$(GREEN)Building $(NAME)...$(RESET)"
# 	@$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) $(MLXFLAGS) $(LDFLAGS) -o $(NAME)  # Correct order of linking
# 	@echo "$(GREEN)Build successful!$(RESET)"

# # Rule to compile object files from SRC_DIR
# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE) | $(OBJ_DIR)
# 	@echo "$(GREEN)Compiling $<...$(RESET)"
# 	@$(CC) $(CFLAGS) -c $< -o $@

# # Explicit rule to compile main.c (since it is not in SRC_DIR)
# # $(OBJ_DIR)/main.o: ./main.c
# # 	@echo "$(GREEN)Compiling main.c...$(RESET)"
# # 	@$(CC) $(CFLAGS) -c ./main.c -o $(OBJ_DIR)/main.o

# # Create obj directory if it doesn't exist
# $(OBJ_DIR):
# 	@mkdir -p $(OBJ_DIR)

# # Build the libft.a library in FT_PRINT_DIR
# $(LIBFT):
# 	@echo "$(GREEN)Building libftprintf.a...$(RESET)"
# 	@make -C $(FT_PRINT_DIR)

# clean:
# 	@echo "$(RED)Cleaning object files...$(RESET)"
# 	@rm -rf $(OBJ_DIR)
# 	@make -C $(FT_PRINT_DIR) clean  # Clean up libft objects

# fclean: clean
# 	@echo "$(RED)Removing $(NAME) and libft.a...$(RESET)"
# 	@rm -f $(NAME)
# 	@make -C $(FT_PRINT_DIR) fclean

# re: fclean all

# leak: re
# 		valgrind --leak-check=full ./$(NAME) mapping.cub

# .PHONY: all clean fclean re

# Program name
NAME = cub3d

# Compiler and flags
CC = cc
# CFLAGS = -Wall -Wextra -Werror -I. -I./mlx -I./includes
CFLAGS = -I. -I./mlx -I./includes
LDFLAGS = -lm -lz

# MinilibX settings
MLXFLAGS = -L./mlx -lmlx -L/usr/lib/X11 -lXext -lX11
MINILIBX = ./mlx/

# Directories
SRC_DIR = ./src
OBJ_DIR = ./obj
FT_PRINT_DIR = ./comb_libft

# Source and object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILES:.c=.o)))

# Libftprintf library
LIBFT = $(FT_PRINT_DIR)/libftprintf.a

# Colors for output
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

# Default target
all: $(LIBFT) $(NAME)

# Build the main executable
$(NAME): $(OBJ_FILES) $(LIBFT)
	@echo "$(GREEN)Building $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) $(MLXFLAGS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)Build successful!$(RESET)"

# Rule to compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(GREEN)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Build the libftprintf library
$(LIBFT):
	@echo "$(GREEN)Building libftprintf.a...$(RESET)"
	@make -C $(FT_PRINT_DIR)

# Clean object files
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make -C $(FT_PRINT_DIR) clean

# Full clean (including executable and library)
fclean: clean
	@echo "$(RED)Removing $(NAME) and libft.a...$(RESET)"
	@rm -f $(NAME)
	@make -C $(FT_PRINT_DIR) fclean

# Rebuild everything
re: fclean all

# Valgrind memory leak check
leak: re
	valgrind --leak-check=full ./$(NAME) mapping.cub

# Phony targets
.PHONY: all clean fclean re leak
