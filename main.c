/*
ask and store name
print menu, menu logic
game logic
*/

/*
 - Menu print functions are always responsible for clearing the screen
 - Menu functions are responsible for input and output
 */
#include "game.c"
#include "menus.c"
#include "ranking.c"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


enum main_menu { JOGAR = 1, CONFIG, INTRUCOES, RANKING, SAIR };

enum config_menu {
    ZERAR_RANKING = 1,
    MODO_BLIND,
    EDITOR_FASES,
    VOLTAR_MENU_PRINCIPAL
};

void mainMenu();
void configMenu();
void cleanRanking();
void printInstructions();

Player curr;

int main() {
    while (1) {
        clear();
        printf("=====================================\n");
        printf("    BEM-VINDO AO BAPC! (Ball APC)    \n");
        printf("=====================================\n\n");
        printf("Digite seu nickname para comecar: ");
        fgets(curr.name, 20, stdin);
        curr.name[strcspn(curr.name, "\n")] = 0;  // Remove trailing newline

        if (curr.name[0] != '\n')
            break;
    }

    mainMenu();
}

void mainMenu() {
    while (1) {
        printMainMenu();

        int opcode;

        scanf(" %d", &opcode);

        switch (opcode) {
            case JOGAR:
                curr.score = setupGame();
                if(curr.score != 0) addRank(curr);
                break;
            case CONFIG:
                configMenu();
                break;
            case INTRUCOES:
                printInstructions();
                waitForEnter();
                break;
            case RANKING:
                printRankings();
                printf("\nPressione Enter para continuar...");
                waitForEnter();
                break;
            case SAIR:
                return;
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

    while (1) {
        printConfigMenu();
        scanf("%d", &opcode);

        char c;
        while ((c = getchar()) != '\n' && c != EOF);  // Flush input buffer after scanf

        switch (opcode) {
            case ZERAR_RANKING:
                printf("\nConfirma reinicializar o ranking? (S/N) ");
                char confirmation = getchar();
                if (confirmation == 'S' || confirmation == 's') {
                    cleanRanking();
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

void printInstructions() {
    clear();

    FILE* fdInstructions = fopen("intructions.txt", "r");
    if(fdInstructions == NULL) {
        printf("ERRO! Ao tentar ler arquivo de instrucoes\n");
        printf("Favor conferir diretorio\n");
        printf("Pressione Enter para continuar...");
        waitForEnter();
        return;
    }


    // copy text from intructions.txt
    // done to avoid excessive printfs
    char c;
    while((c = fgetc(fdInstructions)) != EOF) {
        putchar(c);
    }

    printf("\nPressione enter para retornar ao menu principal...");
    return;
}