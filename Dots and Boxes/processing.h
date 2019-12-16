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
void computerMoves();
extern int numOfPlayers;
extern int gridSize;
extern int top; // the last index of redo array.
extern int records[60][4];
extern bool grid[11][6];
extern int playerGrid[11][6];
extern int boxesGrid[5][5];
extern int relines;
extern int avInd[60][2];

#endif // PROCESSING_H_INCLUDED
