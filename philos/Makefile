NAME = philos

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f

SRCDIR = src/
INCDIR = include/

SRCS = $(SRCDIR)main.c \
       $(SRCDIR)args.c \
       $(SRCDIR)init.c \
       $(SRCDIR)routine.c \
       $(SRCDIR)utils.c \
       $(SRCDIR)monitor.c \
       $(SRCDIR)monitor_utils.c \
       $(SRCDIR)actions.c \
       $(SRCDIR)thread_management.c \
       $(SRCDIR)thread_utils.c \
       $(SRCDIR)cleanup.c

OBJS = $(SRCS:.c=.o)

INCLUDES = -I$(INCDIR)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re 