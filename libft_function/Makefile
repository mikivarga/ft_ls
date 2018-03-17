#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvarga <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/06 14:47:57 by mvarga            #+#    #+#              #
#    Updated: 2017/03/11 19:29:33 by mvarga           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libftprintf.a

CFLAGS = -Wall -Wextra -Werror

SOURCE = conversions_c_wc.c\
		conversions_signed_digit.c\
		conversions_str.c\
		conversions_unsigned_digit.c\
		conversions_wstr.c\
		conversions_pointer.c\
		flags.c\
		ft_printf.c\
		get_data_from_va_list.c\
		print.c\
		pr_point.c\
		print_digits.c\

OBJECTS = $(SOURCE:.c=.o)

LIB_DIR = ./libft/

LIB_INC = ./libft/libft.h

HEAD = ft_printf.h

all: $(NAME)

$(NAME): $(OBJECTS) $(LIB_DIR)libft.a
	ar rc $(NAME) $(OBJECTS) $(LIB_DIR)*.o
	ranlib $(NAME)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@ -I $(LIB_DIR) -I $(LIB_INC) -I $(HEAD)

$(LIB_DIR)libft.a:
	make -C $(LIB_DIR)

clean:
	rm -rf $(OBJECTS)
	make clean -C $(LIB_DIR)

fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIB_DIR)

re: fclean all