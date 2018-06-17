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
        bool makeMove(int direction);
        bool getResult();
        friend std::ostream &operator<<(std::ostream &os, PuzzleBoard const &m);
        int solve();
};

