CFLAGS = -Wall -Wextra -Werror -no-pie
CC = gcc

SERVER_N = server
CLIENT_N = client
SERVER_BONUS_N = server_bonus
CLIENT_BONUS_N = client_bonus

LIB_DIR = libft
LIB_FILE = libft.a
LIB = $(LIB_DIR)/$(LIB_FILE)

INCLUDES = -I$(LIB_DIR)

all: $(SERVER_N) $(CLIENT_N)

bonus: $(SERVER_BONUS_N) $(CLIENT_BONUS_N)

$(SERVER_N): server.o $(LIB)
	$(CC) $(CFLAGS) server.o -L$(LIB_DIR) -lft $(INCLUDES) -o $@

$(CLIENT_N): client.o $(LIB)
	$(CC) $(CFLAGS) client.o -L$(LIB_DIR) -lft $(INCLUDES) -o $@

$(SERVER_BONUS_N): server_bonus.o $(LIB)
	$(CC) $(CFLAGS) server_bonus.o -L$(LIB_DIR) -lft $(INCLUDES) -o $@

$(CLIENT_BONUS_N): client_bonus.o $(LIB)
	$(CC) $(CFLAGS) client_bonus.o -L$(LIB_DIR) -lft $(INCLUDES) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB):
	$(MAKE) -C $(LIB_DIR)

clean:
	rm -f *.o
	$(MAKE) clean -C $(LIB_DIR)

fclean: clean
	rm -f $(SERVER_N) $(CLIENT_N) $(SERVER_BONUS_N) $(CLIENT_BONUS_N)
	$(MAKE) fclean -C $(LIB_DIR)

re: fclean all

re_bonus: fclean bonus

.PHONY: all bonus clean fclean re re_bonus