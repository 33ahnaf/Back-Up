/*
 * Re-creation attempt of the Tic-Tac-Toe game
 * Created on 25th July, 2026 by Ahnaf
 * inspired by the C programming book of Nafiul Zami
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define PLAYER_1 'X'
#define PLAYER_2 'O'

int gridSize;
char **gameGrid;
int emptyCells;

void drawGrid(void);
bool allocateGridArray(void);
void freeGridArray(void);
void clear_screen(void);
void Player1_turn(void);
void Player2_turn(void);
bool checkGame(char target);
bool showWin(char player);
bool showDraw(void);
void emptyGrid(void);

int main(){
    printf("--------- TIC-TAC-TOE ---------\n\n");
    printf("Grid size: ");
    scanf("%d", &gridSize);
    emptyCells = gridSize*gridSize;
    if(allocateGridArray()) return 1;

    emptyGrid();

    while(emptyCells != 0){
        Player1_turn();
        if(checkGame(PLAYER_1)){
            if(showWin(PLAYER_1))
                continue;
            break;
        }else if(emptyCells <= 0){
            if(showDraw())
                continue;
            break;
        }

        Player2_turn();
        if(checkGame(PLAYER_2)){
            if(showWin(PLAYER_2))
                continue;
            break;
        }else if(emptyCells <= 0){
            if(showDraw())
                continue;
            break;
        }
    }

    freeGridArray();
    return 0;
}




void drawGrid(void){
    // draw the grid
    for(int y = 0; y < gridSize; y++){

        for(int x = 0; x < gridSize; x++){
            // print X or O for every [y][x] position
            if(x != gridSize - 1){
                printf(" %c |", gameGrid[y][x]); // print | if it's not the last x position
            }else{
                printf(" %c\n", gameGrid[y][x]); // print \n if it's the last x position
            }

        }

        if(y != gridSize - 1){ // print the grid y divider if it's not the last y position
            for(int x = 0; x < gridSize; x++){
                if(x != gridSize-1){
                    printf("---|");
                }else{
                    printf("---\n");
                }
            }

        }

    }
}

bool allocateGridArray(void){
    gameGrid = (char**) malloc(gridSize * sizeof(char*));
    if(gameGrid == NULL) return 1;

    for(int y = 0; y < gridSize; y++){
        gameGrid[y] = (char*) malloc(gridSize * sizeof(char*));
        if(gameGrid[y] == NULL) return 1;
    }

    return 0;
}

void emptyGrid(void){
    for(int y = 0; y < gridSize; y++)
        for(int x = 0; x < gridSize; x++)
            gameGrid[y][x] = ' ';
}

void freeGridArray(void){
    for(int y = 0; y < gridSize; y++)
        free(gameGrid[y]);
    free(gameGrid);
}

void clear_screen(void){
    // \e[1;1H moves the cursor to row 1, column 1
    // \e[2J clears the entire visible screen
    printf("\e[1;1H\e[2J");
    // Optional: Use \e[1;1H\e[3J if you want to clear the scrollback buffer too
}

void Player1_turn(void){
    int x, y;
    clear_screen();
    drawGrid();
    printf("\n");
    printf("---- %c's turn ----\n", PLAYER_1);
    printf("Enter the position: ");
    scanf("%d %d", &x, &y);
    x--; y--; // because player counts from 1
    if((x > gridSize - 1 || x < 0) || (y > gridSize - 1 || y < 0)){
        clear_screen();
        printf("\n\n\t\tOut of bound!\n");
        printf("\t\t  Try again\n");
        sleep(2);
        Player1_turn();
    }else if(gameGrid[y][x] == ' '){
        gameGrid[y][x] = PLAYER_1;
        emptyCells--;
    }else{
        clear_screen();
        printf("\n\n\t\tAlready occupied!\n");
        printf("\t\t    Try again\n");
        sleep(2);
        Player1_turn();
    }
}

void Player2_turn(void){
    int x, y;
    clear_screen();
    drawGrid();
    printf("\n");
    printf("---- %c's turn ----\n", PLAYER_2);
    printf("Enter the position: ");
    scanf("%d %d", &x, &y);
    x--; y--; // because player counts from 1
    if((x > gridSize - 1 || x < 0) || (y > gridSize - 1 || y < 0)){
        clear_screen();
        printf("\n\n\t\tOut of bound!\n");
        printf("\t\t  Try again\n");
        sleep(2);
        Player2_turn();
    }else if(gameGrid[y][x] == ' '){
        gameGrid[y][x] = PLAYER_2;
        emptyCells--;
    }else{
        clear_screen();
        printf("\n\n\t\tAlready occupied!\n");
        printf("\t\t    Try again\n");
        sleep(2);
        Player2_turn();
    }
}

bool diagonalCheck(char target){
    for(int i = 0; i < gridSize; i++)
        if(gameGrid[i][i] != target)
            return false;
    return true;
}

bool diagonalCheck2nd(char target){
    for(int i = 0; i < gridSize; i++)
        if(gameGrid[i][gridSize - i - 1] != target)
            return false;
    return true;
}

bool YCheck(char target, int y){
    for(int x = 0; x < gridSize; x++)
        if(gameGrid[y][x] != target)
            return false;
    return true;
}

bool XCheck(char target, int x){
    for(int y = 0; y < gridSize; y++)
        if(gameGrid[y][x] != target)
            return false;
    return true;
}

bool checkGame(char target){
    if(diagonalCheck(target) || diagonalCheck2nd(target))
        return true;
    else
        for(int i = 0; i < gridSize; i++)
            if(XCheck(target, i) || YCheck(target, i))
                return true;
    return false;
}

bool showWin(char player){
    char userinput;
    sleep(1);
    clear_screen();
    printf("\n\n\t\t--- END OF GAME ---\n");
    printf("\t\t   PLAYER %c WON!\n", player);
    printf("\t\tPlay again? [y/n]:");
    scanf("%c", &userinput);
    if(userinput == 'y' || userinput == 'Y'){
        emptyGrid();
        emptyCells = gridSize*gridSize;
        return true;
    }else if(userinput == 'n' || userinput == 'N'){
        clear_screen();
        printf("\n\n\t\t Bye!!\n");
        sleep(1);
        return false;
    }else
        return showWin(player);
}
bool showDraw(void){
    char userinput;
    sleep(1);
    clear_screen();
    printf("\n\n\t\t--- END OF GAME ---\n");
    printf("\t\t It's a tie!\n");
    printf("\t\tPlay again? [y/n]:");
    scanf("%c", &userinput);
    if(userinput == 'y' || userinput == 'Y'){
        emptyGrid();
        emptyCells = gridSize*gridSize;
        return true;
    }else if(userinput == 'n' || userinput == 'N'){
        clear_screen();
        printf("\n\n\t\t Bye!!\n");
        sleep(1);
        return false;
    }else
        return showDraw();
}