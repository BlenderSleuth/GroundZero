SYS := $(shell gcc -dumpmachine)

CC = gcc
CFLAGS = -s -std=c99 -Wall -Wextra
LDFLAGS = -v -lraylib
SOURCE = GroundZero.c GroundZeroRenderer.c
BUILD_DIR = bin/
ICON = icon
EXECUTABLE = groundzero

ifneq (, $(findstring linux, $(SYS)))
  # Linux, link against glfw
  LDFLAGS += -lglfw 
else ifneq (, $(findstring mingw, $(SYS)))
  # Windows
  LDFLAGS += -lglfw3 -lgdi32
else ifneq (, $(findstring msys, $(SYS)))
  # Windows msys
  $(error Please use MinGW!)
else ifneq (, $(findstring apple, $(SYS)))
  # macOS, use gcc not clang
  CC = gcc-7
endif

all:
	$(CC) $(CFLAGS) -o $(BUILD_DIR)$(EXECUTABLE) $(SOURCE) $(LDFLAGS) $(ICON)

run: all
	@$(BUILD_DIR)$(EXECUTABLE)
