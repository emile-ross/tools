CC = clang

ALL_FLAGS = -Wall -Wcast-align -Wcast-qual -Wconversion -Werror -Wextra -Wpedantic -Wshadow -Wstrict-prototypes -Wswitch-default

89_FLAGS = -std=c89 -Wwrite-strings

OUT = backup-sync

STRLEN_PATH := obj/strlen.o
VERBOSE_PATH := obj/verbose.o
ERRORS_PATH := obj/errors.o

sync_obj = $(ERRORS_PATH) $(VERBOSE_PATH)

get_words_cmd := src/get_words.c -o listwords
renaming_cmd := src/renaming.c -o rename

SYNC_FILENAMES = backup buffers compare config file_backup main mem path strings

SYNC_FILES := $(addprefix src/sync/, $(SYNC_FILENAMES))
SRCS := $(addsuffix .c, $(SYNC_FILES))

backup_cmd := $(SRCS) -o backup-sync

base: all
all: list_words renaming sync

renaming:
	$(CC) $(renaming_cmd) $(ALL_FLAGS) $(89_FLAGS)

list_words: sync_obj
	$(CC) $(get_words_cmd) $(STRLEN_PATH) $(VERBOSE_PATH) $(ALL_FLAGS) $(89_FLAGS)

sync: synchronise
synchronise: verbose errors
	$(CC) $(backup_cmd) $(sync_obj) $(ALL_FLAGS) -std=c99

install: 
	sudo cp $(OUT) /usr/bin/

errors:
	$(CC) -c src/errors.c -o $(ERRORS_PATH) $(ALL_FLAGS) $(89_FLAGS)

strlen:
	$(CC) -c src/strlen.c -o $(STRLEN_PATH) $(ALL_FLAGS) $(89_FLAGS)

verbose:
	$(CC) -c src/verbose.c -o $(VERBOSE_PATH) $(ALL_FLAGS) $(89_FLAGS)

clean:
	rm obj/*

sync_obj: errors verbose
