
NAME=clinked-list
CFLAGS=-Wall -g -O3
CC=gcc
BUILD=./scripts/build
BUILD_WIN=$(BUILD)-win32
CC_WIN=x86_64-w64-mingw32-$(CC)


build:
	$(BUILD)
build-win:
	$(BUILD_WIN)
test:
	$(BUILD)
	$(CC) $(CFLAGS) ./tests/main.c -L ./target -l$(NAME) -o ./bin/test
	./bin/test
test-win:
	$(BUILD_WIN);
	$(CC_WIN) $(CFLAGS) ./tests/main.c -L ./target/win32 -l$(NAME) -o ./bin/test
	wine ./bin/test.exe
clean:
	rm -rf target

