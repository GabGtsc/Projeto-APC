/*
ask and store name
print menu, menu logic
game logic
*/

/* 
 - Menu print functions are always responsible for clearing the screen 
 - Menu functions are responsible for input and output
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif
#define clear() system(CLEAR)

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

FILE* fdRanking;

void printMainMenu();
void configMenu();
void printConfigMenu();
void waitForEnter();
void zerarRanking();

int main() {
    char username[50];

    clear();
    printf("=====================================\n");
    printf("         BEM-VINDO AO JOGO!          \n");
    printf("=====================================\n\n");
    printf("Digite seu nickname para comecar: ");
    fgets(username, 50, stdin);

    int opcode;
    printMainMenu();
    scanf("%d", &opcode);

    switch (opcode)
    {
    case JOGAR:
        
        break;
    case CONFIG:
        configMenu();
        break;
    case INTRUCOES:
    break;
    case RANKING:
    break;
    case SAIR:
        return 0;
        break;
    default:
    break;
    }
}

void waitForEnter() {
    int c;
    // Flush input buffer
    while ((c = getchar()) != '\n' && c != EOF);
    // Wait for Enter
    getchar();
}


void printMainMenu() {
    clear();
    printf("=====================================\n");
    printf("         BEM-VINDO AO JOGO!          \n");
    printf("=====================================\n\n");
    printf(" [1] Jogar\n");
    printf(" [2] Configuracoes\n");
    printf(" [3] Instrucoes\n");
    printf(" [4] Ranking\n");
    printf(" [5] Sair\n");
    printf("-------------------------------------\n");
    printf("Digite sua escolha: ");
    return;
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
            
            break;

        default:
            /* Opcao invalida */
            printf("\nOpcao invalida, pressione Enter para continuar...");
            waitForEnter();
            break;
        }
    }


}

void printConfigMenu() {
    clear();
    printf("=====================================\n");
    printf("         CONFIGURACOES DO JOGO       \n");
    printf("=====================================\n\n");
    printf(" [1] Zerar ranking\n");
    printf(" [2] Modo blind (Em desenvolvimento..)\n");
    printf(" [3] Editor de fases (Em desenvolvimento..)\n");
    printf(" [4] Voltar ao menu principal\n");
    printf("-------------------------------------\n");
    printf("Digite sua escolha: ");

    return;
}

void zerarRanking() {
    fdRanking = fopen("ranking.bin", "wb");
    int zero = 0;
    fwrite(&zero, sizeof(int), 1, fdRanking);
}

