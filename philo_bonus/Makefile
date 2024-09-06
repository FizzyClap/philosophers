NAME = philo_bonus
CC = cc
FLAGS = -Wall -Werror -Wextra -fsanitize=thread
RM = rm -rf
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[38;5;153m
NC = \033[0m

SRCS =	src/main.c\
		src/utils.c\
		src/free.c\
		src/parsing.c\
		src/routine.c\
		src/init.c\

OBJS = $(SRCS:.c=.o)

$(NAME): pimped $(OBJS)
	@sleep 0.8
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS)
	@echo "\033[1A\033[2K\033[1A"
	@echo "│$(GREEN) Compilation of $(NAME) completed ✓ $(NC)	     │"
	@echo "└────────────────────────────────────────────────────┘"
	@$(RM) errors.tmp;

.c.o:
	@$(CC) $(FLAGS) -c -o $@ $< 2>> errors.tmp || \
	{ \
		echo "\033[u\033[1A\033[2K│$(RED) Compilation of $(NAME) failed X$(NC)		     │"; \
		echo "└────────────────────────────────────────────────────┘"; \
		sed "s/error:/\x1b[1;31m&\x1b[0m/g" errors.tmp; \
		$(RM) errors.tmp; \
		exit 1; \
	}

pimped:
	@echo "$(NC)┌─────$(NAME)────────────────────────────────────┐"
	@echo "│$(BLUE) Compiling $(NAME) in progress... ⌛$(NC)	     │"
	@echo "\033[s└────────────────────────────────────────────────────┘"

all: $(NAME)

clean:
	@echo "$(NC)┌─────clean $(NAME)──────────────────────────────┐"
	@echo "│$(BLUE) Cleaning $(NAME) objects in progress... ⌛$(NC)     │"
	@echo "└────────────────────────────────────────────────────┘"
	@sleep 0.8
	@echo "\033[1A\033[2K\033[1A"
	@$(RM) $(OBJS)
	@echo "│$(GREEN) Cleaning of $(NAME) objects completed ✓ $(NC)       │"
	@echo "└────────────────────────────────────────────────────┘"

fclean: clean
	@echo "$(NC)┌─────fclean $(NAME)─────────────────────────────┐"
	@echo "│$(BLUE) Cleaning $(NAME) in progress... ⌛$(NC)	     │"
	@echo "└────────────────────────────────────────────────────┘"
	@sleep 0.8
	@echo "\033[1A\033[2K\033[1A"
	@$(RM) $(NAME)
	@echo "│$(GREEN) Cleaning of $(NAME) completed ✓ $(NC)		     │"
	@echo "└────────────────────────────────────────────────────┘"

re: fclean all

norme:
	@echo "$(BLUE)Checking norminette in progress... ⌛"
	@if norminette src include libft > norme.tmp;\
	then echo "$(GREEN)Norminette check passed successfully ✓";\
	else echo "$(RED)Norminette check failed.$(NC)";\
	cat norme.tmp | grep "Error";\
	fi
	@$(RM) norme.tmp

.PHONY: all clean fclean re pimped norme
