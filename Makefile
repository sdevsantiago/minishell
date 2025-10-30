# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/30 20:22:21 by sede-san          #+#    #+#              #
#    Updated: 2025/10/28 20:14:44 by sede-san         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ******************************* Output files ******************************* #

NAME	= minishell

# ************************** Compilation variables *************************** #

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
HEADERS	= -I $(INCLUDE_PATH) $(LIBS_INCLUDE)

ifeq ($(DEBUG), lldb) # debug with LLDB
	CFLAGS	+= -g3
else ifeq ($(DEBUG), valgrind) # debug with valgrind
	CFLAGS	+= -g3
else ifeq ($(DEBUG), address) # use AdressSanitize
	CFLAGS	+= -fsanitize=address -g3
else # apply optimization flags if no debugging is being done
	CFLAGS	+= -O3
endif

MAKE	+= --no-print-directory

# ****************************** Source files ******************************** #

SRC_PATH	= src
# SRC			=
SRC			= $(shell find $(SRC_PATH) -type f -name "*.c")

INCLUDE_PATH	= include

# ****************************** Object files ******************************** #

OBJS_PATH	= build
OBJS		= $(SRC:$(SRC_PATH)/%.c=$(OBJS_PATH)/%.o)

$(OBJS_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@$(PRINT) "$< compiled"

# ********************************* Rules ************************************ #

all: mandatory
.PHONY: all

mandatory: libft get_next_line ft_printf $(NAME)
.PHONY: mandatory

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@$(PRINT) "$(GREEN)$(EMOJI_CHECK) $(NAME) ready. $(RESET)"

clean:
	@rm -rf $(OBJS_PATH)
	@$(PRINT) "$(RED)$(EMOJI_BROOM) Object files removed.$(RESET)"
.PHONY: clean

fclean: clean
	@rm -f $(NAME)
	@if [ -d $(LIBFT_PATH) ]; then										\
		$(MAKE) --silent -C $(LIBFT_PATH) fclean > /dev/null;			\
	fi
	@if [ -d $(GET_NEXT_LINE_PATH) ]; then								\
		$(MAKE) --silent -C $(GET_NEXT_LINE_PATH) fclean > /dev/null;	\
	fi
	@$(PRINT) "$(RED)$(EMOJI_BROOM) Binaries removed.$(RESET)"
.PHONY: fclean

re: fclean all
.PHONY: re

# ****************************** Libraries ********************************** #

LIBS			= -lreadline $(LIBFT_NAME) $(GET_NEXT_LINE_NAME) $(FT_PRINTF_NAME)
LIBS_INCLUDE	= -I $(LIBFT_INCLUDE_PATH) -I $(GET_NEXT_LINE_INCLUDE_PATH) -I $(FT_PRINTF_INCLUDE_PATH)
LIBS_PATH		= lib

# ** Libft ** #

LIBFT				= Libft
LIBFT_REPO			= https://github.com/sdevsantiago/Libft.git
LIBFT_PATH			= $(LIBS_PATH)/$(LIBFT)
LIBFT_INCLUDE_PATH	= $(LIBFT_PATH)
LIBFT_NAME			= $(LIBFT_PATH)/libft.a

libft: $(LIBFT_NAME)
.PHONY: libft

$(LIBFT_NAME):
	@if [ ! -d $(LIBFT_PATH) ]; then										\
		$(PRINT) "$(YELLOW)$(EMOJI_WRENCH) Cloning $(LIBFT)...$(RESET)";	\
		git clone --quiet $(LIBFT_REPO) $(LIBFT_PATH);						\
		rm -rf $(LIBFT_PATH)/.git;											\
		$(PRINT) "$(GREEN)$(EMOJI_CHECK) $(LIBFT) cloned...$(RESET)";		\
	fi
	@if [ ! -f $(LIBFT_NAME) ]; then										\
		$(PRINT) "$(YELLOW)$(EMOJI_WRENCH) Compiling $(LIBFT)...$(RESET)";	\
		$(MAKE) --silent -C $(LIBFT_PATH) all clean;						\
		$(PRINT) "$(GREEN)$(EMOJI_CHECK) $(LIBFT) compiled.$(RESET)";		\
	fi

# ** get_next_line **

GET_NEXT_LINE				= get_next_line
GET_NEXT_LINE_REPO			= https://github.com/sdevsantiago/get_next_line.git
GET_NEXT_LINE_PATH			= $(LIBS_PATH)/$(GET_NEXT_LINE)
GET_NEXT_LINE_INCLUDE_PATH	= $(GET_NEXT_LINE_PATH)/include
GET_NEXT_LINE_NAME			= $(GET_NEXT_LINE_PATH)/get_next_line.a

get_next_line: $(GET_NEXT_LINE_NAME)
.PHONY: get_next_line

$(GET_NEXT_LINE_NAME):
	@if [ ! -d $(GET_NEXT_LINE_PATH) ]; then \
		$(PRINT) "$(YELLOW)$(EMOJI_WRENCH) Cloning $(GET_NEXT_LINE)...$(RESET)";	\
		git clone --quiet $(GET_NEXT_LINE_REPO) $(GET_NEXT_LINE_PATH);				\
		rm -rf $(GET_NEXT_LINE_PATH)/.git;											\
		rm -rf $(GET_NEXT_LINE_PATH)/tests;											\
		rm -rf $(GET_NEXT_LINE_PATH)/files;											\
		$(PRINT) "$(GREEN)$(EMOJI_CHECK) $(GET_NEXT_LINE) cloned...$(RESET)";		\
	fi
	@if [ ! -f $(GET_NEXT_LINE_NAME) ]; then \
		$(PRINT) "$(YELLOW)$(EMOJI_WRENCH) Compiling $(GET_NEXT_LINE)...$(RESET)";	\
		$(MAKE) --silent -C $(GET_NEXT_LINE_PATH) all clean > /dev/null; 			\
		$(PRINT) "$(GREEN)$(EMOJI_CHECK) $(GET_NEXT_LINE) compiled.$(RESET)";		\
	fi

# ** ft_printf **

FT_PRINTF				= ft_printf
FT_PRINTF_REPO			= https://github.com/sdevsantiago/ft_printf.git
FT_PRINTF_PATH			= $(LIBS_PATH)/$(FT_PRINTF)
FT_PRINTF_INCLUDE_PATH	= $(FT_PRINTF_PATH)/include
FT_PRINTF_NAME			= $(FT_PRINTF_PATH)/libftprintf.a

ft_printf: $(FT_PRINTF_NAME)
.PHONY: ft_printf

$(FT_PRINTF_NAME):
	@if [ ! -d $(FT_PRINTF_PATH) ]; then \
		$(PRINT) "$(YELLOW)$(EMOJI_WRENCH) Cloning $(FT_PRINTF)...$(RESET)";	\
		git clone --quiet $(FT_PRINTF_REPO) $(FT_PRINTF_PATH);					\
		rm -rf $(FT_PRINTF_PATH)/.git;											\
		$(PRINT) "$(GREEN)$(EMOJI_CHECK) $(FT_PRINTF) cloned...$(RESET)";		\
	fi
	@if [ ! -f $(FT_PRINTF_NAME) ]; then \
		$(PRINT) "$(YELLOW)$(EMOJI_WRENCH) Compiling $(FT_PRINTF)...$(RESET)";				\
		$(MAKE) --silent -C $(FT_PRINTF_PATH) all clean LIBFT_PATH=../$(LIBFT) > /dev/null;	\
		$(PRINT) "$(GREEN)$(EMOJI_CHECK) $(FT_PRINTF) compiled.$(RESET)";					\
	fi

# ***************************** Style variables ****************************** #

PRINT	= printf "%b\n"

RED		= \033[0;31m
GREEN	= \033[0;32m
YELLOW	= \033[0;33m
BLUE	= \033[0;34m
RESET	= \033[0m

EMOJI_BROOM		= 🧹
EMOJI_CHECK		= ✅
EMOJI_CROSS		= ❌
EMOJI_WRENCH	= 🔧
EMOJI_BOX		= 📦
