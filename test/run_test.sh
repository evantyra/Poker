#!/bin/bash

rm -f *.o

#Make the display.o file
cd ../display_class
echo "In $PWD making display"
make
cd ../test

echo "In $PWD copying files"
cp ../display_class/display.o .
cp ../Frame* .
cp ../Card* .
cp ../Hand* .
cp ../Deck* .
cp ../Player* .
cp ../HumanPlayer* .

echo "Compiling..."
g++ Frame.cpp -c
g++ Card.cpp -c
g++ Hand.cpp -c
g++ Deck.cpp -c
g++ Player.cpp -c
g++ HumanPlayer.cpp -c
g++ HumanPlayerStub.cpp -c

echo "Making executable..."
g++ HumanPlayerDriver.cpp display.o Frame.o Card.o Hand.o Deck.o Player.o HumanPlayer.o HumanPlayerStub.o -o HumanPlayerDriver.o -lncursesw

echo "Running executable..."
./HumanPlayerDriver.o
