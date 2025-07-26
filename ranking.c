#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menus.c"

#ifndef RANKING_C
#define RANKING_C


typedef struct {
    char name[20];
    int score;
} Player;

void cleanRanking();
void addRank();

void cleanRanking() {
    FILE* fdRanking = fopen("ranking.bin", "wb");
    if (fdRanking == NULL) {
        perror("ERRO! Falha ao abrir arquivo de ranking.\n");
        printf("Pressione Enter para continuar...");
        waitForEnter();
        return;
    }
    // Do not write anything, just truncate the file
    fclose(fdRanking);
}

void addRank(Player rank) {
    FILE* fdRanking = fopen("ranking.bin", "ab");
    if (fdRanking == NULL) {
        perror("ERRO! Falha ao abrir arquivo de ranking.\n");
        printf("Pressione Enter para continuar...");
        waitForEnter();
        return;
    }

    fwrite(&rank, sizeof(Player), 1, fdRanking);
    fclose(fdRanking);
}

void printRankings() {
    FILE* fdRanking = fopen("ranking.bin", "rb");
    if (fdRanking == NULL) {
        perror("ERRO! Falha ao abrir arquivo de ranking.\n");
        printf("Pressione Enter para continuar...");
        waitForEnter();
        return;
    }

    Player curr;
    int playerCount = 0;

    clear();
    printf("=====================================\n");
    printf("              RANKING                \n");
    printf("=====================================\n\n");

    while(fread(&curr, sizeof(Player), 1, fdRanking) == 1) {
        printf("%-20s %d\n", curr.name, curr.score);
        playerCount++;
    }

    if (playerCount == 0) {
        printf("Nenhum ranking encontrado.\n");
    }

    fclose(fdRanking);
}

#endif