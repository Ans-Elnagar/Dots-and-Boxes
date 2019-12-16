#include "displays.h"
/**********************************************************************
* MainMenu: first clears the console then draw the main menu screen ***
*         finally executing the user choice.                        ***
**********************************************************************/
void MainMenu(){
    system("cls");
    printf("\n\n\n""\033[1;31m"
           "            ##########################################################            \n"
           "            ##########################################################            \n"
           "            ##                                                      ##            \n"
           "            ##                \033[1;33m""Dots     and     Boxes                \033[1;31m##            \n"
           "            ##                                                      ##            \n"
           "            ##########################################################            \n"
           "            ##########################################################            \n"
           "\n\n""\033[1;33m"
           "                                Start a new game: \n"
           "                                    1. Beginner mode.  2x2\n"
           "                                    2. Expert mode.  5x5\n"
           "                                3. Load a game.\n"
           "                                4. Top 10 players.\n"
           "                                \033[1;31m5. Exit.\n\033[0m"
           "\n\n");
    int choice = 0;
    for (;;){
        printf("                                        ");
        scanf("%d",&choice);
        switch (choice){
            case 1:
                gridSize = 5;
                relines=12;
                numOfBoxes = 2;
                ModeMenu();
                break;
            case 2:
                gridSize = 11;
                relines=60;
                numOfBoxes = 5;
                ModeMenu();
                break;
            case 3:
                ///////////////
                ///////////////
                break;
            case 4:
                ///////////////
                ///////////////
                break;
            case 5:
                exit(EXIT_SUCCESS);
            case 0:
                fgets(garbage,100,stdin);
            default:
                invalidInput();
        }
    }
}
/**********************************************************************
* ModeMenu: first clear the console then draw the mode menu screen.****
**********************************************************************/
void ModeMenu(){
    system("cls");
    printf("\n\n\n""\033[1;31m"
           "            ##########################################################            \n"
           "            ##########################################################            \n"
           "            ##                                                      ##            \n"
           "            ##                \033[1;33m""Dots     and     Boxes                \033[1;31m##            \n"
           "            ##                                                      ##            \n"
           "            ##########################################################            \n"
           "            ##########################################################            \n"
           "\n\n""\033[1;33m"
           "                                Select number of players: \n"
           "                                    1. One Player.\n"
           "                                    2. Two Players.\n"
           "                                \033[1;31m3. Back.\n\033[0m\n\n");
           int choice = 0;
           for (;;){
                printf("                                        ");
                scanf("%d",&choice);
                switch(choice){
                case 1:
                        numOfPlayers = 1;
                        startTime=time(NULL);
                        uicomp();
                        /////////
                        break;
                    case 2:
                        numOfPlayers = 2;
                        startTime=time(NULL);
                        uiplayer();
                        ////////
                        ////////
                        break;
                    case 3:
                        MainMenu();
                        break;
                    case 0:
                        fgets(garbage,100,stdin);
                    default:
                        invalidInput();
               }
           }

}
void GridMenu(){
    if (numOfBoxes == 2){
        printf("                                  ");
    } else {
        printf("                           ");
    }
    for (int i=0; i<gridSize;i++){
        printf("%d ",i+1);
    }
    for (int i=0; i<gridSize; i++){ // checks if i is 2 digits, So not to move rows of the grid
        if (numOfBoxes == 2){
            printf("\n                             ");
        } else {
            printf("\n                      ");
        }
        if (i/9){ // Notice i starts of 0
            printf("   %d",i+1);
        }
        else{
            printf("    %d",i+1);
        }
        for (int j=(i+1)%2; j<=numOfBoxes; j++){
            if (i%2==0){
                // This part is for dots and horizontal lines
                dotShape();
                if (grid[i][j] == true){
                    switch (playerGrid[i][j]){
                        case 1:
                            blueL();
                            Hline();
                            break;
                        case 2:
                            redL();
                            Hline();
                            break;
                    }
                }
                else {
                    eHline();
                }
                if (j == numOfBoxes){
                    dotShape();
                }
            }
            // This part is for vertical lines and colored cells
            else {
                if (grid[i][j] == true){
                    switch (playerGrid[i][j]){
                        case 1:
                            blueL();
                            Vline();
                            break;
                        case 2:
                            redL();
                            Vline();
                            break;
                    }
                }
                else {
                    eVline();
                }
                if (j != numOfBoxes){
                    switch(boxesGrid[i/2][j]){
                        case 1:
                            blueB();
                            break;
                        case 2:
                            redB();
                            break;
                        default :
                            emptyB();
                    }
                }
            }
        }
    }
    printf("\n");
}
//function to display user interface if he plays with computer
void uicomp(){
    system("cls");
    int m1=0,m2=0;
    //time in minutes and seconds
    int f;
    time_t t1;
    int mins,secs;
    t1=time(NULL);
    t1=t1-startTime;
    mins=t1/60;secs=t1%60;
    //display in screen
    printf("                TURN          REMAINING LINES          TIME   \n"
      "             \033[1;34m Player 1\033[0m              %d                 %2d:%2d  \n",relines,mins,secs);
    printf("            \033[1;33m!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\033[0m\n");
    printf("              \033[1;34mPlayer 1\033[0m                           \033[1;31mComputer\033[0m     \n"
           "              \033[1;34mMoves : %d \033[0m                         \033[1;31mMoves : %d \033[0m     \n"
           "              \033[1;34mScore : %d \033[0m                         \033[1;31mScore : %d \033[0m     \n",player1.moves,player2.moves,player1.score,player2.score);
           printf("            \033[1;33m!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\033[0m\n");
           GridMenu();
           //here the grid
           ///////////////////
    printf("            press (50) undo ,(60) redo ,(70) save game ,(80) back to main menu ,(90) exit\n");
    for (;;){
    printf("        enter your play(Row Col for the line) : ");
    m1=0;m2=0;
    scanf("%d",&m1);
    switch (m1){
    case 0 :
        fgets(garbage,100,stdin);
        invalidInput();
        break;
    case 50:
        ///// undo operation /////
        break;
    case 60:
        ///// redo operation /////
        break;
    case 70 :
        ///// save game /////
        break;
    case 80 :
        MainMenu();
        break;
    case 90 :
        exit(EXIT_SUCCESS);
    default :
      if (scanf("%d",&m2)!=1){
        fgets(garbage,100,stdin);
        invalidInput();
        break;
      }

      ////////////////
      break;

    }
}
}
//function to display user interface if he plays with another player
void uiplayer(){
    system("cls");
    int m1=0,m2=0;
    //time in minutes and seconds
    int f;
    time_t t1;
    int mins,secs;
    t1=time(NULL);
    t1=t1-startTime;
    mins=t1/60;secs=t1%60;
    //display in screen


    printf("                TURN          REMAINING LINES          TIME   \n");
    if (rounds%2==player1.turn){
        blueL();
        printf("              %s\033[0m              %d                 %2d:%2d  \n",player1.name,relines,mins,secs);
    }
    else if (rounds%2==player2.turn){
        redL();
        printf("              %s\033[0m              %d                 %2d:%2d  \n",player2.name,relines,mins,secs);
    }

    printf("            \033[1;33m!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\033[0m\n");
    printf("              \033[1;34mPlayer 1\033[0m                               \033[1;31mPlayer 2\033[0m     \n"
           "              \033[1;34mMoves : %d \033[0m                             \033[1;31mMoves : %d \033[0m     \n"
           "              \033[1;34mScore : %d \033[0m                             \033[1;31mScore : %d \033[0m     \n",player1.moves,player2.moves,player1.score,player2.score);
           printf("            \033[1;33m!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\033[0m\n");
           GridMenu();
           //here the grid
           //////////////
    printf("            press (50) undo ,(60) redo ,(70) save game ,(80) back to main menu ,(90) exit\n");
    for (;;){
    m1=0;m2=0;
    printf("        enter your play(Row Col for the line) : ");
    scanf("%d",&m1);
    switch (m1){
    case 0 :
        fgets(garbage,100,stdin);
        invalidInput();
        break ;
    case 50:
        ///// undo operation /////
        break;
    case 60:
        ///// redo operation /////
        break;
    case 70 :
        ///// save game /////
        break;
    case 80 :
        MainMenu();
        break;
    case 90 :
        exit(EXIT_SUCCESS);
    default :
      if (scanf("%d",&m2)!=1){
        fgets(garbage,100,stdin);
        invalidInput();
        break;
      }

      ////////////////
      break;

    }
}
}
/**************************************
* redL : every text after it is red ***
**************************************/
void redL(){
    printf("\033[1;31m");
}
/*******************************
* redB : Background turn red ***
*******************************/
void redB(){
    printf("\033[41m 2 \033[0m");
}
/****************************************
* blueL : every text after it is blue ***
****************************************/
void blueL(){
    printf("\033[1;34m");
}
/*********************************
* blueB : Background turn blue ***
*********************************/
void blueB(){
    printf("\033[44m 1 \033[0m");
}
/******************************
* emptyB : empty background ***
******************************/
void emptyB(){
    printf("   ");
}
/******************************************************************
* reset : remove the properties of text or background before it ***
******************************************************************/
void reset(){
    printf("\033[0m");
}
/***********************************************
*** invalidInput : printing an error message ***
***********************************************/
void invalidInput(){
    redL();
    printf("\n                                   invalid input          \n");
    reset();
}
/**************************************************************************
*** dotShape : printing the dot shape so it can be changed at any time ***
**************************************************************************/
void dotShape(){
    printf("\376");
}
/*******************************************
*** eHline : draws empty horizontal line ***
*******************************************/
void eHline(){
    printf("   ");
}
/************************************
*** Hline : draws horizontal line ***
************************************/
void Hline(){
    printf("\304\304\304");
    reset();
}
/*****************************************
*** eVline : draws empty vertical line ***
*****************************************/
void eVline(){
    printf(" ");
}
/**********************************
*** Vline : draws Vertical line ***
**********************************/
void Vline(){
    printf("\263");
    reset();
}
