#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

/*
ask and store name
print menu, menu logic
game logic
*/
void printMainMenu();

int main() {
    char username[50];
    
    // TODO: menu inicial mais bonitinho pedindo nome, nome do jogo
    printf("nickname: ");
    fgets(username, 50, stdin);

    printMainMenu();
}

void printMainMenu() {
    system(CLEAR);

    printf("MENU\n\n");
    printf("1- jogo\n");
    printf("2- conf\n");
    printf("3- instru\n");
    printf("4- ranking\n");
    printf("5- sair\n");

    putchar('\n');
    printf("Digite sua escolha: ");
}