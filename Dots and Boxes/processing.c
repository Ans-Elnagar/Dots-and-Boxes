#include "processing.h"
void makeChanges(int i, int j){
    records[rounds][0] = i;
    records[rounds][1] = j;
    records[rounds][3] = 0;
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
        printf("\n                                        2- No\n");
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
    fprintf(game,"%d\n",player1.moves);
    fprintf(game,"%s\n",player2.name);
    fprintf(game,"%d\n",player2.score);
    fprintf(game,"%d\n",player2.turn);
    fprintf(game,"%d\n",player2.moves);
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
        for (int j=0; j<8; j++){
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
        player1.score -= records[rounds][3];
    }
    else {
        player2.moves--;
        player2.score -= records[rounds][3];
    }
    switch (records[rounds][3]){
        case 1 :
            boxesGrid [records[rounds][4]][records[rounds][5]] = 0;
            swapTurns();
            break;
        case 2:
            boxesGrid [records[rounds][4]][records[rounds][5]] = 0;
            boxesGrid [records[rounds][6]][records[rounds][7]] = 0;
            swapTurns();
            break;
        default:
            break;
    }
    if ( rounds > 0 && records[rounds][2] == 2 && numOfPlayers == 1){
        unMakeChanges();
    }
}
void redoChanges(){
    /*int i,j,turn;
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
    checkBoxes(i,j);*/
    int i = records[rounds][0];
    int j = records[rounds][1];
    if (i%2 == 0){
        grid[i][(j/2)+1] = true;
        playerGrid[i][(j/2)+1] = records[rounds][2];
    }
    else {
        grid[i][j/2] = true;
        playerGrid[i][j/2] = records[rounds][2];
    }
    if (records[rounds][2] == 1){
        player1.moves++;
        player1.score += records[rounds][3];
    }
    else {
        player2.moves++;
        player2.score += records[rounds][3];
    }
    switch (records[rounds][3]){
        case 1 :
            boxesGrid [records[rounds][4]][records[rounds][5]] = records[rounds][2];
            swapTurns();
            break;
        case 2:
            boxesGrid[records[rounds][4]][records[rounds][5]] = records[rounds][2];
            boxesGrid[records[rounds][6]][records[rounds][7]] = records[rounds][2];
            swapTurns();
            break;
        default:
            break;
    }
    relines--;
    rounds++;
    if ( rounds < top && (records[rounds-1][2] == 1 || (records[rounds-1][2] == 2 && rounds == top-1) || (records[rounds-1][2] == 2 && records[rounds][2] == 2) ) && numOfPlayers == 1){
        redoChanges();
    }
}

void computerMoves()
{
    int h=0;
    int i,j,a,b;
    int l=1;
    for(i=0;i<gridSize;i++)
    {
        for(j=(i+1)%2;j<=numOfBoxes;j++)
        {
            if(grid[i][j]==0)
            {
                avInd[h][0]=i;
                avInd[h][1]=j;
                h++;
                if (i%2==0)
                {
                    if (i==0)
                    {
                        //checking the box under
                        if(grid[1][j]==1 && grid[1][j-1]==1 && grid[2][j]==1)
                        {
                            a=i;
                            b=j;
                            l=0;
                            break;
                        }

                    } else if (i==(gridSize-1))
                    {
                        //checking the box above
                        if(grid[i-1][j]==1 && grid[i-1][j-1]==1 && grid[i-2][j]==1)
                        {
                            a=i;
                            b=j;
                            l=0;
                            break;
                        }

                    } else
                    {
                        //checking the box under and the box above
                        if((grid[i+1][j]==1 && grid[i+1][j-1]==1 && grid[i+2][j]==1) ||(grid[i-1][j]==1 && grid[i-1][j-1]==1 && grid[i-2][j]==1))
                        {
                            a=i;
                            b=j;
                            l=0;
                            break;
                        }
                    }

                } else
                {
                    if (j==0)
                    {
                        //checking the box on the right
                        if(grid[i+1][j+1] ==1 && grid[i-1][j+1]==1 && grid[i][j+1]==1)
                        {
                            a=i;
                            b=j;
                            l=0;
                            break;
                        }

                    } else if (j==numOfBoxes)
                    {
                        //checking the box on the left
                        if(grid[i+1][j]==1 && grid[i-1][j]==1 && grid[i][j-1]==1)
                        {
                            a=i;
                            b=j;
                            l=0;
                            break;
                        }

                    } else
                    {
                        //checking the box on the right and on the left
                        if((grid[i+1][j+1] ==1 && grid[i-1][j+1]==1 && grid[i][j+1]==1) || (grid[i+1][j]==1 && grid[i-1][j]==1 && grid[i][j-1]==1) )
                        {
                            a=i;
                            b=j;
                            l=0;
                            break;
                        }

                    }
                }
            }
        }
        if(l==0)
            break;
    }
    if(l==1)
    {
        srand(time(NULL));
        int r=rand()%relines;
        a=avInd[r][0];
        b=avInd[r][1];
    }
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
/*void scoreDec(int turn)
{
    if (turn==player1.turn)
    {
        player1.score--;
    } else if (turn==player2.turn)
    {
        player2.score--;
    }
}*/
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
                records[rounds][3] = 1;
                records[rounds][4] = 0;
                records[rounds][5] = j-1;
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
                records[rounds][3] = 1;
                records[rounds][4] = (i/2)-1;
                records[rounds][5] = j-1;
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
                swapTurns();
                records[rounds][3] = 1;
                records[rounds][4] = i/2;
                records[rounds][5] = j-1;
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
                swapTurns();
                records[rounds][3] = 1;
                records[rounds][4] = (i/2)-1;
                records[rounds][5] = j-1;
            }
            //swapping turns of any of the two boxes were closed
            if((grid[i+1][j]==1 && grid[i+1][j-1]==1 && grid[i+2][j]==1) &&(grid[i-1][j]==1 && grid[i-1][j-1]==1 && grid[i-2][j]==1))
            {
                swapTurns();
                records[rounds][3] = 2;
                records[rounds][4] = i/2;
                records[rounds][5] = j-1;
                records[rounds][6] = (i/2)-1;
                records[rounds][7] = j-1;
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
                records[rounds][3] = 1;
                records[rounds][4] = i/2;
                records[rounds][5] = j;
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
                records[rounds][3] = 1;
                records[rounds][4] = i/2;
                records[rounds][5] = j-1;
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
                swapTurns();
                records[rounds][3] = 1;
                records[rounds][4] = i/2;
                records[rounds][5] = j;
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
                swapTurns();
                records[rounds][3] = 1;
                records[rounds][4] = i/2;
                records[rounds][5] = j-1;
            }
            //swapping turns if any of the two boxes was closed
            if((grid[i+1][j+1] ==1 && grid[i-1][j+1]==1 && grid[i][j+1]==1) && (grid[i+1][j]==1 && grid[i-1][j]==1 && grid[i][j-1]==1) )
            {
                swapTurns();
                records[rounds][3] = 2;
                records[rounds][4] = i/2;
                records[rounds][5] = j;
                records[rounds][6] = i/2;
                records[rounds][7] = j-1;
            }

        }
    }
}
/*void undoBoxes(int i,int j)
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
}*/
void loadData(FILE *fptr)
{
    int x,y;
    fscanf(fptr,"%s",player1.name);
    fscanf(fptr,"%d",&player1.score);
    fscanf(fptr,"%d",&player1.turn);
    fscanf(fptr,"%d",&player1.moves);
    fscanf(fptr,"%s",player2.name);
    fscanf(fptr,"%d",&player2.score);
    fscanf(fptr,"%d",&player2.turn);
    fscanf(fptr,"%d",&player2.moves);
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
        for(y=0;y<8;y++)
        {
            fscanf(fptr,"%d",&records[x][y]);
        }
    }
    fscanf(fptr,"%d",&top);
    fscanf(fptr,"%d",&overtime);
    startTime = time(NULL);
    startTime -= overtime;
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
        fscanf(top10,"%s",&topNames[i]);
        fscanf(top10,"%d",&topScores[i]);
    }
}
void updateTop()
{
    int i;
    int l=1;
    for(i=0;i<10;i++)
    {
        if(strcmp(winner,topNames[i])==0)
        {
            if(winnerScore>topScores[i])
            {
                topScores[i]=winnerScore;
                l=0;
            }
        }
    }
    if (l==1)
    {
        for(i=0;i<10;i++)
        {
            if(winnerScore>=topScores[i])
            {
                for (int j=9;j>i;j--)
                {
                    strcpy(topNames[j],topNames[j-1]);
                    topScores[j]=topScores[j-1];
                }
                strcpy(topNames[i],winner);
                topScores[i]=winnerScore;
                break;
            }
        }
    }
}
void saveTop()
{
    FILE *top10;
    top10=fopen("Top10.txt","w");
    for(int i=0;i<10;i++)
    {
        fprintf(top10,"%s\n",topNames[i]);
        fprintf(top10,"%d\n",topScores[i]);
    }
}



