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
    checkBoxes(i,j);
    if (rounds%2 == player1.turn){
        player1.moves++;
    }
    else {
        player2.moves++;
    }
    relines--;
    rounds++;
    if (numOfPlayers == 1)
        {
        uicomp();
    }else {
        uiplayer();
    }
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
    avInd[relines][2];
    int i,j;
    for(i=0;i<11;i++)
    {
        for(j=(i+1)%2;j<6;j++)
        {
            switch (grid[i][j])
            {
                case 0:
                    avInd[h][0]=i;
                    avInd[h][1]=j;
                    h++;
                    break;
                default:
                    break;
            }
        }
    }
    srand(time(NULL));
    int r=rand()%relines;
    int a=avInd[r][0];
    int b=avInd[r][1];
    grid[a][b]=1;
    relines--;
    if(i%2==0)
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
        if (i==0)
        {
            //checking the box under
            if(grid[1][j]==1 && grid[1][j-1]==1 && grid[2][j]==1)
            {
                scoreInc(turn);
                swapTurns();
                if (turn==player1.turn)
                {
                    boxesGrid[0][j-1]=1;
                } else
                {
                    boxesGrid[0][j-1]=2;
                }
                records[rounds][3]++;
            }

        } else if (i==(gridSize-1))
        {
            //checking the box above
            if(grid[i-1][j]==1 && grid[i-1][j-1]==1 && grid[i-2][j]==1)
            {
                scoreInc(turn);
                swapTurns();
                if (turn==player1.turn)
                {
                    boxesGrid[(i/2)-1][j-1]=1;
                } else
                {
                    boxesGrid[(i/2)-1][j-1]=2;
                }
                records[rounds][3]++;
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
        if (j==0)
        {
            //checking the box on the right
            if(grid[i+1][j+1] ==1 && grid[i-1][j+1]==1 && grid[i][j+1]==1)
            {
                scoreInc(turn);
                swapTurns();
                if (turn==player1.turn)
                {
                    boxesGrid[i/2][j]=1;
                } else
                {
                    boxesGrid[i/2][j]=2;
                }
                records[rounds][3]++;
            }

        } else if (j==numOfBoxes)
        {
            //checking the box on the left
            if(grid[i+1][j]==1 && grid[i-1][j]==1 && grid[i][j-1]==1)
            {
                scoreInc(turn);
                swapTurns();
                if (turn==player1.turn)
                {
                    boxesGrid[i/2][j-1]=1;
                } else
                {
                    boxesGrid[i/2][j-1]=2;
                }
                records[rounds][3]++;
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

