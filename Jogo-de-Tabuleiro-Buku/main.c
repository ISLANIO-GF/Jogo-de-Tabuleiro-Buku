#include <stdio.h>
#include <stdlib.h>
#include "tad-buku.h"
#include <locale.h>


int main()
{
    setlocale(LC_ALL, "Portuguese");

    //variáveis:
    char jogador_01[50], jogador_02[50];
    int tam_tab = 0, jogada = 1, lin_jog = 0, col_jog = 0;
    Tabuleiro *tab = NULL;
    Pilha *mao = NULL, *pontuacao_jog_01 = NULL, pontuacao_jog_02 = NULL;

    //Criando o jogo.
    menu();
    printf("\n");
    do{
        printf("Informe o tamanho do tabuleiro: ");
        scanf("%d", &tam_tab);

        if(tam_tab % 2 == 0 && tam_tab > 5){
            tab = criaTabuleiro(tam_tab);
            iniciarTabuleiro(tab);
            printf("\n========== Tabuleiro Criado com sucesso! ==========\n");
            imprimeTabuleiro(tab);
            pausa();
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
    pontuacao_jog_01 = criarPilha();
    pontuacao_jog_02 = criarPilha();


    //Iniciando o jogo.

    limpaTela();
    printf("\nPara comerçamos precisamos do nome dos jogadores.\n");

    printf("\nNome do Jogador 01: ");
    fgets(jogador_01, 50, stdin);
    jogador_01[strcspn(jogador_01, "\n")] = '\0';

    printf("\nNome do Jogador 02: ");
    fgets(jogador_02, 50, stdin);
    jogador_02[strcspn(jogador_02, "\n")] = '\0';

    printf("\n===== Iniciando o Jogo. Boa sorte ao jogadores! =====\n");
    do{
        if(jogada % 2 != 0){
            printf("\n%s escolha uma linha: ", jogador_01);
            scanf("%d", &lin_jog);
            jogada++;
        }
        else {
            printf("\n%s escolha uma coluna: ", jogador_02);
            scanf("%d", &col_jog);
            jogada++;
        }
    } while(lin_jog != -1 && col_jog != -1);





    destruirTabuleiro(tab);
    return 0;
}
