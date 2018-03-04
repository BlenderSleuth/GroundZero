SYS := $(shell gcc -dumpmachine)

CC = g++
CFLAGS = -Wall -Wextra -std=c++11
LDFLAGS = -lraylib
SOURCE = GroundZero.cpp GroundZeroRenderer.cpp
EXECUTABLE = groundzero

ifneq (, $(findstring linux, $(SYS)))
  # Linux, link against glfw
  LDFLAGS += -lglfw 
else ifneq (, $(findstring msys, $(SYS)))
  # Windows
else ifneq (, $(findstring apple, $(SYS)))
  # macOS, use gcc not clang
  CC = g++-7
endif

all:
	@$(CC) $(CFLAGS) $(SOURCE) -o $(EXECUTABLE) $(LDFLAGS)

run: all
	@./$(EXECUTABLE)