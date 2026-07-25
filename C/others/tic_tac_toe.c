/*
 * Re-creation attempt of the Tic-Tac-Toe game
 * Created on 25th July, 2026 by Ahnaf
 * inspired by the C programming book of Nafiul Zami
 */

#include <stdio.h>

#define GRID_SIZE 3
#define PLAYER_1 'X'
#define PLAYER_2 'O'

char gameGrid[GRID_SIZE][GRID_SIZE];

void drawGrid();

int main(){
    return 0;
}

void drawGrid(){
    for(int y = 0; y < GRID_SIZE; y++){
        for(int x = 0; x < GRID_SIZE; x++){

    printf(" %c | %c | %c\n", gameGrid[0][0], gameGrid[0][1], gameGrid[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", gameGrid[1][0], gameGrid[1][1], gameGrid[1][2]);
}
