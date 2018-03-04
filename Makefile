CC = g++
CFLAGS = -Wall -Wextra -std=c++11 -I/usr/include
LDFLAGS = -L/usr/lib -lraylib -lglfw
SOURCE = GroundZero.cpp GroundZeroRenderer.cpp
EXECUTABLE = groundzero

all:
	$(CC) $(CFLAGS) $(SOURCE) -o $(EXECUTABLE) $(LDFLAGS)

run: all
	@./$(EXECUTABLE)