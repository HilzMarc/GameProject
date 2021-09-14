#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H
#endif // GAMEOFLIFE_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <stdio.h>

using namespace std;

class GameOfLife{

    int FieldWidth;
    int FieldHeight;
    int **FieldOld;
    int **FieldNew;

public:
    void resetField();
    void CreateField();
    void SaveField(string filename);
    void LoadField(string filename);
    void SetWidth(int width);
    void SetHeight(int height);
    int getHeight();
    int getWidth();
    void SetDead(int row, int col);
    void SetAlive(int row, int col);
    void ChangeState(int row, int col);
    int GetNeighboursCount(int row, int col);
    void CalcNextIter();
    int getState(int row, int col);
};
