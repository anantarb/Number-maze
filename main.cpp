#include<iostream>
#include"problem4.h"

using namespace std;

int main()
{
    int row1[] = {3,3,3,1};
    int row2[] = {3,3,2,1};
    int row3[] = {3,3,3,3};
    int row4[] = {1,3,1,3};
    int *adj[] = {row1, row2, row3, row4};
    PuzzleBoard a(4, adj);
    cout << a;
    cout << a.solve();

}
