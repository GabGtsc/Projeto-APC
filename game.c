#ifndef GAME_C
#define GAME_C

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "menus.c"

void cleanVariables();
void readLevel();
void padMatrix();
void printMatrix();

char mat[10][10]; //global, matrix funcs will directly change as a side effect, no passing pointers 
int heights[10];
int maxHeigth;
int colCount;

FILE* gameFd;
int currLevel = 0;


void setupLevels() {
    //
    gameFd = fopen("entrada.txt", "r");
    if(gameFd == NULL) {
        printf("\n\nErro! Ao abrir arquivo de entradas\n");
        printf("Pressione Enter para continuar...");
        waitForEnter();
        return;
    }

    while(1) { 
    cleanVariables();
    readLevel();
    padMatrix();
    gameLoop();
    }
    return;
}

void gameLoop() {
    printMatrix();
}

void printMatrix() {

    clear();
    printf("=========== JOGO ===========\n\n"); // Added header text
    for (int row = 0; row < maxHeigth; row++) {
        for(int col = 0; col < colCount; col++) {
            putchar(mat[row][col]);
            printf("  ");
        }
        putchar('\n');
    }
    putchar('\n');
    
    for(int col = 0; col < colCount; col++) {
            printf("%d", col + 1);
            if(col != colCount - 1) {
                printf("  ");
            }
    }
    putchar('\n');

    printf("Digite seu movimento: ");
}

void cleanVariables() {
    for(int i = 0; i < 10; i++) {
        heights[i] = -1;
        for(int j = 0; j < 10; j++) {
            mat[i][j] = -1;
        }
    }
    maxHeigth = 0;

    return;
}

void readLevel() {
    // reads the level from entrada.txt, assumes file is already open
    int currHeight;
    char c;

    int col;
    for(col = 0; col < 10; col++) {
        fscanf(gameFd, " %c", &c);
        if(c == '-') break;
        
        currHeight = c - '0';
        for(int row = 0; row < currHeight; row++) {
            fscanf(gameFd, " %c", &c);

            mat[row][col] = c;
        }
        
        heights[col] = currHeight;
        if(currHeight > maxHeigth) maxHeigth = currHeight;
        
        putchar(c);
    }

    colCount = col;

    return;
}

void padMatrix() {
    for(int col = 0; col < colCount; col++) {
        for(int row = maxHeigth - 1; row >= 0; row--) {
            if(mat[row][col] == -1) {
                mat[row][col] = ' ';
            }
        }
    }
    return;
}


#endif // GAME_C