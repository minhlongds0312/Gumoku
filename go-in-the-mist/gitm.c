// name: Minh Long Duong
// unikey: mduo2085
// SID: 520077702

// code here
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>

char playBoard[19][19];
char turnPlayer = 'B';
char winner = 'n';
int holeX = 10;
int holeY = 10;
char history[1000] = ""; // length 1000 because after calculation, the max history length would be about 912
int count = 0; //counter to check tie
void trim(char *str)
{
    int x, i;
    x = 0;
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] != ' ' && str[i] != '\n')
        {
            x = i;
        }
        i++;
    }
    str[x + 1] = '\0';
}
void initBoard()
{
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 19; j++)
        {
            playBoard[i][j] = '.';
        }
    }
}
void changeHole(int x, int y)
{
    x = x + 1;
    y = y + 1;
    holeY = 1 + (((5 * (x * x)) + (3 * x) + 4) % 19);
    holeX = abs(1 + (((4 * (y * y)) + (2 * y) - 4) % 19)); // since index starts at 0 and the formula starts at 1
    // coordinates are inverted
}
void placeBlack(int x, int y)
{
    changeHole(x, y);
    playBoard[x][y] = '#';
}
void placeWhite(int x, int y)
{
    changeHole(x, y);
    playBoard[x][y] = 'o';
}
void readMove(char str[])
{
    if (isspace(str[strlen(str) - 2]) || (isspace(str[5]) && isspace(str[6])) || strlen(str) < 8)
    {
        printf("Invalid!\n");
        return;
    }
    trim(str);
    // check 2 digit coordinate
    if (strlen(str) == 9)
    {
        char coor[4] = {str[7], str[8], '\0'};
        int x = atoi(coor);
        if (x < 10)
        {
            printf("Invalid coordinate\n");
            return;
        }
        // check coordinate validity
        if (x < 1 || x > 19 || str[6] < 65 || str[6] > 83 || strlen(str) != 9)
        {
            printf("Invalid coordinate\n");
            return;
        }
        if (playBoard[x - 1][str[6] - 65] == '#' || playBoard[x - 1][str[6] - 65] == 'o')
        {
            printf("Occupied coordinate\n");
            return;
        }
        if (turnPlayer == 'B')
        {
            placeBlack(x - 1, str[6] - 65);
            turnPlayer = 'W';
        }
        else
        {
            placeWhite(x - 1, str[6] - 65);
            turnPlayer = 'B';
        }
        char move[4] = {str[6], str[7], str[8]};
        strcat(history, move);
    }
    else
    // check 1 digit coordinate
    {
        if (str[7] < 49 || str[7] > 57 || str[6] < 65 || str[6] > 83 || strlen(str) != 8)
        {
            printf("Invalid coordinate\n");
            return;
        }
        if (playBoard[str[7] - '0' - 1][str[6] - 65] == '#' || playBoard[str[7] - '0' - 1][str[6] - 65] == 'o')
        {
            printf("Occupied coordinate\n");
            return;
        }
        if (turnPlayer == 'B')
        {
            placeBlack(str[7] - '0' - 1, str[6] - 65);
            turnPlayer = 'W';
        }
        else
        {
            placeWhite(str[7] - '0' - 1, str[6] - 65);
            turnPlayer = 'B';
        }
        char move[3] = {str[6], str[7]};
        strcat(history, move);
    }
    //-65 to convert from ASCII to in; -1 to make the first index 0
}

void viewHole()
{
    char charHoleX = holeY + 64;
    char charHoleY[10];
    if (holeY < 9)
    {
        int holeYInt = holeX;
        sprintf(charHoleY, "%d", holeYInt);
    }
    else
    {
        int holeYInt = holeX;
        sprintf(charHoleY, "%d", holeYInt);
    }
    int radX = charHoleX - 64 - 1;
    int radY = atoi(charHoleY) - 1;
    printf("%c%s,", charHoleX, charHoleY);
    for (int x = radY + 3; x >= radY - 3; x--) // since we added 1 before
    {
        for (int y = radX - 3; y <= radX + 3; y++)
        {
            if ((x < 0 || x > 18) || y < 0 || y > 18)
            {
                printf("x");
            }
            else
            {
                printf("%c", playBoard[x][y]);
            }
        }
    }
    printf("\n");
}
void endGame()
{
    if (winner == 'W')
    {
        printf("White wins!\n");
    }
    else if (winner == 'B')
    {
        printf("Black wins!\n");
    }
    else
    {
        printf("Wow, a tie!\n");
    }
    strcat(history, "\n");
    printf("%s", history);
    printf("Thank you for playing!\n");
    exit(0);
}
void checkWinPlayer(char sign)
{
    if (sign == 'o')
    {
        winner = 'W';
        endGame();
    }
    else if (sign == '#')
    {
        winner = 'B';
        endGame();
    }
}
void checkWin()
{
    // check tie
    if (count == 19 * 19)
    {
        winner = 'n';
        endGame();
    }
    // check horizontal
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (playBoard[i][j] == playBoard[i][j + 1] && playBoard[i][j + 1] == playBoard[i][j + 2] && playBoard[i][j + 2] == playBoard[i][j + 3] && playBoard[i][j + 3] == playBoard[i][j + 4])
            {
                checkWinPlayer(playBoard[i][j]);
            }
        }
    }
    // check vertical
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 19; j++)
        {
            {
                if (playBoard[i][j] == playBoard[i + 1][j] && playBoard[i + 1][j] == playBoard[i + 2][j] && playBoard[i + 2][j] == playBoard[i + 3][j] && playBoard[i + 3][j] == playBoard[i + 4][j])
                {
                    checkWinPlayer(playBoard[i][j]);
                }
            }
        }
    }
    // check diagonal
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if ((playBoard[i][j] == playBoard[i + 1][j + 1] && playBoard[i + 1][j + 1] == playBoard[i + 2][j + 2] && playBoard[i + 2][j + 2] == playBoard[i + 3][j + 3] && playBoard[i + 3][j + 3] == playBoard[i + 4][j + 4]))
            {
                checkWinPlayer(playBoard[i][j]);
            }
        }
    }
    for (int i = 0; i < 15; i++)
    {
        for (int j = 4; j < 19; j++)
        {
            if ((playBoard[i][j] == playBoard[i + 1][j - 1] && playBoard[i + 1][j - 1] == playBoard[i + 2][j - 2] && playBoard[i + 2][j - 2] == playBoard[i + 3][j - 3] && playBoard[i + 3][j - 3] == playBoard[i + 4][j - 4]))
            {
                checkWinPlayer(playBoard[i][j]);
            }
        }
    }
}

int main()
{
    initBoard();
    char str[50] = " ";
    while (fgets(str, 50, stdin) != NULL)
    {
        // check length validity
        if (strlen(str) > 40)
        {
            int c;
            int spaceCount = 0;
            for (int index = 0; index < strlen(str); index++)
            {
                if (isspace(str[index]))
                {
                    spaceCount += 1;
                }
            }
            while((c = getchar()) != EOF){
                if(c == ' '){
                    spaceCount+=1;
                }
                if(c == '\n' || c == '\0' || c == EOF){
                    break;
                }
            }
            if (spaceCount >1)
            {
                printf("Invalid!\n");
                continue;
            }
            else if (((!isspace(str[8]) || !isspace(str[7])) && spaceCount != 1))
            {
                printf("Invalid!\n");
                continue;
            }
            else
            {
                printf("Invalid coordinate\n");
                continue;
            }
            while ((c = getchar()) != '\n')
            {
                // Discard the extra characters
            }
        }
        else if (str[0] == 'p' && str[1] == 'l' && str[2] == 'a' && str[3] == 'c' && str[4] == 'e' && isspace(str[5]))
        {
            if (turnPlayer == 'W')
            {
                readMove(str);
                count += 1;
            }
            else
            {
                readMove(str);
                count += 1;
            }
        }
        else if (str[0] == 'v' && str[1] == 'i' && str[2] == 'e' && str[3] == 'w' && strlen(str) == 5)
        {
            viewHole();
        }
        else if (str[0] == 'w' && str[1] == 'h' && str[2] == 'o' && strlen(str) == 4)
        {
            printf("%c\n", turnPlayer);
        }
        else if (str[0] == 't' && str[1] == 'e' && str[2] == 'r' && str[3] == 'm' && strlen(str) <= 6 && str[4] != ' ')
        {

            exit(1);
        }
        else if ((str[0] = 'h') && str[1] == 'i' && str[2] == 's' && str[3] == 't' && str[4] == 'o' && str[5] == 'r' && str[6] == 'y' && strlen(str) == 8)
        {
            printf("%s\n", history);
        }
        else if ((str[0] = 'r') && str[1] == 'e' && str[2] == 's' && str[3] == 'i' && str[4] == 'g' && str[5] == 'n' && strlen(str) <= 8 && str[6] != ' ')
        {

            if (turnPlayer == 'W')
                winner = 'B';
            else
                winner = 'W';
            endGame();
        }
        else
        {
            printf("Invalid!\n");
        }
        str[0] = '\0';
        checkWin();
    };
    return 0;
}