#ifndef GAME_C
#define GAME_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menus.c"

#define MATRIX_SIDE 10

void cleanVariables();
int readLevel();
void padMatrix();
void printMatrix();
void gameLoop();
int checkColumn(int col);
void executeMove(int srcCol, int destCol);
int isMoveLegal(int srcCol, int destCol);

char mat[MATRIX_SIDE]
        [MATRIX_SIDE];  // global, matrix funcs will directly change as a side
                        // effect, no passing pointers
int heights[MATRIX_SIDE];
int maxHeigth;
int colCount;

FILE* gameFd;
int currLevel = 0;

void setupLevels() {
    gameFd = fopen("entrada_v2.txt", "r");
    if (gameFd == NULL) {
        printf("\n\nErro! Ao abrir arquivo de entradas\n");
        printf("Pressione Enter para continuar...");
        waitForEnter();
        return;
    }

    int isLastLevel = 0;

    while (1) {
        cleanVariables();
        isLastLevel = readLevel();
        padMatrix();
        gameLoop();
        if (isLastLevel) {
            break;
        }
    }

    // TODO: Game end logic and prints
    return;
}

void gameLoop() {
    printMatrix();
    printf("Digite seu movimento: ");

    int srcCol, destCol;
    int parabenize = 0;

    while (1) {
        // check if move is legal
        printMatrix();
        if (parabenize) {
            printf("Completou uma coluna! PARABENS!!!\n");
            parabenize = 0;
        }
        printf("Digite seu movimento: ");

        if (scanf("%d %d", &srcCol, &destCol) != 2) {
            printf("Entrada invalida! Digite dois numeros. ");
            waitForEnter();
            continue;
        }
        srcCol -= 1;
        destCol -= 1;

        if (!isMoveLegal(srcCol, destCol)) {
            continue;
        }

        executeMove(srcCol, destCol);

        if (checkColumn(destCol) == 1) {
            parabenize = 1;
        }
        if (checkColumn(destCol) == 2) {
            break;
        }
    }

    printMatrix();
    printf("Terminou a fase, PARABENS!!!!!\n");
    printf("Aperte Enter para continuar... ");
    waitForEnter();
}

int isMoveLegal(int srcCol, int destCol) {
    int srcHeigth = heights[srcCol];
    int destHeigth = heights[destCol];

    if (srcCol < 0 || srcCol >= colCount || destCol < 0 ||
        destCol >= colCount) {
        printf("Coluna invalida! Tente novamente. ");
        waitForEnter();
        return 0;
    }

    if (srcHeigth <= 0) {
        printf("Coluna origem vazia! Tente novamente. ");
        waitForEnter();
        return 0;
    }

    if (destHeigth == maxHeigth) {
        printf("Coluna destino cheia! Tente novamente. ");
        waitForEnter();
        return 0;
    }

    if (destHeigth > 0 &&
        mat[srcHeigth - 1][srcCol] != mat[destHeigth - 1][destCol]) {
        printf(
            "Topo da coluna destino tem caractere diferente! Tente "
            "novamente. ");
        waitForEnter();
        return 0;
    }

    return 1;
}

void executeMove(int srcCol, int destCol) {
    char srcChar = mat[heights[srcCol] - 1][srcCol];
    for (int i = heights[srcCol] - 1; i >= 0; i--) {
        if (mat[i][srcCol] == srcChar && heights[destCol] != maxHeigth) {
            mat[heights[destCol]][destCol] = mat[i][srcCol];
            mat[i][srcCol] = ' ';
            heights[destCol]++;
            heights[srcCol]--;
        } else {
            break;
        }
    }
}

int checkColumn(int col) {
    char c = mat[0][col];

    // 0 se não, 1 se sim, 2 se todas
    for (int row = maxHeigth - 1; row >= 0; row--) {
        if (mat[row][col] != c)
            return 0;
    }

    // se a coluna estiver certa, checar se o resto está
    for (int col = 0; col < colCount; col++) {
        char c = mat[0][col];
        for (int row = 0; row < maxHeigth; row++) {
            if (mat[row][col] != c)
                return 1;
        }
    }

    return 2;
}

void printMatrix() {
    clear();
    printf("=========== JOGO ===========\n\n");
    for (int row = maxHeigth - 1; row >= 0; row--) {
        for (int col = 0; col < colCount; col++) {
            putchar(mat[row][col]);
            printf("  ");
        }
        putchar('\n');
    }
    putchar('\n');

    for (int col = 0; col < colCount; col++) {
        printf("%d", col + 1);
        if (col != colCount - 1) {
            printf("  ");
        }
    }
    putchar('\n');
    return;
}

void cleanVariables() {
    for (int i = 0; i < MATRIX_SIDE; i++) {
        heights[i] = -1;
        for (int j = 0; j < MATRIX_SIDE; j++) {
            mat[i][j] = -1;
        }
    }
    maxHeigth = 0;

    return;
}

int readLevel() {
    // reads the level from entrada.txt, assumes file is already open
    int currHeight;
    char c;

    int reachedEOF = 0;
    int col;
    for (col = 0; col < MATRIX_SIDE; col++) {
        if (fscanf(gameFd, " %c", &c) != 1) {
            reachedEOF = 1;
            break;
        }
        if (c == '-')
            break;

        currHeight = c - '0';
        for (int row = 0; row < currHeight; row++) {
            fscanf(gameFd, " %c", &c);

            mat[row][col] = c;
        }

        heights[col] = currHeight;
        if (currHeight > maxHeigth)
            maxHeigth = currHeight;

        putchar(c);
    }

    colCount = col;

    return reachedEOF;
}

void padMatrix() {
    for (int col = 0; col < colCount; col++) {
        for (int row = maxHeigth - 1; row >= 0; row--) {
            if (mat[row][col] == -1) {
                mat[row][col] = ' ';
            }
        }
    }
    return;
}

#endif  // GAME_C