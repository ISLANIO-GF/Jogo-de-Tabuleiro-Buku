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

            printf("\n");
            for(int i = 0; i < tam_tab * 3.5 - 12; i++)
                printf("=");
            printf(" Tabuleiro Criado com sucesso! ");
            for(int i = 0; i < tam_tab * 3.5 - 12; i++)
                printf("=");

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
    removerPeca(&mao); //O objetivo aqui é deixar a mão sem nenhuma peça.
    removerPeca(&pontuacao_jog_branco); //O objetivo aqui é deixar a pontuação do jogador branco zerada.
    removerPeca(&pontuacao_jog_preto); //O objetivo aqui é deixar a pontuação do jogador branco zerada.


    //Iniciando o jogo.
    limpaTela();
    printf("\nPara comerçamos precisamos do nome dos jogadores.\n");

    //Informações dos jogadores.
    printf("\nNome do Jogador Branco: ");
    fgets(jogador_01, 50, stdin);
    jogador_01[strcspn(jogador_01, "\n")] = '\0';

    printf("\nNome do Jogador Preto: ");
    fgets(jogador_02, 50, stdin);
    jogador_02[strcspn(jogador_02, "\n")] = '\0';

    //Começando a partida.
    printf("\n===== Iniciando o Jogo. Boa sorte ao jogadores! =====\n");
    do{
        if(jogada % 2 != 0){
            limpaTela();
            imprimeTabuleiro(tab);
            printf("\nJogador (Branco) %s escolha uma linha: ", jogador_01);
            scanf("%d", &lin_jog);

            if(condicaoParadaLinhaVazia(tab, lin_jog - 1, &pontuacao_jog_preto)) //Função que verifica se o jogador escolheu uma linha vazia.
                break;

            coletarPecas(tab, lin_jog - 1, &mao, 'B'); //'B' é o sinal para a função que a jogada é do jogador branco.
            limpaTela();
            imprimeTabuleiro(tab);

            fazerJogada(tab, &mao);
            verificaPontuacao(tab, &pontuacao_jog_branco, 'B'); //'B' é o sinal para a função que a jogada é do jogador branco.
            printf("\nPontuação Total do jogador (Branco) %s: %d\n", jogador_01, alturaPilha(pontuacao_jog_branco));
            pausa();

            if(jogada != 1)
                if(condicaoParadaUnicaPeca(tab, &pontuacao_jog_branco, &pontuacao_jog_preto)) //Função que verifica se existem apeas uma peça em cada casa do tabuleiro (condição para finalizar o jogo).
                    break;

            jogada++;

        }
        else {
            limpaTela();
            imprimeTabuleiro(tab);
            printf("\nJogador (Preto) %s escolha uma coluna: ", jogador_02);
            scanf("%d", &col_jog);

            if(condicaoParadaColunaVazia(tab, col_jog - 1, &pontuacao_jog_branco)) //Função que verifica se o jogador escolheu uma linha vazia.
                break;

            coletarPecas(tab, col_jog - 1, &mao, 'P'); //'P' é o sinal para a função que a jogada é do jogador preto.
            limpaTela();
            imprimeTabuleiro(tab);

            fazerJogada(tab, &mao);
            verificaPontuacao(tab, &pontuacao_jog_preto, 'P'); //'P' é o sinal para a função que a jogada é do jogador preto.
            printf("\nPontuação Total do jogador (Preto) %s: %d\n", jogador_02, alturaPilha(pontuacao_jog_preto));
            pausa();

            if(jogada > 2)
                if(condicaoParadaUnicaPeca(tab, &pontuacao_jog_branco, &pontuacao_jog_preto)) //Função que verifica se existem apeas uma peça em cada casa do tabuleiro (condição para finalizar o jogo).
                    break;

            jogada++;
        }
    } while(lin_jog != -1 && col_jog != -1);



    printf("\nPontuação Total do jogador (Branco) %s: %d\n", jogador_01, alturaPilha(pontuacao_jog_branco));
    printf("\nPontuação Total do jogador (Preto) %s: %d\n", jogador_02, alturaPilha(pontuacao_jog_preto));

    destruirTabuleiro(tab);
    return 0;
}
