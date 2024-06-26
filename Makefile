INCLUDE		= pipex.h
COMP		= gcc
NAME		= pipex
CFLAGS		= -Wall -Werror -Wextra

SRC			= check.c\
			process_child.c\
			process_parent.c\
			ft_split.c\
			main.c\
			utils.c\
			utils_2.c\
			ultimate_free.c\
			verif_access.c

OBJS=$(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	echo $(OBJS)
	@$(COMP) $(CFLAGS) $(SRC) -o $(NAME)
	@if [ $$? -eq 0 ]; then \
	echo "\033[32;1mCompilation successful!\033[0m"; \
	fi

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: clean fclean re all
