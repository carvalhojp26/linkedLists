.PHONY: docs build

build:
	gcc src/main.c src/utils.c src/logic.c src/menu.c -o main.out -Wall -O2

docs:
	doxygen && \
	cd latex/ && \
	make pdf && \
	cd .. && \
	mv latex/refman.pdf docs/linkedLists-refman.pdf && \
	rm -rf docs/html && \
	mv html docs/ && \
	rm -rf latex