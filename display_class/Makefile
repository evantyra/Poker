# This is an example makefile
# It is very important to add -lncursesw for the ncurses library
CC=g++
DEBUG=
CFLAGS=-c -Wall $(DEBUG)
LDFLAGS=-lncurses $(DEBUG)
SOURCES=display.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=display

all: clean $(SOURCES) $(EXECUTABLE)

debug: clean
debug: DEBUG +=-g
debug: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)

