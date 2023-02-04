NAME = philo
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
SRCS =	push_swap.c \
		srcs/struct/struct.c \
		srcs/struct/struct_utils.c \

OBJS = ${SRCS:.c=.o}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean
