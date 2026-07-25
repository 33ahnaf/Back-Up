/*
 * Re-creation attempt of the Tic-Tac-Toe game
 * Created on 25th July, 2026 by Ahnaf
 * inspired by the C programming book of Nafiul Zami
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PLAYER_1 'X'
#define PLAYER_2 'O'

int gridSize;
char **gameGrid;
int emptyCells;

void drawGrid(void);
int  allocateGridArray(void);
void freeGridArray(void);
void clear_screen(void);
void Player1_turn(void);
void Player2_turn(void);
void checkGame(void);

int main(){
    printf("--------- TIC-TAC-TOE ---------\n\n");
    printf("Grid size: ");
    scanf("%d", &gridSize);
    emptyCells = gridSize*gridSize;
    if(allocateGridArray()) return 1;
    
    for(int y = 0; y < gridSize; y++)
        for(int x = 0; x < gridSize; x++)
            gameGrid[y][x] = ' ';

    while(emptyCells != 0){
        Player1_turn();
        if(!emptyCells) break;
        Player2_turn();
        if(!emptyCells) break;
    }

    freeGridArray();
    return 0;
}




void drawGrid(){
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

int allocateGridArray(){
    gameGrid = (char**) malloc(gridSize * sizeof(char*));
    if(gameGrid == NULL) return 1;

    for(int y = 0; y < gridSize; y++){
        gameGrid[y] = (char*) malloc(gridSize * sizeof(char*));
        if(gameGrid[y] == NULL) return 1;
    }

    return 0;
}

void freeGridArray(){
    for(int y = 0; y < gridSize; y++)
        free(gameGrid[y]);
    free(gameGrid);
}

void clear_screen(){
    // \e[1;1H moves the cursor to row 1, column 1
    // \e[2J clears the entire visible screen
    printf("\e[1;1H\e[2J");
    // Optional: Use \e[1;1H\e[3J if you want to clear the scrollback buffer too
}

void Player1_turn(){
    int x, y;
    clear_screen();
    drawGrid();
    printf("\n");
    printf("---- %c's turn ----\n", PLAYER_1);
    printf("Enter the position: ");
    scanf("%d %d", &y, &x);
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

void Player2_turn(){
    int x, y;
    clear_screen();
    drawGrid();
    printf("\n");
    printf("---- %c's turn ----\n", PLAYER_2);
    printf("Enter the position: ");
    scanf("%d %d", &y, &x);
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

void checkGame(void){
    for(int y = 0; y < gridSize; y++)
        for(int x = 0; x < gridSize; x++)
}