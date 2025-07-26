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
void sortPlayers(Player arr[], int count);
int comparePlayers(Player a, Player b);

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
        playerCount++;
    }

    if (playerCount == 0) {
        printf("Nenhum ranking encontrado.\n");
    } else {
        rewind(fdRanking);
        Player arr[playerCount];
        fread(&arr, sizeof(Player), playerCount, fdRanking);
        sortPlayers(arr, playerCount);

        for(int i = 0; i < playerCount; i++) { printf("%20s %d\n", arr[i].name, arr[i].score); }

    }

 
    fclose(fdRanking);
}

void sortPlayers(Player arr[], int count) {
    int sorted = 0;
    while(!sorted) {
        sorted = 1;

        for(int i = 0; i < count - 1; i++) {
            if(comparePlayers(arr[i], arr[i+1]) > 0) {
                Player temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;

                sorted = 0;
            }
        }
    }
}

int comparePlayers(Player a, Player b) {
    if(a.score != b.score) {
        return b.score - a.score;
    } else {
        return strcmp(a.name, b.name);
    }
}

#endif