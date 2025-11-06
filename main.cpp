// EECS 348 Assignment 6
// Same as Assignment 2
// Author: Sushant Brungi
// Creation Date: 11/04/25
// Collaborators: RG, Me, Copilit, Stackoverflow
// Inputs: Assignment2_Test_File.txt
// Outputs: Sudoku solutions and puzzle

#include <iostream>              // for input and output
#include <fstream>               // for file reading
#include <vector>                // for using vectors
#include <string>                // for using strings

using namespace std;          

const int SIZE = 9;             // Sudoku grid is 9x9

// lines written by me except 14-15 by copilot
void printGrid(const vector<vector<int>>& grid) {
    for (int row = 0; row < SIZE; row++) {             // loop through rows
        for (int col = 0; col < SIZE; col++) {         // loop through columns
            if (grid[row][col] == 0)                   // if cell is empty
                cout << "_";                           // print underscore
            else
                cout << grid[row][col];                // print number
            if (col < SIZE - 1)
                cout << " ";                           // space between numbers
        }
        cout << endl;                                  // new line after row
    }
}

// lines written by me other than 28-29 helped by overflow and copilot.
bool isSafe(const vector<vector<int>>& grid, int row, int col, int num) {
    for (int i = 0; i < SIZE; i++) {                   // check row and column
        if (grid[row][i] == num || grid[i][col] == num)
            return false;                              // number already exists
    }

    int startRow = (row / 3) * 3;                      // top-left row of 3x3 box
    int startCol = (col / 3) * 3;                      // top-left col of 3x3 box
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (grid[startRow + r][startCol + c] == num)
                return false;                          // number in 3x3 box
        }
    }

    return true;                                       // place number
}

// this will solve using backtracking. first loop by copilot but rest by me once i understood the functioanlity.
void solveSudoku(vector<vector<int>>& grid, vector<vector<vector<int>>>& solutions) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (grid[row][col] == 0) {                 // find empty cell
                for (int num = 1; num <= 9; num++) {   // try numbers 1 to 9
                    if (isSafe(grid, row, col, num)) { // check if safe
                        grid[row][col] = num;          // place number
                        solveSudoku(grid, solutions);  // recurse
                        grid[row][col] = 0;            // backtrack
                    }
                }
                return;                                // stop and backtrack
            }
        }
    }
    solutions.push_back(grid);                         // store valid solution
}

// will read puzzle from the file. lines written by me other than 79 bc of for loop. and the first vector<<
bool readPuzzle(const string& filename, vector<vector<int>>& grid) {
    ifstream file(filename);                           // open file
    if (!file.is_open())                               // check if opened
        return false;

    grid.resize(SIZE, vector<int>(SIZE, 0));           // create 9x9 grid
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            string token;
            if (!(file >> token))                      // read next value
                return false;
            if (token == "_")
                grid[row][col] = 0;                    // blank cell
            else
                grid[row][col] = token[0] - '0';       // convert char to int
        }
    }

    return true;                                       // puzzle loaded
}

// this will oeprate the main function. mostly written by me other than 102,109-114. but rest myslef. help from overflow and copilot.
int main(int argc, char* argv[]) {
    if (argc < 2) {                                    // check for input files
        cout << "Usage: ./Assignment6.exe puzzle1.txt [puzzle2.txt ...]" << endl;
        return 1;
    }

    for (int i = 1; i < argc; i++) {                   // loop through files
        string filename = argv[i];                     // get filename
        vector<vector<int>> grid;                      // create grid

        if (!readPuzzle(filename, grid)) {             // read puzzle
            cout << "Error reading " << filename << endl;
            continue;
        }

        cout << "----------------------------" << endl;
        cout << "Puzzle: " << filename << endl;
        printGrid(grid);                               // show original puzzle

        vector<vector<vector<int>>> solutions;         // store all solutions
        solveSudoku(grid, solutions);                  // solve puzzle

        if (solutions.empty()) {
            cout << "No solution found." << endl;
        } else {
            cout << "Solutions found: " << solutions.size() << endl;
            for (size_t s = 0; s < solutions.size(); s++) {
                cout << "Solution #" << (s + 1) << ":" << endl;
                printGrid(solutions[s]);               // show each solution
            }
        }
    }

    return 0;                                           // end program
}
