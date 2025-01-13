CFLAGS = -Wall -Wextra -Werror
CC = gcc

SERVER_N = server
CLIENT_N = client

LIB_DIR = libft
LIB_FILE = libft.a
LIB = $(LIB_DIR)/$(LIB_FILE)

INCLUDES = -I$(LIB_DIR)

all: $(SERVER_N)

$(SERVER_N): server.o $(LIBFT)
	$(CC) $(CFLAGS) $< -L$(LIB_DIR) -lft $(INCLUDES) -o $@

$(CLIENT_N): client.o $(LIBFT)
	$(CC) $(CFLAGS) $< -L$(LIB_DIR) -lft $(INCLUDES) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft

clean:
	rm -f *.o $(LIBFT)
	$(MAKE) clean -C libft

fclean: clean
	rm -f $(SERVER_N) $(CLIENT_N) 

re: fclean all
