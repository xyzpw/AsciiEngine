CXX = g++
CXXFLAGS = -fPIC -Iinclude -std=c++20 -Wall -Wextra
LDFLAGS = -lncurses -lSDL2 -lSDL2_mixer

BUILD_DIR = build

SOURCES := $(shell find src -type f -name '*.cc')
OBJ := $(SOURCES:src/%.cc=$(BUILD_DIR)/%.o)

LIB = libAsciiEngine.so

all: $(LIB)


$(LIB): $(OBJ)
	$(CXX) -shared -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: src/%.cc
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

PREFIX ?= /usr/local

install:
	cp $(LIB) /usr/local/lib/
	cp -r include/AsciiEngine /usr/local/include/

install_local:
	mkdir -p build/install/lib
	mkdir -p build/install/include/AsciiEngine
	cp $(LIB) build/install/lib/
	cp -r include/AsciiEngine build/install/include/AsciiEngine
