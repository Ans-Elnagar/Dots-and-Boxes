#ifndef DISPLAYS_H_INCLUDED
#define DISPLAYS_H_INCLUDED
void MainMenu();    void ModeMenu();
void redL();        void redB();
void blueL();       void blueB();
void reset();
void invalidInput();
void dotShape();
void emptyB();
void eHline();     void Hline();
void eVline();     void Vline();
extern int numOfPlayers;
extern int gridSize;
extern int numOfBoxes;
extern int records[60][4];
extern bool grid[11][6];
extern int playerGrid[11][11];
extern int boxesGrid[5][5];
#endif // DISPLAYS_H_INCLUDED
