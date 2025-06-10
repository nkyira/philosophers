NAME	= philo
CC		= gcc
FLAGS	= -Wall -Werror -Wextra -pthread

SRCDIR	= src/
OBJDIR	= obj/

SRC		= $(wildcard $(SRCDIR)*.c)
OBJ		= $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRC))

INC		= inc/

all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c | $(OBJDIR)
	$(CC) $(INCLUDE) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
