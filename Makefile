
NAME=clinked-list
CFLAGS=-Wall -g -O3


build:
	./scripts/build
test:
	./scripts/build;
	gcc $(CFLAGS) ./tests/main.c -L ./target -l$(NAME) -o ./bin/test;
	./bin/test;

