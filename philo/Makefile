NAME = philo
CC = cc
FLAGS = -Wall -Werror -Wextra -fsanitize=thread -g
RM = rm -rf

SRCS =	src/main.c\
		src/utils.c\
		src/free.c\
		src/parsing.c\
		src/routine.c\
		src/init.c\

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS)

.c.o:
	$(CC) $(FLAGS) -c -o $@ $<

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
