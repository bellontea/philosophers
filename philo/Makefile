NAME = philo

OBJ_DIR = ./objects
HEADER = philo.h

CFLAGS = -pthread -I./ -Wall -Wextra -Werror 

SRC = $(shell ls ./*.c)

OBJS := $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
CC = gcc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c $(HEADER)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all