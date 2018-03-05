SYS := $(shell gcc -dumpmachine)

CC = gcc
CFLAGS = -Wall -Wextra -std=gnu99
LDFLAGS = -lraylib
SOURCE = GroundZero.c GroundZeroRenderer.c
BUILD_DIR = bin/
EXECUTABLE = groundzero

ifneq (, $(findstring linux, $(SYS)))
  # Linux, link against glfw
  LDFLAGS += -lglfw 
else ifneq (, $(findstring msys, $(SYS)))
  # Windows
else ifneq (, $(findstring apple, $(SYS)))
  # macOS, use gcc not clang
  CC = gcc-7
endif

all:
	@$(CC) $(CFLAGS) $(SOURCE) -o $(BUILD_DIR)$(EXECUTABLE) $(LDFLAGS)

run: all
	@$(BUILD_DIR)$(EXECUTABLE)