#ifndef PROCESSING_H_INCLUDED
#define PROCESSING_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "types.h"
#include "displays.h"
void makeChanges(int i, int j);
void unMakeChanges();
int save(int n);
void redoChanges();
void computerMoves();
void checkBoxes();
void undoBoxes();
void swapTurns();
void scoreInc();
void scoreDec();
void loadData(FILE *fptr);
int loadGames(int g);
void clearGameData();
void loadTop();
extern int numOfPlayers;
extern int gridSize;
extern int overtime;
extern int top; // the last index of redo array.
extern int records[60][4];
extern bool grid[11][6];
extern int playerGrid[11][6];
extern int boxesGrid[5][5];
extern int relines;
extern int overtime;
extern int avInd[60][2];
extern char topNames[10][30];
extern int topScores[10];
#endif // PROCESSING_H_INCLUDED
