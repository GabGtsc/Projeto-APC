
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif
#define clear() system(CLEAR)

#ifndef MENUS_C
#define MENUS_C

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

void waitForEnter() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();
}

#endif // MENUS_C
