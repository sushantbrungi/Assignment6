
# EECS 348 - Assignment 6
# Makefile for Sudoku Solver
# ----------------------------
# Usage:
#   make          -> compile program
#   make run      -> run solver on all puzzles
#   make clean    -> delete compiled files

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = Assignment6.exe
SRC = Assignment6.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET) puzzle1.txt puzzle2.txt puzzle3.txt puzzle4.txt puzzle5.txt

clean:
	rm -f $(TARGET)
