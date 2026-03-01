#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "tad-buku.h"



int main(){

    setlocale(LC_ALL, "Portuguese");

    //variáveis:
    char jogador_01[50], jogador_02[50];
    int tam_tab = 0, jogada = 1, lin_jog = 0, col_jog = 0;
    Tabuleiro *tab = NULL;
    Pilha *mao = NULL, *pontuacao_jog_branco = NULL, *pontuacao_jog_preto = NULL;

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

    //criando pilha para mão do jogador e pontuação.
    mao = criaPilha();
    pontuacao_jog_branco = criaPilha();
    pontuacao_jog_preto = criaPilha();


    /*
    No momento que se cria a pilha a mesma já inicia com um elemento.
    Para resolver esse problema chama a função removerPeca uma vez antes de iniciar o jogo.
    */
    mao = removerPeca(mao); //O objetivo aqui é deixar a mão sem nenhuma peça.
    pontuacao_jog_branco = removerPeca(pontuacao_jog_branco); //O objetivo aqui é deixar a pontuação do jogador branco zerada.
    pontuacao_jog_preto = removerPeca(pontuacao_jog_preto); //O objetivo aqui é deixar a pontuação do jogador branco zerada.


    //Iniciando o jogo.

    limpaTela();
    printf("\nPara comerçamos precisamos do nome dos jogadores.\n");

    //Informações dos jogadores.
    printf("\nNome do Jogador Branco: ");
    getchar();
    fgets(jogador_01, 50, stdin);
    jogador_01[strcspn(jogador_01, "\n")] = '\0';

    printf("\nNome do Jogador Preto: ");
    fgets(jogador_02, 50, stdin);
    jogador_02[strcspn(jogador_02, "\n")] = '\0';

    //Começando a partida.
    printf("\n===== Iniciando o Jogo. Boa sorte ao jogadores! =====\n");
    do{
        if(jogada % 2 != 0){
            imprimeTabuleiro(tab);
            printf("\nJogador (Branco) %s escolha uma linha: ", jogador_01);
            scanf("%d", &lin_jog);

            mao = coletarPecas(tab, lin_jog - 1, mao);
            limpaTela();
            imprimeTabuleiro(tab);

            printf("Mao antes = %d\n", alturaPilha(mao));
            fazerJogada(tab, &mao);
            printf("\nSua mão tem %d peças.\n", alturaPilha(mao));
            jogada++;
        }
        else {
            limpaTela();
            imprimeTabuleiro(tab);
            printf("\nJogador (Preto) %s escolha uma coluna: ", jogador_02);
            scanf("%d", &col_jog);
            jogada++;
        }
    } while(lin_jog != -1 && col_jog != -1);





    destruirTabuleiro(tab);
    return 0;
}
