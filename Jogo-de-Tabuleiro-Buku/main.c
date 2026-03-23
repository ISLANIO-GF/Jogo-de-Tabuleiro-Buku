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

    //Mostrando regras.
    menu();
    int resp;
    do{
        printf("\nMostrar regras do jogo:\n");
        printf("1 - SIM\n");
        printf("2 - NÂO\n");
        scanf("%d", &resp);
        printf("\n");
        if(resp == 1){
            exibirRegras();
            printf("\n");
            while(getchar() != '\n');
            pausa();
            limpaTela();
        }
        if(resp != 1 && resp != 2)
            printf("Resposta inválida!\n");

    }while(resp != 1 && resp != 2);


    //Criando o jogo.
    do{
        printf("Informe o tamanho do tabuleiro: ");
        scanf("%d", &tam_tab);

        if(tam_tab % 2 == 0 && tam_tab > 3){
            tab = criaTabuleiro(tam_tab);
            iniciarTabuleiro(tab);

            printf("\n");
            for(int i = 0; i < tam_tab * 3.5 - 12; i++)
                printf("=");
            printf(" Tabuleiro Criado com sucesso! ");
            for(int i = 0; i < tam_tab * 3.5 - 12; i++)
                printf("=");
            printf("\n");

            imprimeTabuleiro(tab);
            while(getchar() != '\n');
            pausa();
        }
        else{
            limpaTela();
            menu();
            printf("\n");
            printf("\nO tamanho do tabuleiro deve ser maior que 3 e par.\n");
            printf("Tente novamente!\n");
            printf("\n");
        }

    }while(tam_tab % 2 != 0 || tam_tab < 3);

    //criando pilha para mão do jogador e pontuação.
    mao = criaPilha();
    pontuacao_jog_branco = criaPilha();
    pontuacao_jog_preto = criaPilha();

    //Iniciando o jogo. Coletando dados dos jogadores.
    limpaTela();
    printf("\nPara comerçamos o jogo precisamos do nome dos jogadores.\n");

    //Informações dos jogadores.
    printf("\nNome do Jogador Branco: ");
    fgets(jogador_01, 50, stdin);
    jogador_01[strcspn(jogador_01, "\n")] = '\0';

    printf("\nNome do Jogador Preto: ");
    fgets(jogador_02, 50, stdin);
    jogador_02[strcspn(jogador_02, "\n")] = '\0';

    //Começando a partida.
    printf("\n===== Iniciando o Jogo. Boa sorte aos jogadores! =====\n");
    pausa();
    do{
        if(jogada % 2 != 0){
            limpaTela();
            exiberPontuacao(tam_tab, jogador_01, jogador_02, pontuacao_jog_branco, pontuacao_jog_preto);
            imprimeTabuleiro(tab);

            printf("\nJogador (Branco) %s escolha uma linha: ", jogador_01);
            scanf("%d", &lin_jog);

            if(condicaoParadaLinhaVazia(tab, lin_jog - 1, pontuacao_jog_preto)) //Função que verifica se o jogador escolheu uma linha vazia.
                break;

            coletarPecas(tab, lin_jog - 1, mao, 'B'); //'B' é o sinal para a função que a jogada é do jogador branco.
            limpaTela();
            exiberPontuacao(tam_tab, jogador_01, jogador_02, pontuacao_jog_branco, pontuacao_jog_preto);
            imprimeTabuleiro(tab);

            fazerJogada(tab, mao, tam_tab, jogador_01, jogador_02, pontuacao_jog_branco, pontuacao_jog_preto);
            verificaPontuacao(tab, pontuacao_jog_branco, 'B'); //'B' é o sinal para a função que a jogada é do jogador branco.
            printf("\nPontuação Total do jogador (Branco) %s: %d\n", jogador_01, alturaPilha(pontuacao_jog_branco));

            if(lin_jog > 0 && lin_jog <= tam_tab) //Corrige o bugg quando a escolha da linha é inválida.
                while(getchar() != '\n');
            pausa();

            if(jogada != 1) //Essa regra é dispensada para a primeira jogada.
                if(condicaoParadaUnicaPeca(tab, pontuacao_jog_branco, pontuacao_jog_preto)) //Função que verifica se existem apeas uma peça em cada casa do tabuleiro (condição para finalizar o jogo).
                    break;

            jogada++;

        }
        else {
            limpaTela();
            exiberPontuacao(tam_tab, jogador_01, jogador_02, pontuacao_jog_branco, pontuacao_jog_preto);
            imprimeTabuleiro(tab);

            printf("\nJogador (Preto) %s escolha uma coluna: ", jogador_02);
            scanf("%d", &col_jog);

            if(condicaoParadaColunaVazia(tab, col_jog - 1, pontuacao_jog_branco)) //Função que verifica se o jogador escolheu uma linha vazia.
                break;

            coletarPecas(tab, col_jog - 1, mao, 'P'); //'P' é o sinal para a função que a jogada é do jogador preto.
            limpaTela();
            exiberPontuacao(tam_tab, jogador_01, jogador_02, pontuacao_jog_branco, pontuacao_jog_preto);
            imprimeTabuleiro(tab);

            fazerJogada(tab, mao, tam_tab, jogador_01, jogador_02, pontuacao_jog_branco, pontuacao_jog_preto);
            verificaPontuacao(tab, pontuacao_jog_preto, 'P'); //'P' é o sinal para a função que a jogada é do jogador preto.
            printf("\nPontuação Total do jogador (Preto) %s: %d\n", jogador_02, alturaPilha(pontuacao_jog_preto));

            if(col_jog > 0 && col_jog <= tam_tab) //Corrige o bugg quando a escolha da coluna é inválida.
                while(getchar() != '\n');
            pausa();

            if(condicaoParadaUnicaPeca(tab, pontuacao_jog_branco, pontuacao_jog_preto)) //Função que verifica se existem apeas uma peça em cada casa do tabuleiro (condição para finalizar o jogo).
                break;

            jogada++;

        }
    } while(lin_jog != -1 && col_jog != -1);


    //Resultado da partida.
    printf("\n");
    for(int i = 0; i < tam_tab * 3.5 - 5; i++)
        printf("=");
    printf(" JOGO FINALIZADO ");
    for(int i = 0; i < tam_tab * 3.5 - 5; i++)
        printf("=");
    printf("\n");

    int pontJog01 = alturaPilha(pontuacao_jog_branco);
    int pontJog02 = alturaPilha(pontuacao_jog_preto);

    printf("\nPontuação Total do jogador (Branco) %s: %d\n", jogador_01, pontJog01);
    printf("\nPontuação Total do jogador (Preto) %s: %d\n", jogador_02, pontJog02);

    printf("\n");
    for(int i = 0; i < tam_tab * 3.5 - 2; i++)
        printf("=");
    printf(" RESULTADO ");
    for(int i = 0; i < tam_tab * 3.5 - 2; i++)
        printf("=");
    printf("\n");


    if(pontJog01 == pontJog02)
        printf("\nEmpate! Que tal outra partida de desempate?\n");
    else if(pontJog01 > pontJog02)
        printf("\nParabéns ao jogador %s por ter vencido o jogo!!!\n", jogador_01);
    else
        printf("\nParabéns ao jogador %s por ter vencido o jogo!!!\n", jogador_02);


    printf("\n");
    for(int i = 0; i < tam_tab * 7 + 7; i++)
        printf("=");
    printf("\n");


    //Liberando memória.
    destruirPilha(mao);
    destruirPilha(pontuacao_jog_branco);
    destruirPilha(pontuacao_jog_preto);
    destruirTabuleiro(tab);

    return 0;
}
