/*
ask and store name
print menu, menu logic
game logic
*/

/* 
 - Menu print functions are always responsible for clearing the screen 
 - Menu functions are responsible for input and output
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.c"
#include "menus.c"

enum main_menu {
    JOGAR = 1,
    CONFIG,
    INTRUCOES,
    RANKING,
    SAIR
};

enum config_menu {
    ZERAR_RANKING = 1,
    MODO_BLIND,
    EDITOR_FASES,
    VOLTAR_MENU_PRINCIPAL
};


void mainMenu();
void configMenu();
void zerarRanking();

char username[50];
FILE* fdRanking;

int main() {

    setupLevels();

    clear();
    printf("=====================================\n");
    printf("         BEM-VINDO AO JOGO!          \n");
    printf("=====================================\n\n");
    printf("Digite seu nickname para comecar: ");
    fgets(username, 50, stdin);

    mainMenu();
}



void mainMenu() {
    while(1) {
        printMainMenu();

        int opcode;

        scanf(" %d", &opcode);

        switch (opcode)
        {
        case JOGAR:
            setupLevels();
            break;
        case CONFIG:
            configMenu();
            break;
        case INTRUCOES:
            break;
        case RANKING:
            break;
        case SAIR:
            return;
            break;
        default:
            /* invalid option */
            printf("\nOpcao invalida, pressione Enter para continuar...");
            waitForEnter();
        break;
        }
    }
}

void configMenu() {
    int opcode;
    
    while(1) {
        printConfigMenu();
        scanf("%d", &opcode);

        char c;
        while ((c = getchar()) != '\n' && c != EOF); // Flush input buffer after scanf
        
        switch(opcode)
        {
        case ZERAR_RANKING:
            printf("\nConfirma reinicializar o ranking? (S/N) ");
            char confirmation = getchar();
            if(confirmation == 'S' || confirmation == 's') {
                zerarRanking();
                printf("Ranking zerado! Pressione Enter para continuar...");
                waitForEnter();
            }
            break;

        case MODO_BLIND:
            printf("\nNao implementado, pressione Enter para continuar...");
            waitForEnter();
            break;

        case EDITOR_FASES:
            printf("\nNao implementado, pressione Enter para continuar...");
            waitForEnter();
            break;

        case VOLTAR_MENU_PRINCIPAL:
            return;
            break;

        default:
            /* invalid option */
            printf("\nOpcao invalida, pressione Enter para continuar...");
            waitForEnter();
            break;
        }
    }


}

void zerarRanking() {
    fdRanking = fopen("ranking.bin", "wb");
    int zero = 0;
    fwrite(&zero, sizeof(int), 1, fdRanking);
}

