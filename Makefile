
NAME="clinked_list"
CFLAGS=-Wall -g


build:
	./scripts/build
test:
	build
	gcc $(CFLAGS) ./tests/main.c -L ./include/ -l$(NAME) -o ./bin/test
	./bin/test

