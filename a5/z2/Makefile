CC = gcc
CFLAGS = -Wall -Wextra -pthread -O0

## Remove some warnings.
CFLAGS += -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function

all: linked_list test

## Which lock to use?
# LOCK_FILE = pthread_lock.c

## Additional source files
SRC_FILES = ../common/aff.c

linked_list: main.c $(LOCK_FILE) $(SRC_FILES) 
	$(CC) $(CFLAGS) $^ -o $@

test: test.c $(LOCK_FILE) $(SRC_FILES)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f linked_list test
