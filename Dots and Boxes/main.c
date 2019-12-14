#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "displays.h"
#include "processing.h"
int numOfPlayers; // 1 if against computer and 2 if two players
int gridSize;    // The biggest number written above the grid
int numOfBoxes; // number of boxes on the grid
int records[60][4];
bool grid[11][6];
int playerGrid[11][11];
int boxesGrid[5][5];
int main()
{
    MainMenu();
    exit(EXIT_SUCCESS);
}
