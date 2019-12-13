#ifndef DISPLAYS_H_INCLUDED
#define DISPLAYS_H_INCLUDED

void MainMenu();    void ModeMenu();
void redL();        void redB();
void blueL();       void blueB();
void reset();
void invalidInput();
void eHline();     void Hline();
void eVline();     void Vline();
extern int numOfPlayers;
extern int gridBoxes;

#endif // DISPLAYS_H_INCLUDED
