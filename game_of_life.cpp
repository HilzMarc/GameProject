#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <stdio.h>

#include "game_of_life.h"

/*
 * This function creates the new field
 * Height und width must be entered before calling this function
 * using set
 */

void GameOfLife::CreateField() {
    // Initiating the Array
    this->FieldNew = nullptr;
    this->FieldOld = nullptr;
    this->FieldOld = new int*[this->FieldHeight];
    this->FieldNew = new int*[this->FieldHeight];

    for(int i=0; i<this->FieldHeight; i++){

        this->FieldOld[i] = nullptr;
        this->FieldOld[i] = new int[this->FieldWidth];

        this->FieldNew[i] = nullptr;
        this->FieldNew[i] = new int[this->FieldWidth];
    }

    // Filling the array wirh zero (=dead cells)
    for(int i=0;i<this->FieldHeight;i++)
        for(int k=0; k<this->FieldWidth; k++){
            this->FieldOld[i][k] = 0;
            this->FieldNew[i][k] = 0;
        }

    return;
}

/*
 * This function exports the content of the field into a textfile,
 * using the filename given in the argument.
 */
void GameOfLife::SaveField(string filename){

    // Openign the file.
    ofstream ofs;
    ofs.open(filename);
    ofs << to_string(this->FieldHeight) + "\n";
    ofs << to_string(this->FieldHeight) + "\n";

    // Transformimg the data from the array and writing each line into the text file
    for(int i=0;i<this->FieldHeight;i++){
        for (int k=0;k<this->FieldWidth;k++){
            if (this->FieldOld[i][k]==0) {
                ofs << "o";
            } else {
                ofs << "*";
            }

        }
        ofs << "\n";
    }
    ofs.close();
}

/*
 * This function loads the content of a text file into the array.
 * It uses the filename given by an argument.
 */
void GameOfLife::LoadField(string filename){
    string templine, firstline, secondline;
    ifstream ifs(filename);
    if(!ifs){
        return;
    } else {
        // Get the height and with of the field represented in the textfile
        getline(ifs, firstline);
        this->FieldHeight = stoi(firstline);

        getline(ifs, secondline);
        this->FieldWidth = stoi(secondline);
        // Using the information to create new field.
        this->CreateField();

        // Read the content of the text file into the array.
        string templine;
        string tempchar;
        //
        for(int i=0;i<this->FieldHeight;i++){
            getline(ifs, templine);

            for(size_t k=0; k<this->FieldWidth; k++){

                tempchar = templine.substr(k, 1);
                if(tempchar=="*"){
                    this->FieldOld[i][k] = 1;
                } else if(tempchar=="o"){
                    this->FieldOld[i][k] = 0;
                } else{
                    // cout << "Fehler beim Auslesen aus Datei!";
                }
            }
        }
    }
}

// Simple setter-funtion
void GameOfLife::SetWidth(int width) {
    this->FieldWidth = width;
}

// Simple setter-function
void GameOfLife::SetHeight(int height){
    this->FieldHeight = height;
}

// Simple getter-function
int GameOfLife::getHeight()
{
    return this->FieldHeight;
}

// Simple getter-function
int GameOfLife::getWidth()
{
    return this->FieldWidth;
}

// Simple setter-function
void GameOfLife::SetDead(int row, int col){
    this->FieldOld[row][col] = 0;
}

// Simple setter-function
void GameOfLife::SetAlive(int row, int col){
    this->FieldOld[row][col] = 1;
}

// Simple getter-function
int GameOfLife::getState(int row, int col)
{
    return this->FieldOld[row][col];
}

/*
 * This function toggles the state of cell of which the coordiantes given as arguments
 *
 */
void GameOfLife::ChangeState(int row, int col){
    if (this->FieldOld[row][col] == 1){
        this->FieldOld[row][col] = 0;
    } else {
        this->FieldOld[row][col] = 1;
    }
}

/*
 * This function calculates the number of living neighbour cells of a given cell and returns this as an integer.
 * Attention: Cells on an adge postion are treated as if the field is surrounded by dead cells!
 */
int GameOfLife::GetNeighboursCount(int row, int col){
    int result=0;
    // First all 8 cases, where the regarded cell is on the edge are went throught
    if(row==0 and col==0){ // Top left
        result += 0;
        result += 0;
        result += 0;
        result += this->FieldOld[row][col+1];
        result += this->FieldOld[row+1][col+1];
        result += this->FieldOld[row+1][col];
        result += 0;
        result += 0;
        return result;
    } else if (row==0 and col>0 and col<(this->FieldWidth-1)) { // Top row
        result += 0;
        result += 0;
        result += 0;
        result += this->FieldOld[row][col+1];
        result += this->FieldOld[row+1][col+1];
        result += this->FieldOld[row+1][col];
        result += this->FieldOld[row+1][col-1];
        result += this->FieldOld[row][col-1];
        return result;
    } else if (row==0 and col==(this->FieldWidth-1)) { // Top right
        result += 0;
        result += 0;
        result += 0;
        result += 0;
        result += 0;
        result += this->FieldOld[row+1][col];
        result += this->FieldOld[row+1][col-1];
        result += this->FieldOld[row][col-1];
        return result;
    } else if (col==(this->FieldWidth-1) and row>0 and row<(this->FieldHeight-1)) { // Right column
        result += this->FieldOld[row-1][col-1];
        result += this->FieldOld[row-1][col];
        result += 0;
        result += 0;
        result += 0;
        result += this->FieldOld[row+1][col];
        result += this->FieldOld[row+1][col-1];
        result += this->FieldOld[row][col-1];
        return result;
    } else if (col==(this->FieldWidth-1) and row==(this->FieldHeight-1)) { // Bottom right
        result += this->FieldOld[row-1][col-1];
        result += this->FieldOld[row-1][col];
        result += 0;
        result += 0;
        result += 0;
        result += 0;
        result += 0;
        result += this->FieldOld[row][col-1];
        return result;
    } else if (row==(this->FieldHeight-1) and col>0 and col<(this->FieldWidth-1)) { // Bottom row
        result += this->FieldOld[row-1][col-1];
        result += this->FieldOld[row-1][col];
        result += this->FieldOld[row-1][col+1];
        result += this->FieldOld[row][col+1];
        result += 0;
        result += 0;
        result += 0;
        result += this->FieldOld[row][col-1];
        return result;
    } else if (row==(this->FieldHeight-1) and col==0) { // Bottom left
        result += 0;
        result += this->FieldOld[row-1][col];
        result += this->FieldOld[row-1][col+1];
        result += this->FieldOld[row][col+1];
        result += 0;
        result += 0;
        result += 0;
        result += 0;
        return result;
    } else if(col==0 and row>0 and row<(this->FieldHeight-1)) { // Left column
        result += 0;
        result += this->FieldOld[row-1][col];
        result += this->FieldOld[row-1][col+1];
        result += this->FieldOld[row][col+1];
        result += this->FieldOld[row+1][col+1];
        result += this->FieldOld[row+1][col];
        result += 0;
        result += 0;
        return result;
    } else { // All other cells, which are not at the edge
        result += this->FieldOld[row-1][col-1];
        result += this->FieldOld[row-1][col];
        result += this->FieldOld[row-1][col+1];
        result += this->FieldOld[row][col+1];
        result += this->FieldOld[row+1][col+1];
        result += this->FieldOld[row+1][col];
        result += this->FieldOld[row+1][col-1];
        result += this->FieldOld[row][col-1];
        return result;
    }
}
/*
 * This function calculates the next iteration of the game field
 *
 */
void GameOfLife::CalcNextIter(){
    int tempNeighbours;
    // Go throught al cells...
    for(int row=0;row<this->FieldHeight;row++){
        for(int col=0;col<this->FieldWidth;col++){
            // ...and check the number of neighbours to determine the next state of the cell
            tempNeighbours = GetNeighboursCount(row, col);
            if (this->FieldOld[row][col] == 0) { // Dead cell
                if (tempNeighbours == 3) {       // Zelle lebt
                                this->FieldNew[row][col] = 1;
                }
            } else {
                if (tempNeighbours < 2){                // Zelle stirbt
                    this->FieldNew[row][col] = 0;

                } else if (tempNeighbours <= 3){        // Zelle behält Zustand
                    this->FieldNew[row][col] = this->FieldOld[row][col];

                } else {                                // Zelle stirbt
                    this->FieldNew[row][col] = 0;
                }
            }
        }
    }
    // Copy the calculated result into the old array
    for(int i=0;i<this->FieldHeight;i++){
        for(int k=0;k<this->FieldWidth;k++){
            this->FieldOld[i][k] = this->FieldNew[i][k];
            this->FieldNew[i][k] = 0;
        }
    }

    return;
}
