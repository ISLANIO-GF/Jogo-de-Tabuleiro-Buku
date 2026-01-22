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
    Pilha *mao = NULL, *jogador_01 = NULL, jogador_02 = NULL;

    //Iniciando o jogo.
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
            printf("Tente novamente!\n");
            printf("\n");
        }
    }while(tam_tab % 2 != 0 || tam_tab < 5);

    //Criando pilhas para mão dos jogadores e as pilhas de pontuação.
    mao = criarPilha();
    jogador_01 = criarPilha();
    jogador_02 = criarPilha();


    imprimeTabuleiro(tab);

    destruirTabuleiro(tab);
    return 0;
}
