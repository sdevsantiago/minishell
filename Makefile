# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/30 20:22:21 by sede-san          #+#    #+#              #
#    Updated: 2025/08/20 22:40:43 by sede-san         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ******************************* Output files ******************************* #

# Executable file name
NAME = minishell

# ************************** Compilation variables *************************** #

# Compiler
CC = cc

# Compilation flags
CFLAGS = -Wall -Wextra -Werror -Wunreachable-code # -Ofast

# Additional headers
HEADERS = -I $(INCLUDE_PATH) -I $(GNL_INCLUDE_PATH) -I $(PRINTF_INCLUDE_PATH) -I $(LIBFT_INCLUDE_PATH)

# Debug flags, execute with DEBUG=1 -> make DEBUG=1
DFLAGS = -g3
ifeq ($(DEBUG), 1)
	CFLAGS += $(DFLAGS)
endif

# Make command with no-print-directory flag
MAKE += --no-print-directory

# ***************************** Style variables ****************************** #

# Define color codes
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RESET = \033[0m # No Color

# Emojis
EMOJI_BROOM = 🧹
EMOJI_CHECK = ✅
EMOJI_CROSS = ❌
EMOJI_WRENCH = 🔧
EMOJI_BOX = 📦

# ****************************** Source files ******************************** #

# Source files path
SRC_PATH = src

# Source files
SRC = \
	$(SRC_PATH)/minishell.c							\
	$(SRC_PATH)/commands/command_utils.c			\
	$(SRC_PATH)/commands/exec.c						\
	$(SRC_PATH)/commands/parse.c					\
	$(SRC_PATH)/features/builtins/builtin_utils.c	\
	$(SRC_PATH)/features/builtins/cd.c				\
	$(SRC_PATH)/features/builtins/echo.c			\
	$(SRC_PATH)/features/builtins/exit.c			\
	$(SRC_PATH)/features/builtins/export.c			\
	$(SRC_PATH)/features/builtins/printenv.c		\
	$(SRC_PATH)/features/builtins/pwd.c				\
	$(SRC_PATH)/features/builtins/unset.c			\
	$(SRC_PATH)/utils/get_hostname.c				\
	$(SRC_PATH)/utils/signals.c

# Include path
INCLUDE_PATH = ./include

# ****************************** Object files ******************************** #

# Object files path
OBJS_PATH = build

# Source files and destination paths
OBJS = $(SRC:$(SRC_PATH)/%.c=$(OBJS_PATH)/%.o)

# Compile as object files
$(OBJS_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)
	@echo "$< compiled"

# ********************************* Rules ************************************ #

# Compile all
all: lib $(NAME)
.PHONY: all

# Compile project
$(NAME): $(OBJS)
	@echo "$(YELLOW)$(EMOJI_BOX) Linking...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)$(EMOJI_CHECK) Linked.$(RESET)"

# Clean object files
clean:
	@echo "$(RED)$(EMOJI_BROOM) Cleaning object files...$(RESET)"
	@rm -rf $(OBJS_PATH)
	@echo "$(GREEN)$(EMOJI_CHECK) Object files cleaned.$(RESET)"
.PHONY: clean

# Clean object files and binaries
fclean: clean
	@echo "$(RED)$(EMOJI_BROOM) Cleaning binaries...$(RESET)"
	@rm -f $(NAME)
	@if [ -d $(LIBFT_PATH) ]; then \
		$(MAKE) -C $(LIBFT_PATH) fclean; \
	fi
	@if [ -d $(GNL_PATH) ]; then \
		$(MAKE) -C $(GNL_PATH) fclean; \
	fi
	@echo "$(GREEN)$(EMOJI_CHECK) Binaries cleaned.$(RESET)"
.PHONY: fclean

# Delete libraries, object files and binaries
update: fclean
	@echo "$(RED)$(EMOJI_BROOM) Removing libraries...$(RESET)"
	@rm -rf $(LIB_PATH)
	@echo "$(GREEN)$(EMOJI_CHECK) Libraries removed.$(RESET)"
	@echo "$(YELLOW)$(EMOJI_WRENCH) Fetching updates...$(RESET)"
	@git pull
	@echo "$(GREEN)$(EMOJI_CHECK) Updated.$(RESET)"
	@echo "$(YELLOW)$(EMOJI_WRENCH) Recompiling...$(RESET)"
	@$(MAKE)
.PHONY: update

# Recompile
re: fclean all
.PHONY: re

# ********************************* Libraries ******************************** #

# Compile libraries
lib:
	@$(MAKE) libft
#	@$(MAKE) ft_printf
	@$(MAKE) get_next_line
.PHONY: lib

# Compile file with libraries
LIBS = -lreadline $(GNL_BIN) $(LIBFT_BIN) # $(PRINTF_BIN)

# Libraries path
LIB_PATH = lib

# ** Libft ** #

LIBFT = Libft
LIBFT_REPO = https://github.com/sdevsantiago/Libft.git
LIBFT_PATH = $(LIB_PATH)/$(LIBFT)
LIBFT_INCLUDE_PATH = $(LIBFT_PATH)
LIBFT_BIN = $(LIBFT_PATH)/libft.a

libft:
	@if [ ! -d $(LIBFT_PATH) ]; then \
		echo "$(YELLOW)$(EMOJI_WRENCH) Cloning $(LIBFT)...$(RESET)"; \
		git clone $(LIBFT_REPO) $(LIBFT_PATH); \
		rm -rf $(LIBFT_PATH)/.git; \
		echo "$(GREEN)$(EMOJI_CHECK) $(LIBFT) cloned...$(RESET)"; \
	fi
	@if [ ! -f $(LIBFT_BIN) ]; then \
		echo "$(YELLOW)$(EMOJI_WRENCH) Compiling $(LIBFT)...$(RESET)"; \
		$(MAKE) -C $(LIBFT_PATH) all bonus clean; \
		echo "$(GREEN)$(EMOJI_CHECK) $(LIBFT) compiled.$(RESET)"; \
	else \
		echo "$(GREEN)$(EMOJI_CHECK) $(LIBFT) already compiled.$(RESET)"; \
	fi
.PHONY: libft

# ** ft_printf ** #

PRINTF = ft_printf
PRINTF_REPO = https://github.com/sdevsantiago/ft_printf.git
PRINTF_PATH = $(LIB_PATH)/$(PRINTF)
PRINTF_INCLUDE_PATH = $(PRINTF_PATH)
PRINTF_BIN = $(PRINTF_PATH)/libftprintf.a

ft_printf:
	@if [ ! -d $(PRINTF_PATH) ]; then \
		echo "$(YELLOW)$(EMOJI_WRENCH) Cloning $(PRINTF)...$(RESET)"; \
		git clone $(PRINTF_REPO) $(PRINTF_PATH); \
		rm -rf $(PRINTF_PATH)/.git; \
		echo "$(GREEN)$(EMOJI_CHECK) $(PRINTF) cloned...$(RESET)"; \
	fi
	@if [ ! -f $(PRINTF_BIN) ]; then \
		echo "$(YELLOW)$(EMOJI_WRENCH) Compiling $(PRINTF)...$(RESET)"; \
		$(MAKE) -C $(PRINTF_PATH) all bonus clean; \
		echo "$(GREEN)$(EMOJI_CHECK) $(PRINTF) compiled.$(RESET)"; \
	else \
		echo "$(GREEN)$(EMOJI_CHECK) $(PRINTF) already compiled.$(RESET)"; \
	fi
.PHONY: ft_printf

# ** get_next_line ** #

GNL = get_next_line
GNL_REPO = https://github.com/sdevsantiago/get_next_line.git
GNL_PATH = $(LIB_PATH)/$(GNL)
GNL_INCLUDE_PATH = $(GNL_PATH)/include
GNL_BIN = $(GNL_PATH)/get_next_line.a

get_next_line:
	@if [ ! -d $(GNL_PATH) ]; then \
		echo "$(YELLOW)$(EMOJI_WRENCH) Cloning $(GNL)...$(RESET)"; \
		git clone $(GNL_REPO) $(GNL_PATH); \
		rm -rf $(GNL_PATH)/.git; \
		rm -rf $(GNL_PATH)/tests; \
		echo "$(GREEN)$(EMOJI_CHECK) $(GNL) cloned...$(RESET)"; \
	fi
	@if [ ! -f $(GNL_BIN) ]; then \
		echo "$(YELLOW)$(EMOJI_WRENCH) Compiling $(GNL)...$(RESET)"; \
		$(MAKE) -C $(GNL_PATH) all clean; \
		echo "$(GREEN)$(EMOJI_CHECK) $(GNL) compiled.$(RESET)"; \
	else \
		echo "$(GREEN)$(EMOJI_CHECK) $(GNL) already compiled.$(RESET)"; \
	fi
.PHONY: get_next_line
