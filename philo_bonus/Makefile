NAME = philo_bonus
CC = gcc
FLAGS = -Wall -Werror -Wextra
RM = rm -f
SRC = main philo_utils routine
SRC_FILES = $(addsuffix .c, $(SRC))
HDR = philosophers_bonus
HDR_FILES = $(addsuffix .h, $(HDR))
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

all: $(NAME) $(HDR_FILES)

$(NAME):
	$(CC) -pthread $(FLAGS) $(SRC_FILES) -o $(NAME)
	@echo "$(GREEN)All compiled.$(DEF_COLOR)"

clean:

fclean:
	$(RM) $(NAME)

re:	fclean all

.PHONY = all clean fclean re 