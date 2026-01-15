#include <stdio.h>
#include <stdlib.h>
#include "tad-buku.h"
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "Portuguese");

    //variáveis:
    int tam_tab = 0;
    Tabuleiro *tab = NULL;

    menu();
    printf("\n");
    do{
        printf("Informe o tamanho do tabuleiro: ");
        scanf("%d", &tam_tab);
        if(tam_tab % 2 == 0 && tam_tab > 5)
            tab = criaTabuleiro(tam_tab);
        else{
            printf("\nO tamanho do tabuleiro deve ser maior que 6 e par.\n");
            printf("Tente novamente!");
            limpaTela();
            menu();
            printf("\n\n");
        }
    }while(tam_tab % 2 != 0 || tam_tab < 5);


    imprimeTabuleiro(tab);

    return 0;
}
