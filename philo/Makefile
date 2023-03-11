NAME = philo
CC = gcc
FLAGS = -Wall -Werror -Wextra
RM = rm -f
INCLUDE = -pthread
SRCS = main.c philo_utils.c initialize.c routine.c
OBJS = $(SRCS:.c=.o)
HEADER = philosophers.h

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
	@echo "$(GREEN)All compiled.$(DEF_COLOR)"

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY = all clean fclean re 