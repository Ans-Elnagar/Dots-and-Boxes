#include "processing.h"
void makeChanges(int i, int j){
    records[rounds][0] = i;
    records[rounds][1] = j;
    if (i%2 == 0){
        grid[i][(j/2)+1] = true;
        if (rounds%2 == player1.turn){
            records[rounds][2] = 1;
            playerGrid[i][(j/2)+1] = 1;
        } else {
            records[rounds][2] = 2;
            playerGrid[i][(j/2)+1] = 2;
        }
    } else {
        grid[i][j/2] = true;
        if (rounds%2 == player1.turn){
            records[rounds][2] = 1;
            playerGrid[i][j/2] = 1;
        } else {
            records[rounds][2] = 2;
            playerGrid[i][j/2] = 2;
        }
    }
    if (rounds%2 == player1.turn){
        player1.moves++;
    }
    else {
        player2.moves++;
    }
    checkBoxes(i,j);
    relines--;
    rounds++;
    if (numOfPlayers == 1)
        {
        uicomp();
    }else {
        uiplayer();
    }
}

int save(int n){
    FILE *game;
    switch (n){
        case 1:
            game = fopen("savedGames/Game1.txt","r");
            break;
        case 2:
            game = fopen("savedGames/Game2.txt","r");
            break;
        case 3:
            game = fopen("savedGames/Game3.txt","r");
            break;
    }
    int isSaved;
    fscanf(game,"%d",&isSaved);
    if (isSaved == 1){
        printf("\n        There is a game already saved here do you want to over write it ?\n");
        printf("\n                                        1- Yes");
        printf("\n                                        2- No");
        int choice;
        do {
        choice = 0;
        scanf("%d",&choice);
        switch (choice) {
            case 1:
                break;
            case 2:
                return 0;
            case 0:
                fgets(garbage,100,stdin);
            default:
                invalidInput();
            }
        } while (choice != 1);
    fclose(game);
    }
    switch (n){
        case 1:
            game = fopen("savedGames/Game1.txt","w");
            break;
        case 2:
            game = fopen("savedGames/Game2.txt","w");
            break;
        case 3:
            game = fopen("savedGames/Game3.txt","w");
            break;
    }
    fprintf(game,"1\n");
    fprintf(game,"%s\n",player1.name);
    fprintf(game,"%d\n",player1.score);
    fprintf(game,"%d\n",player1.turn);
    fprintf(game,"%s\n",player2.name);
    fprintf(game,"%d\n",player2.score);
    fprintf(game,"%d\n",player2.turn);
    fprintf(game,"%d\n%d\n%d\n%d\n%d\n",rounds,relines,numOfBoxes,gridSize,numOfPlayers);
    for (int i=0; i<11; i++){
        for (int j=0; j<6; j++){
            fprintf(game,"%d ",playerGrid[i][j]);
        }
        fprintf(game,"\n");
    }
    for (int i=0; i<5; i++){
        for (int j=0; j<5; j++){
            fprintf(game,"%d ",boxesGrid[i][j]);
        }
        fprintf(game,"\n");
    }
    for (int i=0; i<60; i++){
        for (int j=0; j<4; j++){
            fprintf(game,"%d ",records[i][j]);
        }
        fprintf(game,"\n");
    }
    fprintf(game,"%d\n",top);
    int t = time(NULL);
    int timeTillNow = t - startTime;
    fprintf(game,"%d\n",timeTillNow);
    fclose(game);
    return 1;
}


void unMakeChanges(){
    rounds--;
    relines++;
    int i = records[rounds][0];
    int j = records[rounds][1];
    if (i%2 == 0){
        grid[i][(j/2)+1] = false;
        playerGrid[i][(j/2)+1] = 0;
    }
    else {
        grid[i][j/2] = false;
        playerGrid[i][j/2] = 0;
    }
    if (records[rounds][2] == 1){
        player1.moves--;
    }
    else {
        player2.moves--;
    }
    undoBoxes(i,j);
}
void redoChanges(){
    int i,j,turn;
    i = records[rounds][0];
    j = records[rounds][1];
    turn = records[rounds][2];
    if (i%2 == 0){
        grid[i][(j/2)+1] = true;
        if (turn == 1){
            playerGrid[i][(j/2)+1] = 1;
        } else {
            playerGrid[i][(j/2)+1] = 2;
        }
    } else {
        grid[i][j/2] = true;
        if (turn == 1){
            playerGrid[i][j/2] = 1;
        } else {
            playerGrid[i][j/2] = 2;
        }
    }
    if (turn == 1){
        player1.moves++;
    }
    else {
        player2.moves++;
    }
    checkBoxes(i,j);
    relines--;
    rounds++;
}

void initializingExpert()
{
    int i,j;
    for(i=0;i<11;i++)
    {
        for(j=0;j<6;j++)
        {
            grid[i][j]=1;
        }
    }
    //making exceptions
    for(i=0;i<11;i++)
    {
        for(j=0;j<6;j++)
            {
                if(j==0 && i%2==0)
                {
                    grid[i][j]=0;
                }
            }
    }
}
void computerMoves()
{
    int h=0;
    /*avInd[relines][2];*/
    int i,j;
    for(i=0;i<gridSize;i++)
    {
        for(j=(i+1)%2;j<=numOfBoxes;j++)
        {
            if(grid[i][j]==0)
            {
                avInd[h][0]=i;
                avInd[h][1]=j;
                h++;
            }
        }
    }
    srand(time(NULL));
    int r=rand()%relines;
    int a=avInd[r][0];
    int b=avInd[r][1];
    if(a%2==0)
    {
        b=(b-1)*2;
    } else
    {
        b=b*2;
    }
    makeChanges(a,b);
    // Check for closed box //
}
void scoreInc(int turn)
{
    if (turn==player1.turn)
    {
        player1.score++;
    } else if (turn==player2.turn)
    {
        player2.score++;
    }
}
void scoreDec(int turn)
{
    if (turn==player1.turn)
    {
        player1.score--;
    } else if (turn==player2.turn)
    {
        player2.score--;
    }
}
void swapTurns()
{
    int temp =player1.turn;
    player1.turn=player2.turn;
    player2.turn=temp;
}
void checkBoxes(int i,int j)
{
    int turn = rounds%2;
    if (i%2==0)
    {
        j=(j/2)+1;
        if (i==0)
        {
            //checking the box under
            if(grid[1][j]==1 && grid[1][j-1]==1 && grid[2][j]==1)
            {
                scoreInc(turn);
                if (turn==player1.turn)
                {
                    boxesGrid[0][j-1]=1;
                } else
                {
                    boxesGrid[0][j-1]=2;
                }
                records[rounds][3]++;
                swapTurns();
            }

        } else if (i==(gridSize-1))
        {
            //checking the box above
            if(grid[i-1][j]==1 && grid[i-1][j-1]==1 && grid[i-2][j]==1)
            {
                scoreInc(turn);
                if (turn==player1.turn)
                {
                    boxesGrid[(i/2)-1][j-1]=1;
                } else
                {
                    boxesGrid[(i/2)-1][j-1]=2;
                }
                records[rounds][3]++;
                swapTurns();
            }

        } else
        {
            //checking the box under
            if(grid[i+1][j]==1 && grid[i+1][j-1]==1 && grid[i+2][j]==1)
            {
                scoreInc(turn);
                if (turn==player1.turn)
                {
                    boxesGrid[(i/2)][j-1]=1;
                } else
                {
                    boxesGrid[(i/2)][j-1]=2;
                }
                records[rounds][3]++;
            }
            //checking the box above
            if(grid[i-1][j]==1 && grid[i-1][j-1]==1 && grid[i-2][j]==1)
            {
                scoreInc(turn);
                if (turn==player1.turn)
                {
                    boxesGrid[(i/2)-1][j-1]=1;
                } else
                {
                    boxesGrid[(i/2)-1][j-1]=2;
                }
                records[rounds][3]++;
            }
            //swapping turns of any of the two boxes were closed
            if((grid[i+1][j]==1 && grid[i+1][j-1]==1 && grid[i+2][j]==1) ||(grid[i+1][j]==1 && grid[i+1][j-1]==1 && grid[i+2][j]==1))
            {
                swapTurns();
            }
        }

    } else
    {
        j=j/2;
        if (j==0)
        {
            //checking the box on the right
            if(grid[i+1][j+1] ==1 && grid[i-1][j+1]==1 && grid[i][j+1]==1)
            {
                scoreInc(turn);
                if (turn==player1.turn)
                {
                    boxesGrid[i/2][j]=1;
                } else
                {
                    boxesGrid[i/2][j]=2;
                }
                records[rounds][3]++;
                swapTurns();
            }

        } else if (j==numOfBoxes)
        {
            //checking the box on the left
            if(grid[i+1][j]==1 && grid[i-1][j]==1 && grid[i][j-1]==1)
            {
                scoreInc(turn);
                if (turn==player1.turn)
                {
                    boxesGrid[i/2][j-1]=1;
                } else
                {
                    boxesGrid[i/2][j-1]=2;
                }
                records[rounds][3]++;
                swapTurns();
            }

        } else
        {
            //checking the box on the right
            if(grid[i+1][j+1] ==1 && grid[i-1][j+1]==1 && grid[i][j+1]==1)
            {
                scoreInc(turn);
                if (turn==player1.turn)
                {
                    boxesGrid[i/2][j]=1;
                } else
                {
                    boxesGrid[i/2][j]=2;
                }
                records[rounds][3]++;
            }
            //checking the box on the left
            if(grid[i+1][j]==1 && grid[i-1][j]==1 && grid[i][j-1]==1)
            {
                scoreInc(turn);
                if (turn==player1.turn)
                {
                    boxesGrid[i/2][j-1]=1;
                } else
                {
                    boxesGrid[i/2][j-1]=2;
                }
                records[rounds][3]++;
            }
            //swapping turns if any of the two boxes was closed
            if((grid[i+1][j+1] ==1 && grid[i-1][j+1]==1 && grid[i][j+1]==1) || (grid[i+1][j]==1 && grid[i-1][j]==1 && grid[i][j-1]==1) )
            {
                swapTurns();
            }

        }
    }
}
void undoBoxes(int i,int j)
{
    int turn = rounds%2;
    if (i%2==0)
    {
        j=(j/2)+1;
        if (i==0)
        {
            //checking the box under
            if (boxesGrid[0][j-1]!=0)
            {
                swapTurns();
                scoreDec(turn);
            }
            boxesGrid[0][j-1]=0;
        } else if (i==(gridSize-1))
        {
            //checking the box above
            if (boxesGrid[(i/2)-1][j-1]!=0)
            {
                swapTurns();
                scoreDec(turn);
            }
            boxesGrid[(i/2)-1][j-1]=0;
        } else
        {
            //swapping turns of any of the two boxes were closed
            if(boxesGrid[(i/2)][j-1]!=0 ||boxesGrid[(i/2)-1][j-1]!=0)
            {
                swapTurns();
            }
            //checking the box under
            if (boxesGrid[(i/2)][j-1]!=0)
            {
                scoreDec(turn);
            }
            //checking the box above
            if (boxesGrid[(i/2)-1][j-1]!=0)
            {
                scoreDec(turn);
            }
            boxesGrid[(i/2)][j-1]=0;
            boxesGrid[(i/2)-1][j-1]=0;
        }

    } else
    {
        j=j/2;
        if (j==0)
        {
            //checking the box on the right
            if(boxesGrid[i/2][j]!=0)
            {
                swapTurns();
                scoreDec(turn);
            }
            boxesGrid[i/2][j]=0;
        } else if (j==numOfBoxes)
        {
            //checking the box on the left
            if(boxesGrid[i/2][j-1]!=0)
            {
                swapTurns();
                scoreDec(turn);
            }
            boxesGrid[i/2][j-1]=0;
        } else
        {
            //swapping turns if any of the two boxes was closed
            if((boxesGrid[i/2][j]!=0) || (boxesGrid[i/2][j-1]!=0) )
            {
                swapTurns();
            }
            //checking the box on the right
            if(boxesGrid[i/2][j]!=0)
            {
                scoreDec(turn);
            }
            //checking the box on the left
            if(boxesGrid[i/2][j-1]!=0)
            {
                scoreDec(turn);
            }
            boxesGrid[i/2][j]=0;
            boxesGrid[i/2][j-1]=0;
        }
    }
}
void loadData(FILE *fptr)
{
    int x,y;
    fscanf(fptr,"%s",player1.name);
    fscanf(fptr,"%d",&player1.score);
    fscanf(fptr,"%d",&player1.turn);
    fscanf(fptr,"%s",player2.name);
    fscanf(fptr,"%d",&player2.score);
    fscanf(fptr,"%d",&player2.turn);
    fscanf(fptr,"%d",&rounds);
    fscanf(fptr,"%d",&relines);
    fscanf(fptr,"%d",&numOfBoxes);
    fscanf(fptr,"%d",&gridSize);
    fscanf(fptr,"%d",&numOfPlayers);
    for(x=0;x<11;x++)
    {
        for(y=0;y<6;y++)
        {
            fscanf(fptr,"%d",&playerGrid[x][y]);
            if(playerGrid[x][y]!=0)
            {
                grid[x][y]=true;
            }
        }
    }
    for(x=0;x<5;x++)
    {
        for(y=0;y<5;y++)
        {
            fscanf(fptr,"%d",&boxesGrid[x][y]);
        }
    }
    for(x=0;x<60;x++)
    {
        for(y=0;y<4;y++)
        {
            fscanf(fptr,"%d",&records[x][y]);
        }
    }
    fscanf(fptr,"%d",&top);
    fscanf(fptr,"%d",&overtime);
}
int loadGames(int g)
{
    FILE *fptr;
    int i;
    switch (g)
    {
        case 1:
            fptr=fopen("savedGames/Game1.txt","r");
            fscanf(fptr,"%d",&i);
            if(i==1)
            {
                loadData(fptr);
                return 1;

            } else
            {
                return 0;
            }
            break;
        case 2:
            fptr=fopen("savedGames/Game2.txt","r");
            fscanf(fptr,"%d",&i);
            if(i==1)
            {
                loadData(fptr);
                return 1;

            } else
            {
                return 0;
            }
            break;
        case 3:
            fptr=fopen("savedGames/Game3.txt","r");
            fscanf(fptr,"%d",&i);
            if(i==1)
            {
                loadData(fptr);
                return 1;

            } else
            {
                return 0;
            }
            break;
    }
    return 0;
}
void clearGameData()
{
    int i,j;
    player1.score=0;
    player1.turn=1;
    player1.moves=0;
    player2.score=0;
    player2.score=0;
    player2.moves=0;
    rounds=1;
    for(i=0;i<11;i++)
    {
        for(j=0;j<6;j++)
        {
            playerGrid[i][j]=0;
        }
    }
    for(i=0;i<11;i++)
    {
        for(j=0;j<6;j++)
        {
            grid[i][j]=false;
        }
    }
    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {
            boxesGrid[i][j]=0;
        }
    }
    for(i=0;i<60;i++)
    {
        for(j=0;j<4;j++)
        {
            records[i][j]=0;
        }
    }
    top=0;
}
void loadTop()
{
    FILE *top10;
    top10=fopen("Top10.txt","r");
    for(int i=0;i<10;i++)
    {
        fscanf(top10,"%s",topNames[i]);
        fscanf(top10,"%d",&topScores[i]);
    }
}



