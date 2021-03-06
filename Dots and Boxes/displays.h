#ifndef DISPLAYS_H_INCLUDED
#define DISPLAYS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include "processing.h"
#include "types.h"
void MainMenu();    void ModeMenu();
void uicomp();      void uiplayer();
void loadUi();      void plnameco();
void plnamepl();    void savegu();
void redL();        void redB();
void blueL();       void blueB();
void reset();
void invalidInput();
void dotShape();
void emptyB();
void eHline();     void Hline();
void eVline();     void Vline();
void topUi();
extern int numOfPlayers;
extern int gridSize;
extern int numOfBoxes;
extern int overtime;
extern int top; // the last index of redo array.
extern int records[62][20];
extern bool grid[11][6];
extern int playerGrid[11][6];
extern int boxesGrid[5][5];
extern int rounds;
extern int relines,startTime;
extern player player1,player2;
extern char garbage[100];
extern int avInd[60][2];
extern char topNames[10][11];
extern int topScores[10];
extern char winner[10];
extern int winnerScore;
#endif // DISPLAYS_H_INCLUDED
