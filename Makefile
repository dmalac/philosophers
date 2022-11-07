NAME = philo

SRC = 	main.c \
		create_cleanup.c \
		eat_sleep_think.c \
		error.c \
		ft_atoi.c \
		get.c \
		init_all.c \
		monitoring.c \
		print_msg.c \
		utils.c

SRCDIR = src
OBJDIR = obj
INCLDIR = incl

OBJ = $(SRC:%.c=$(OBJDIR)/%.o)

CC = gcc
CCFLAGS = -I $(INCLDIR) -Wall -Wextra -Werror -pthread

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CCFLAGS) $^ -o $@

$(OBJ): | $(OBJDIR)

$(OBJDIR):
	mkdir $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CCFLAGS) -c $? -o $@

clean:
	rm -Rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re