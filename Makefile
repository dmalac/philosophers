NAME = philo

SRC = 	main.c \
		ft_atoi.c \
		ft_strlen.c \
		ft_putendl_fd.c \
		eat_sleep_think.c \
		init_all.c \
		error.c \
		get.c \
		print.c \
		create_cleanup.c \
		monitoring.c

SRCDIR = src
OBJDIR = obj
INCLDIR = incl

OBJ = $(SRC:%.c=$(OBJDIR)/%.o)

CC = gcc
CCFLAGS = -I $(INCLDIR) -Wall -Wextra -Werror -pthread

# delete
# DEBUG_FLAGS = -g -fsanitize=thread
DEBUG_FLAGS = -g -fsanitize=address
DEBUG ?= 0

UNITY_DIR = unity_tester
UNITY_SRC = $(UNITY_DIR)/src/unity.c \
			$(SRCDIR)/init_all.c \
			$(SRCDIR)/ft_strlen.c \
			$(SRCDIR)/ft_putendl_fd.c \
			$(SRCDIR)/ft_atoi.c \
			$(UNITY_DIR)/test_init_all.c

# delete

all: $(NAME)

$(NAME): $(OBJ)
ifeq ($(DEBUG), 1)
	$(CC) $(CCFLAGS) $(DEBUG_FLAGS) $^ -o $@
else
	$(CC) $(CCFLAGS) $^ -o $@
endif

debug:	# delete
	$(MAKE) "DEBUG = 1"

unity:	# delete
	$(CC) -I $(UNITY_DIR)/src $(CCFLAGS) $(UNITY_SRC) -o unitest

$(OBJ): | $(OBJDIR)

$(OBJDIR):
	mkdir $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
ifeq ($(DEBUG),1)
	$(CC) $(CCFLAGS) $(DEBUG_FLAGS) -c $? -o $@
else
	$(CC) $(CCFLAGS) -c $? -o $@
endif

clean:
	rm -Rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

redebug: fclean debug	# delete

.PHONY: all bonus clean fclean re redebug # delete