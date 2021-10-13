EXEC		=	philo

CC			=	gcc
RM			=	rm -rf
CFLAGS		=	-Wall -Werror -Wextra

SRCS		=	./Sources/main.c\
				./Sources/init.c\
				./Sources/exec.c\
				./Sources/status.c\
				./Sources/tool.c\
				./Sources/print.c

OBJS		=	$(SRCS:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) -lpthread -o $(EXEC)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(EXEC)

re: fclean all

.PHONY: all clean fclean re
