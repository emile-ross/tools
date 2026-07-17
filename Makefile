CC = clang

OUT = backup-sync

ALL_FLAGS := -Wconversion -Wextra -Wall -Wpedantic -Wstrict-prototypes -Wcast-qual -Wcast-align -Wshadow -Wswitch-default -Werror -Wshadow

get_words_cmd := src/get_words.c -o listwords
renaming_cmd := src/renaming.c -o rename

SYNC_FILENAMES = main config strings file_write backup
SYNC_FILES := $(addprefix src/sync/, $(SYNC_FILENAMES))
SRCS := $(addsuffix .c, $(SYNC_FILES))

backup_cmd := $(SRCS) -o backup-sync

base: all

all: list_words renaming sync

renaming:
	$(CC) $(renaming_cmd) $(ALL_FLAGS) -std=c89 -Wwrite-strings 

list_words:
	$(CC) $(get_words_cmd) $(ALL_FLAGS) -std=c89 -Wwrite-strings 

sync: synchronise
synchronise:
	$(CC) $(backup_cmd) $(ALL_FLAGS) -std=c99

install: 
	sudo cp $(OUT) /usr/bin/
