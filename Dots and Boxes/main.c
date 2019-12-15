#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "displays.h"
#include "processing.h"
#include "types.h"
int numOfPlayers; // 1 if against computer and 2 if two players
int gridSize;    // The biggest number written above the grid
int numOfBoxes; // number of boxes on the grid
int relines=0,startTime=0,rounds=1;
int records[60][4];
bool grid[11][6];
int playerGrid[11][11];
int boxesGrid[5][5];
player player1={"Player 1","Blue",0,1,0},player2={"Player 2","Red",0,0,0};
char garbage[100];
int avInd[60][2];
int main()
{

    MainMenu();
    exit(EXIT_SUCCESS);
}
