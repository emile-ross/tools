CC = zig cc

ALL_FLAGS := -Wconversion -Wextra -Wall -Wpedantic -std=c89

OUT = -o listwords
get_words_cmd := src/get_words.c $(OUT)
renaming_cmd := src/renaming.c $(OUT)
backup_cmd := src/backup_script.c $(OUT)

base: all

all: list_words renaming backup_script

renaming:
	$(CC) $(renaming_cmd) $(ALL_FLAGS) -Werror

list_words:
	$(CC) $(get_words_cmd) $(ALL_FLAGS) -Werror

backup_script:
	$(CC) $(backup_cmd) $(ALL_FLAGS) -Werror
