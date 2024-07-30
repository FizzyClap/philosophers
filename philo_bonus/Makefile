NAME_BONUS = philo_bonus
CC = cc
FLAGS = -Wall -Werror -Wextra -fsanitize=thread -g
RM = rm -rf

SRCS_BONUS =	src/main.c\
				src/utils.c\
				src/free.c\
				src/init.c\
				src/parsing.c\
				src/routine.c\

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(FLAGS) -o $(NAME_BONUS) $(OBJS_BONUS)

all: $(NAME_BONUS)

clean:
	$(RM) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME_BONUS)

re: fclean all
