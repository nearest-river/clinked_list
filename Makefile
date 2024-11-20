
NAME=clinked-list
CFLAGS=-Wall -g


build:
	./scripts/build
test:
	./scripts/build;
	gcc $(CFLAGS) ./tests/main.c -L ./include -l$(NAME) -o ./bin/test;
	./bin/test;

