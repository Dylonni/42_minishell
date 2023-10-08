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

SRCS			= ${SRC_MAIN}

LIBFT_DIR		= libft/
OBJ				= $(SRCS:.c=.o)

CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -g3
LIBS			= -lreadline

NAME            = minishell

all:			$(NAME)

$(NAME):		$(OBJ)
				@echo "\033[1;35m\n                              ⌛️Compiling files...\033[0m"
				$(CC) $(OBJ) $(CFLAGS) -o $(NAME) $(LIBS)
				@echo "\033[32;1m\n                     Project has compiled successfully! ✅ \033[0m"
				@echo "\033[32;1m\n 💾 Executable './$(NAME)' has been created in: \n    └─ 📂 \033[4;36m ~ $(PWD)\033[0m"

clean:
	$(RM) $(OBJ)

fclean:
	@echo "\033[1;33m\n                        [Cleaning directories with \033[0;36mfclean\033[1;33m]\n\033[0m"
	@make clean
	$(RM) $(NAME)

re:	
	@make fclean
	@echo "\033[1;33m\n                            [Calling \033[0;36mmake all\033[1;33m rule]\n\033[0m"
	@make -s all

.PHONY:	all clean fclean re