# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daumis <daumis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/02 14:26:36 by daumis            #+#    #+#              #
#    Updated: 2023/09/27 18:33:03 by daumis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_MAIN		=	src/main.c \
					src/ft_signal.c \
					src/ft_signal_c.c \
					src/ft_tkn.c \
					src/ft_cmd.c \
					src/ft_quote.c \
					src/ft_exec.c \
					src/ft_exec_rdct.c \
					src/ft_core.c \
					src/utils/ft_checkstat.c \
					src/utils/ft_cmd_utils.c \
					src/utils/ft_exec_hrdc.c \
					src/utils/ft_exec_utils_bis.c \
					src/utils/ft_exec_utils.c \
					src/utils/ft_free.c \
					src/utils/ft_itoa.c \
					src/utils/ft_split.c \
					src/utils/ft_tkn_utils.c \
					src/utils/ft_utils_bis.c \
					src/utils/ft_utils.c \
					src/utils/ft_var_utils.c \
					src/utils/ft_xpnd_quote.c \
					src/utils/ft_xpnd_utils_bis.c \
					src/utils/ft_xpnd_utils.c \
					src/builtins/ft_cd.c \
					src/builtins/ft_echo.c \
					src/builtins/ft_env.c \
					src/builtins/ft_exit.c \
					src/builtins/ft_export.c \
					src/builtins/ft_pwd.c \
					src/builtins/ft_unset.c \
					src/ft_printf/ft_handlehex.c \
					src/ft_printf/ft_handlei.c \
					src/ft_printf/ft_handleu.c \
					src/ft_printf/ft_printf.c \
					src/ft_printf/ft_putchar.c \
					src/ft_printf/ft_putstr.c \

SRCS        = ${SRC_MAIN}
OBJ_DIR     = objs
OBJS        = $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(SRCS))

CC          = cc
RM          = rm -f
CFLAGS      = -Wall -Wextra -Werror -g3
LIBS        = -lreadline

NAME        = minishell

all: $(OBJ_DIR) $(OBJS) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	@printf '\033[A\033[19C'"⌛ [\e[1;96mCompiling\033[0m]\033[35m $<\033[0m \n"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) -o $(NAME) $(LIBS)
	@printf '\033[A\033[20C'"\033[32;1m  ✅ Project has compiled successfully!          \033[0m"
	@printf "\n\n    [🏳️ FLAGS: \033[0;35m$(CFLAGS)\033[0m]"
	@echo "\033[32;1m\n 💾 Executable \e[7m./$(NAME)\e[27m has been created in: \n    └─ 📂 \033[4;36m ~ $(PWD)\033[0m"

clean:
	$(RM) -r $(OBJ_DIR)

fclean:
	@echo "\033[1;93m\n                        [Cleaning directories with \033[0;96mfclean\033[1;93m]\n\033[0m"
	@make clean
	$(RM) $(NAME)

re:
	@make fclean
	@echo "\033[1;93m\n                             [Calling \033[0;96mmake all\033[1;93m rule]\n\n\033[0m"
	@make -s all

.PHONY: all clean fclean re
