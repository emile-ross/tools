CC = clang

ALL_FLAGS := -Wconversion -Wextra -Wall -Wpedantic -std=c90

OUT = -o listwords
CMD := src/get_words.c $(OUT)

base: all

all:
	$(CC) $(CMD) $(ALL_FLAGS) -Werror

