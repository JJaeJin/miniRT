CC=				cc
CFLAGS=			-Wall -Wextra -Werror -g
NAME=			miniRT

FILES=			parse_color parse_double error init_data main parse_capital parse_small parse parse_vector draw_all draw_img vector_cal1 vector_cal2 vector_cal3 draw_sphere draw_plane draw_cylinder \
				convert_system apply_color hook_kb draw_cylinder_point_1 draw_cylinder_point_2 check_obstacles_1 check_obstacles_2 get_obj_normal
SRCS=			$(addsuffix .c, $(addprefix ./src/, $(FILES)))
OBJS=			$(SRCS:.c=.o)
SRCS_BONUS=		$(EMPTY)
OBJS_BONUS=		$(EMPTY)

HD_FILES=		argument color error vector
HEADER_DIR=		./include
HEADER=			$(addsuffix .h, $(addprefix ./include/, $(HD_FILES)))
HEADER_BONUS=	$(EMPTY)

LIBFT_DIR=		./libft
LIBFT=			make -C ./libft/

RM=				rm -rf

.PHONY: all bonus clean fclean re

all:	LAST_MAKE

LAST_MAKE: $(OBJS) $(HEADER)
	$(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -I $(LIBFT_DIR) -L $(LIBFT_DIR) -lft -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	$(RM) LAST_BONUS
	touch $@

bonus:	LAST_BONUS

LAST_BONUS: $(OBJS_BONUS) $(HEADER_BONUS)
	$(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -I $(LIBFT_DIR) -L $(LIBFT_DIR) -lft -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	$(RM) LAST_MAKE
	touch $@

%.o:	%.c
	$(CC) $(CFLAGS) -I $(LIBFT_DIR) -I $(HEADER_DIR) -c $< -o $@

# ./??????/%.o:	./??????/%.c $(HEADER_BONUS)
# 	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) LAST_MAKE
	$(RM) LAST_BONUS
	$(RM) $(OBJS)
	$(RM) $(OBJS_BONUS)
	$(LIBFT) clean

fclean:	clean
	$(RM) $(NAME)
	$(LIBFT) fclean

re:	fclean all
