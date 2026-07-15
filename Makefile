CC = zig cc

ALL_FLAGS := -Wconversion -Wextra -Wall -Wpedantic -Wcast-qual -Wstrict-prototypes -Wcast-align -Wshadow -Wwrite-strings -Wswitch-default -Werror

get_words_cmd := src/get_words.c -o listwords
renaming_cmd := src/renaming.c -o rename
backup_cmd := src/synchronise.c -o sync

base: all

all: list_words renaming backup_script

renaming:
	$(CC) $(renaming_cmd) $(ALL_FLAGS) -std=c89

list_words:
	$(CC) $(get_words_cmd) $(ALL_FLAGS) -std=c89

backup_script:
	$(CC) $(backup_cmd) $(ALL_FLAGS) -std=c99
