CC = gcc
CFLAGS = -Wall -Wextra -pthread -O0

all: accounts

SRC_FILES= accounts.c ../common/aff.c

accounts: $(SRC_FILES) 
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f accounts
