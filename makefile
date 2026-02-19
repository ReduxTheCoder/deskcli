# Paths
SRC := $(shell find src -name "*.cpp")
INCLUDE := -Iinclude

CFLAGS_DEBUG := -Wall -Wextra -pedantic-errors -std=c++23 -g $(INCLUDE)
CFLAGS_RELEASE := -O3 -flto -DNDEBUG -mtune=generic -std=c++23 -march=x86-64 $(INCLUDE)

BIN := bin/tgpc
BIN_DEBUG := bin/tgpc-debug

all: $(BIN_DEBUG)

$(BIN_DEBUG): $(SRC)
	g++ $(SRC) $(CFLAGS_DEBUG) -o $(BIN_DEBUG)

release: $(SRC)
	g++ $(SRC) $(CFLAGS_RELEASE) -o $(BIN)

run: $(BIN_DEBUG)
	./$(BIN_DEBUG)

build: release
	mv ./$(BIN) ~/.local/bin/tgpc

install: release
	mv ./$(BIN) ~/.local/bin/tgpc

clean:
	rm -f $(BIN) $(BIN_DEBUG) $(TEST_BIN)
