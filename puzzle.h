#include<list>
#include<iostream>
#include<cstdlib>

using namespace std;

class PuzzleBoard{
    private:
        int **cost;
        int boardSize;
        int index_row;
        int index_col;
        list<int> *adj;
    public:
        PuzzleBoard(int boardSize, int **fields = NULL);
        /* If fields is null, then initialize the fields of the board with random values between 1 and boardSize-1. */
        bool makeMove(int direction);
        /* makes the move (if valid), direction is 0 for up, 1 for right, 2 for down, 3 for left. Returns true if the move was 
           valid, false otherwise. */
        bool getResult();
        /* Returns false if game is not over yet, true if puzzle was solved */
        friend std::ostream &operator<<(std::ostream &os, PuzzleBoard const &m);
        int solve();
        /* returns the minimum number of moves needed to solve the puzzle, and -1 if it’s not solvable. */
};

