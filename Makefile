# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/20 11:45:24 by abelfany          #+#    #+#              #https://www.youtube.com/watch?v=pW-4JUCTBtg
#    Updated: 2023/07/18 15:13:22 by abelfany         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER = minishell.h
NAME = minishell
LIB = ../libft

SRC = minishell.c \
		ft_strcpy.c \
		flager.c \
		helpers_functions.c \
		 ft_split.c ./commands/export.c ./commands/unset.c\
		exec_tools.c ft_strjoin.c init.c env.c ft_atoi.c exec_cmd.c\
	 	./commands/cd.c ./commands/pwd.c  ./commands/echo.c check_cmd.c\
	 	tools.c ./commands/exit.c ./commands/env.c pipes.c  pipe_exec.c pipe_close.c\

S_OBJ = $(SRC:.c=.o)
C_FLAG = -Wall -Wextra -Werror -fsanitize=address
RM = @rm -rf

all: $(NAME)

$(NAME):$(S_OBJ)
	cc $(C_FLAG) -lreadline -lreadline -L$(shell brew --prefix readline)/lib $(S_OBJ) -o $(NAME)
	
%.o : %.c $(HEADER)
	cc $(C_FLAG) -I$(shell brew --prefix readline)/include -c $< -I $(HEADER) -o $@
	
clean :
	$(RM) $(S_OBJ) 

fclean : clean
	$(RM) $(NAME)

re : fclean all 

.PHONY : all fclean clean re

