.PHONY: build

build:
	gcc src/main.c src/utils.c src/logic.c src/menu.c -o main.out -Wall -O2