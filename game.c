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
void gameLoop();

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

    int srcCol, destCol;
    while(1) {
        printMatrix();

        // check if move is legal
        int scanRes = scanf("%d %d", &srcCol, &destCol);
        if(scanRes != 2) {
            printf("Entrada invalida! Digite dois numeros. ");
            waitForEnter();
            continue;
        }
        srcCol -= 1;
        destCol -= 1;

        int srcHeigth = heights[srcCol];
        int destHeigth = heights[destCol];

        if(srcCol < 0 || srcCol >= colCount || destCol < 0 || destCol >= colCount) {
            printf("Coluna invalida! Tente novamente. ");
            waitForEnter();
            continue;
        }

        if(srcHeigth <= 0) {
            printf("Coluna origem vazia! Tente novamente. ");
            waitForEnter();
            continue;
        }

        if(destHeigth == maxHeigth) {
            printf("Coluna destino cheia! Tente novamente. ");
            waitForEnter();
            continue;
        }

        char srcChar = mat[srcHeigth - 1][srcCol]; // char that is being moved
    
        if(destHeigth > 0 && srcChar != mat[destHeigth - 1][destCol]) {
            printf("Topo da coluna destino tem caractere diferente! Tente novamente. ");
            waitForEnter();
            continue;
        }

        // execute move
        for(int i = heights[srcCol] - 1; i >= 0; i--) {
            if(mat[i][srcCol] == srcChar && heights[destCol] != maxHeigth) {
                mat[heights[destCol]][destCol] = mat[i][srcCol];
                mat[i][srcCol] = ' ';
                heights[destCol]++;
                heights[srcCol]--;
            } else {
                break;
            }
        }

    }
}

void printMatrix() {

    clear();
    printf("=========== JOGO ===========\n\n"); 
    for (int row = maxHeigth - 1; row >= 0; row--) {
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

    return;
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