#include<iostream>
#include<cstdlib>
#include<ctime>
#include<list>
#include"puzzle.h"

using namespace std;

PuzzleBoard::PuzzleBoard(int boardSize, int **fields)
{
    this->boardSize = boardSize;
    cost = new int*[boardSize];
    index_col = 0;
    index_row = 0;
    adj = new list<int>[boardSize*boardSize];

    for (int i = 0; i < boardSize; i++){
        cost[i] = new int[boardSize];
    }

    srand(time(NULL));
    if (fields == NULL){
        for (int i = 0; i < boardSize; i++){
            for (int j = 0; j < boardSize; j++){
                cost[i][j] = (rand() % (boardSize - 1)) + 1;
            }
        }
    }
    else{
        for (int i = 0; i < boardSize; i++){
            for (int j = 0; j < boardSize; j++){
                cost[i][j] = fields[i][j];
            }
        }
    }

    int index = 0;
    for (int i = 0; i < boardSize; i++){
        for (int j = 0; j < boardSize; j++){
            if (j - cost[i][j] >=0){
                adj[index].push_back(index - cost[i][j]);
            }
            if (j + cost[i][j] < boardSize){
                adj[index].push_back(index + cost[i][j]);
            }
            if (i - cost[i][j] >= 0){
                adj[index].push_back(index - boardSize*cost[i][j]);
            }
            if (i + cost[i][j] < boardSize){
                adj[index].push_back(index + boardSize*cost[i][j]);
            }
            index = index + 1;

        }
    }
}

bool PuzzleBoard::makeMove(int direction)
{
    if (direction == 0 && index_row - cost[index_row][index_col] >= 0){
        index_row = index_row - cost[index_row][index_col];
        return true;
    }
    if (direction == 1 && index_col + cost[index_row][index_col] < boardSize){
        index_col = index_col + cost[index_row][index_col];
        return true;
    }
    if (direction == 2 && index_row + cost[index_row][index_col] < boardSize){
        index_row = index_row + cost[index_row][index_col];
        return true;
    }
    if (direction == 3 && index_col - cost[index_row][index_col] >= 0){
        index_col = index_col - cost[index_row][index_col];
        return true;
    }
    return false;
}

bool PuzzleBoard::getResult()
{
    if (index_row == boardSize - 1 && index_col == boardSize - 1){
        return true;
    }
    return false;
}

std::ostream &operator<<(std::ostream &os, PuzzleBoard const &m)
{
    os << "The puzzle board is:" << endl;
    for (int i = 0; i < m.boardSize; i++){
        for (int j = 0; j < m.boardSize; j++){
            os << m.cost[i][j] << " ";
        }
        os << endl;
    }
    os << "The graph representation of puzzle board using adjacency list is:" << endl;
    for (int i = 0; i < m.boardSize*m.boardSize; i++){
        for (list<int>::iterator j = m.adj[i].begin(); j != m.adj[i].end(); ++j){
            os << i << "->" << *j << " ";
        }
        os << endl;
    }
    return os;
}

int PuzzleBoard::solve()
{
    /* Applying BFS search */
    bool *visited = new bool[boardSize*boardSize];
    for(int i = 0; i < boardSize*boardSize; i++){
        visited[i] = false;
    }

    list<int> queue;
    int s = 0;
    visited[s] = true;
    queue.push_back(s);
    queue.push_back(-5);
    list<int>::iterator i;
    int depth = 0;
    while(!queue.empty()){
        s = queue.front();
        if (s == -5){
            break;
        }
        queue.pop_front();
        for (i = adj[s].begin(); i != adj[s].end(); ++i){
            if (visited[*i] == false){
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
        if (visited[boardSize*boardSize - 1] == true){
            return depth + 1;
        }
        if (queue.front() == -5){
            depth++;
            queue.pop_front();
            queue.push_back(-5);
        }
    }
    return -1;
}
