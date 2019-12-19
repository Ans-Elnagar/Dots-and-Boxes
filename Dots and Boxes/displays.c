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
                loadUi();

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
                        plnameco();
                        startTime=time(NULL)-overtime;
                        uicomp();
                        /////////
                        break;
                    case 2:
                        numOfPlayers = 2;
                        plnamepl();
                        startTime=time(NULL)-overtime;
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
    strcpy(player2.name,"Computer");
    if (rounds%2!=player1.turn && relines != 0){
        computerMoves();
    }
    //display in screen
    printf("                TURN          REMAINING LINES          TIME   \n"
      "             \033[1;34m %-10s\033[0m             %d               %2d:%2d  \n",player1.name,relines,mins,secs);
    printf("            \033[1;33m!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\033[0m\n");
    printf("              \033[1;34m%-10s\033[0m                         \033[1;31mComputer\033[0m     \n"
           "              \033[1;34mMoves : %d \033[0m                         \033[1;31mMoves : %d \033[0m     \n"
           "              \033[1;34mScore : %d \033[0m                         \033[1;31mScore : %d \033[0m     \n",player1.name,player1.moves,player2.moves,player1.score,player2.score);
           printf("            \033[1;33m!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\033[0m\n");
           GridMenu();
           //here the grid
           ///////////////////
    printf("            press (50) undo ,(60) redo ,(70) save game ,(80) back to main menu ,(90) exit\n\n");
    while (relines != 0){
    printf("        enter your play(Row Col for the line) : ");
    m1=0;m2=0;
    int x=0,y=0;
    scanf("%d",&m1);
    switch (m1){
    case 0 :
        fgets(garbage,100,stdin);
        invalidInput();
        break;
    case 50:
        ///// undo operation /////
        if (rounds==1){
            printf("                There's no moves left to undo.\n");
        }
        else{
        unMakeChanges();
        uicomp();
        }
        break;
    case 60:
        ///// redo operation /////
        if (rounds < top){
            redoChanges();
            uicomp();
        }
        else {
            printf("                There's no moves to redo.\n");
        }
        break;
    case 70 :
        ///// save game /////
        printf("\n\n \033[1;33m"
           "choose one to save in : \n"
           "1. Game 1.\n"
           "2. Game 2.\n"
           "3. Game 3.\n\033[0m");
        savegu();
        break;
    case 80 :
        clearGameData();
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
    if (m1>gridSize||m1<=0||m2>gridSize||m2<=0||m1%2==m2%2){
        invalidInput();
      }
    else{
        x=m1-1;y=m2-1;
        if (x%2==0){
            if (grid[x][(y/2)+1]==1) invalidInput();
            else{
            top = rounds+1;
            makeChanges(x,y);
            }
        }
        else {
            if (grid[x][y/2]==1) invalidInput();
            else{
            top = rounds+1;
            makeChanges(x,y);
            }
        }

    }

      ////////////////
      break;

    }
}
    if (relines==0){
        if (player1.score>player2.score){
            strcpy(winner,player1.name);
            winnerScore=player1.score;
            printf("                               %s wins !!\n",winner);
        }
        else if (player2.score>player1.score){
            printf("                               Computer Wins !! Hard Luck !");
        }
        else if (player1.score==player2.score){
            printf("                               There's a tie,no one wins");
        }
        printf("\nEnter (80) to back to the main menu (90) to exit : ");
        int oo=0;
        l :
        oo=0;
        scanf("%d",&oo);
        switch (oo){
        case 80:
            clearGameData();
            MainMenu();
            break;
        case 90 :
            exit(EXIT_SUCCESS);
        case 0 :
        fgets(garbage,100,stdin);
        invalidInput();
        printf("\nenter again :");
        goto l;
        default :
            invalidInput();
            printf("\nenter again :");
            goto l;
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
        printf("              %-10s\033[0m           %d                 %2d:%2d  \n",player1.name,relines,mins,secs);
    }
    else if (rounds%2==player2.turn){
        redL();
        printf("              %-10s\033[0m           %d                 %2d:%2d  \n",player2.name,relines,mins,secs);
    }

    printf("            \033[1;33m!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\033[0m\n");
    printf("              \033[1;34m%-10s\033[0m                             \033[1;31m%-10s\033[0m     \n"
           "              \033[1;34mMoves : %d \033[0m                             \033[1;31mMoves : %d \033[0m     \n"
           "              \033[1;34mScore : %d \033[0m                             \033[1;31mScore : %d \033[0m     \n",player1.name,player2.name,player1.moves,player2.moves,player1.score,player2.score);
           printf("            \033[1;33m!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\033[0m\n");
           GridMenu();
           //here the grid
           //////////////
    printf("            press (50) undo ,(60) redo ,(70) save game ,(80) back to main menu ,(90) exit\n\n");
    while (relines != 0){
    m1=0;m2=0;
    int x=0,y=0;
    printf("        enter your play(Row Col for the line) : ");
    scanf("%d",&m1);
    switch (m1){
    case 0 :
        fgets(garbage,100,stdin);
        invalidInput();
        break ;
    case 50:if (rounds==1){
            printf("                There's no moves left to undo.");
        }
        else{
        unMakeChanges();
        uiplayer();
        }
        ///// undo operation /////
        break;
    case 60:
        if (rounds==top){
            printf("                There's no moves to redo.");
        }
        else {
            redoChanges();
            uiplayer();
        }
        ///// redo operation /////

        break;
    case 70 :
        ///// save game /////
        printf("\n\n \033[1;33m"
           "choose one to save in : \n"
           "1. Game 1.\n"
           "2. Game 2.\n"
           "3. Game 3\n\033[0m");
        savegu();
        break;
    case 80 :
        clearGameData();
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
      if (m1>gridSize||m1<=0||m2>gridSize||m2<=0||m1%2==m2%2){
        invalidInput();
      }
    else{
        x=m1-1;y=m2-1;
        if (x%2==0){
            if (grid[x][(y/2)+1]==1) invalidInput();
            else{
            top = rounds+1;
            makeChanges(x,y);
            }
        }
        else {
            if (grid[x][y/2]==1) invalidInput();
            else{
            top = rounds+1;
            makeChanges(x,y);
            }
        }

    }

      ////////////////
      break;

    }
}

    if (relines==0){
        if (player1.score>player2.score){
            strcpy(winner,player1.name);
            winnerScore=player1.score;
            printf("                               %s wins !!\n",winner);
        }
        else if (player2.score>player1.score){
            strcpy(winner,player2.name);
            winnerScore=player2.score;
            printf("                               %s Wins !!",winner);
        }
        else if (player1.score==player2.score){
            printf("                               There's a tie,no one wins");
        }
        printf("\nEnter (80) to back to the main menu (90) to exit : ");
        int oo=0;
        l :
        oo=0;
        scanf("%d",&oo);
        switch (oo){
        case 80:
            clearGameData();
            MainMenu();
            break;
        case 90 :
            exit(EXIT_SUCCESS);
        case 0 :
        fgets(garbage,100,stdin);
        invalidInput();
        printf("\nenter again :");
        goto l;
        default :
            invalidInput();
            printf("\nenter again :");
            goto l;
        }

    }
}
/***************************************************
* plnameco : getting player name in computer mode ***
****************************************************/
void plnameco(){
    system("cls");
    printf("\n\n\n""\033[1;31m"
           "            ##########################################################            \n"
           "            ##########################################################            \n"
           "            ##                                                      ##            \n"
           "            ##                \033[1;33m""Dots     and     Boxes                \033[1;31m##            \n"
           "            ##                                                      ##            \n"
           "            ##########################################################            \n"
           "            ##########################################################            \n"
           "\n\n\n\n""\033[1;33m"
           "                        Enter player 1 name (only 10 char) : \033[0m");
           getchar();
           readname(player1.name,10);
           removespaces(player1.name);
}
/********************************************************
* plnamepl : getting player names in two players mode ***
*********************************************************/
void plnamepl(){
    system("cls");
    printf("\n\n\n""\033[1;31m"
           "            ##########################################################            \n"
           "            ##########################################################            \n"
           "            ##                                                      ##            \n"
           "            ##                \033[1;33m""Dots     and     Boxes                \033[1;31m##            \n"
           "            ##                                                      ##            \n"
           "            ##########################################################            \n"
           "            ##########################################################            \n"
           "\n\n\n\n""\033[1;33m"
           "                        Enter player 1 name (only 10 char) : \033[0m");
    getchar();
    readname(player1.name,11);
    removespaces(player1.name);
    printf("                        \033[1;33mEnter player 2 name (only 10 char) : \033[0m");
    readname(player2.name,11);
    removespaces(player2.name);

}
void loadUi(){
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
           "                                choose the game you want to load: \n"
           "                                1. Game 1.\n"
           "                                2. Game 2.\n"
           "                                3. Game 3.\n"
           "                                \033[1;31m4. Back to main menu.\n\033[0m"
           "\n\n");
                printf("                                        ");
                int ch=0,found;
                invalidl :
                ch=0;
                scanf("%d",&ch);
                if (ch==1||ch==2||ch==3){
                    found=loadGames(ch);
                    if (found==0){
                        printf("There's no game here to be loaded, enter any character to continue");
                        getchar();
                        loadUi();
                    }
                    else if (found==1){
                        if (numOfPlayers==1){
                            uicomp();
                        }
                        else{
                            uiplayer();
                        }
                    }
                }
                else if (ch==4){
                    MainMenu();
                }
                else if (ch==0){
                    fgets(garbage,100,stdin);
                    invalidInput();
                    printf("enter your choice again : ");
                    goto invalidl;
                }
                else {
                    invalidInput();
                    printf("enter your choice again : ");
                    goto invalidl;
                }
}
//function to save game
void savegu(){
    int ch=0,found;
        scanf("%d",&ch);
        if (ch==1||ch==2||ch==3){
        found=save(ch);
        if (numOfPlayers==1){
            uicomp();
        }
        else {
            uiplayer();
        }

        }
        else if (ch==0){
        fgets(garbage,100,stdin);
        invalidInput();
        savegu();
        }
        else{
            invalidInput();
            savegu();
        }
}
void readname(char str[], int n) {
    int ch, i=0,no=0;
    while((ch=getchar()) != '\n'){
        if(i<n) {
            str[i++]=ch;
            no++;
            }
    }
    str[i]='\0';
    for (i=0;i<no;i++){
        str[i]=toupper(str[i]);
    }
    }
void removespaces(char str[]){
    int len,i,j;
    len=strlen(str);
	for(i=0; i<len; i++)
	{
		if(str[i]==' ')
		{
			for(j=i; j<len; j++)
			{
				str[j]=str[j+1];
			}
		len--;
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
