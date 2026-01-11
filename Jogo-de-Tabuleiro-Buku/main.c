#include <stdio.h>
#include <stdlib.h>
#include "tad-buku.h"


int main()
{
    //variáveis:
    int tam_tab = 0;
    Tabuleiro *tab = NULL;

    printf("Informe o tamanho do tabuleiro: ");
    scanf("%d", &tam_tab);
    tab = criaTabuleiro(tam_tab);
    imprimeTabuleiro(tab);

    return 0;
}
