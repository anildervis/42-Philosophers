NAME = philo_bonus
CC = gcc
FLAGS = -Wall -Werror -Wextra
RM = rm -f
INCLUDE = -pthread
SRCS = main.c philo_utils.c controls.c routine.c initialize.c
OBJS = $(SRCS:.c=.o)
HEADER = philosophers_bonus.h
# Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

all: $(NAME) $(HEADER)

$(NAME): $(OBJS)
	$(CC) $(INCLUDE) $(FLAGS) $(OBJS) -o $(NAME)
	@echo "$(YELLOW)Bonus compiled.$(DEF_COLOR)"

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY = all clean fclean re 