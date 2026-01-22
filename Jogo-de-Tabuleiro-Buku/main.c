#include <stdio.h>
#include <stdlib.h>
#include "tad-buku.h"
#include <locale.h>



typedef struct tabuleiro Tabuleiro;


//Função para criar o tabuleiro.

Tabuleiro* criaTabuleiro(int tam){
    Tabuleiro* tab = (Tabuleiro*)malloc(sizeof(Tabuleiro));
    if (tab == NULL){
        printf("Erro ao criar o tabuleiro!");
        exit(1);
    }
    tab->lin = tam;
    tab->col = tam;
    tab->casa = (Pilha**)malloc(tam * sizeof(Pilha*));
    for (int i = 0; i < tam; i++){
        tab->casa[i] = (Pilha*)malloc(tam * sizeof(Pilha));
        for(int j = 0; j < tam; j++){
            tab->casa[i][j] = NULL;
        }
    }
    return tab;
}




int main()
{
    setlocale(LC_ALL, "Portuguese");

    //variáveis:
    int tam_tab = 0;
    Tabuleiro *tab = NULL;

    //Inicio do programa.
    menu();
    printf("\n");
    do{
        printf("Informe o tamanho do tabuleiro: ");
        scanf("%d", &tam_tab);
        if(tam_tab % 2 == 0 && tam_tab > 5){
            tab = criaTabuleiro(tam_tab);
            iniciarTabuleiro(tab);
        }
        else{
            limpaTela();
            menu();
            printf("\n");
            printf("\nO tamanho do tabuleiro deve ser maior que 5 e par.\n");
            printf("Tente novamente!");
            printf("\n\n");
        }
    }while(tam_tab % 2 != 0 || tam_tab < 5);


    imprimeTabuleiro(tab);

    destruirTabuleiro(tab);
    return 0;
}
