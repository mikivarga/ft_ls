#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvarga <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/06 14:47:57 by mvarga            #+#    #+#              #
#    Updated: 2017/04/10 19:00:43 by mvarga           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_ls

CFLAGS = -Wall -Wextra -Werror

SOURCE = ft_check_ls.c\
		ft_delete_tree.c\
		ft_error.c\
		ft_ls_display.c\
		ft_ls_show.c\
		ft_save_ls.c\
		ft_tree_add_item.c\
		ft_tree_in_order.c\
		ft_tree1.c\
		main.c\

OBJECTS = $(SOURCE:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@make -C ./libft_function
	@gcc -o $(NAME) $(CFLAGS) $(SOURCE) ./libft_function/libftprintf.a ./libft_function/libft/libft.a -I ft_ls.h

%.o: ./%.c
	@gcc $(CFLAGS) -o $@ -c $< -I ft_ls.h

clean:
	@ make clean -C ./libft_function
	@ $(RM) $(OBJECTS)

fclean: clean
	@ $(RM) $(OBJ) $(NAME)
	@ make fclean -C ./libft_function

re: fclean all