SYS := $(shell gcc -dumpmachine)

CC = g++
CFLAGS = -static -s -std=c++11 -Wall -Wextra
LDFLAGS = -lraylib
SOURCE = $(wildcard *.cpp)
BUILD_DIR = bin/
ICON = icon
EXECUTABLE = groundzero

ifneq (, $(findstring linux, $(SYS)))
  # Linux, link against glfw
  LDFLAGS += -lglfw
else ifneq (, $(findstring mingw, $(SYS)))
  # Windows
  LDFLAGS += -lglfw3 -lgdi32
else ifneq (, $(findstring apple, $(SYS)))
  # macOS, use gcc not clang
  CC = g++-7
endif

all:
	@$(CC) $(CFLAGS) -o $(BUILD_DIR)$(EXECUTABLE) $(SOURCE) $(LDFLAGS) $(ICON)

run: all
	@$(BUILD_DIR)$(EXECUTABLE)
