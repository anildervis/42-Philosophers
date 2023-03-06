NAME = philosophers
CC = gcc
FLAGS = -Wall -Werror -Wextra
RM = rm -f
MANDATORY_DIR = philo/
SRC = main philo_utils initialize
SRC_FILES = $(addprefix $(MANDATORY_DIR), $(addsuffix .c, $(SRC)))

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

all:
	$(CC) -pthread $(FLAGS) $(SRC_FILES) -o $(NAME)
	@echo "$(GREEN)All compiled.$(DEF_COLOR)"

fclean:
	$(RM) $(NAME)

re:	fclean all

.PHONY = all fclean re bonus