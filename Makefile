# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/28 07:18:15 by iel-mach          #+#    #+#              #
#    Updated: 2022/03/09 11:36:37 by iel-mach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
FLAGS = -Wall -Wextra -Werror
SRCS = ft_utils_philo.c philo.c ft_routine.c


all : $(NAME)

$(NAME) : $(SRCS)
	@gcc $(FLAGS) $(SRCS) -o $(NAME)
	@echo "✅✅✅"

clean :
	@rm -f $(NAME)
	@echo "🗑️ 🗑️ 🗑️"

fclean : clean

re : fclean all