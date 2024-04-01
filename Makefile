CC=					cc
CFLAGS=				-Wall -Wextra -Werror# -g -fsanitize=address
NAME=				miniRT

FILES=				parse_color parse_double error init_data main parse_capital parse_small parse parse_vector draw_all draw_img vector_cal1 vector_cal2 vector_cal3 draw_sphere draw_plane draw_cylinder \
					convert_system apply_color hook_kb draw_cylinder_point_1 draw_cylinder_point_2 check_obstacles_1 check_obstacles_2 get_obj_normal draw_cone draw_cone_point_1 check_obstacles_3\
					get_checkerboard_color get_img_color check_obstacles_4 draw_cone_point_2 draw_cylinder_point_3
SRCS=				$(addsuffix .c, $(addprefix ./src/, $(FILES)))
OBJS=				$(SRCS:.c=.o)
SRCS_BONUS=			$(addsuffix _bonus.c, $(addprefix ./src_bonus/, $(FILES)))
OBJS_BONUS=			$(SRCS_BONUS:.c=.o)

HD_FILES=			argument color error vector
HEADER_DIR=			./include
HEADER_BONUS_DIR=	./include_bonus
HEADER=				$(addsuffix .h, $(addprefix ./include/, $(HD_FILES)))
HEADER_BONUS=		$(addsuffix _bonus.h, $(addprefix ./include_bonus/, $(HD_FILES)))

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

%_bonus.o:	%_bonus.c
	$(CC) $(CFLAGS) -I $(LIBFT_DIR) -I $(HEADER_BONUS_DIR) -c $< -o $@

%.o:	%.c
	$(CC) $(CFLAGS) -I $(LIBFT_DIR) -I $(HEADER_DIR) -c $< -o $@

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
