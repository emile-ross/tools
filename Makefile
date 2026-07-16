CC = zig cc

ALL_FLAGS := -Wconversion -Wextra -Wall -Wpedantic -Wstrict-prototypes -Wcast-qual -Wcast-align -Wshadow -Wwrite-strings -Wswitch-default -Werror

get_words_cmd := src/get_words.c -o listwords
renaming_cmd := src/renaming.c -o rename
backup_cmd := src/synchronise.c -o sync

base: all

all: list_words renaming sync

renaming:
	$(CC) $(renaming_cmd) $(ALL_FLAGS) -std=c89

list_words:
	$(CC) $(get_words_cmd) $(ALL_FLAGS) -std=c89

sync: synchronise
synchronise:
	$(CC) $(backup_cmd) $(ALL_FLAGS) -std=c99
