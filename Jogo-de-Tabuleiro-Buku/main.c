#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "tad-buku.h"



int main(){

    setlocale(LC_ALL, "Portuguese");

    //variáveis:
    char jogadorBranco[50], jogadorPreto[50];
    int tamanhoTabuleiro = 0, jogada = 1, linhaJogada = 0, colunaJogada = 0;
    Tabuleiro *tab = NULL;
    Pilha *mao = NULL, *pontuacaoJogadorBranco = NULL, *pontuacaoJogadorPreto = NULL;

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
        scanf("%d", &tamanhoTabuleiro);

        if(tamanhoTabuleiro % 2 == 0 && tamanhoTabuleiro > 3){
            tab = criaTabuleiro(tamanhoTabuleiro);
            iniciarTabuleiro(tab);

            printf("\n");
            for(int i = 0; i < tamanhoTabuleiro * 3.5 - 12; i++)
                printf("=");
            printf(" Tabuleiro Criado com sucesso! ");
            for(int i = 0; i < tamanhoTabuleiro * 3.5 - 12; i++)
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

    }while(tamanhoTabuleiro % 2 != 0 || tamanhoTabuleiro < 3);

    //criando pilhas para mão do jogador e pontuação.
    mao = criaPilha();
    pontuacaoJogadorBranco = criaPilha();
    pontuacaoJogadorPreto = criaPilha();

    //Iniciando o jogo. Coletando dados dos jogadores.
    limpaTela();
    printf("\nPara comerçamos o jogo precisamos do nome dos jogadores.\n");

    //Informações dos jogadores.
    printf("\nNome do Jogador Branco: ");
    fgets(jogadorBranco, 50, stdin);
    jogadorBranco[strcspn(jogadorBranco, "\n")] = '\0';

    printf("\nNome do Jogador Preto: ");
    fgets(jogadorPreto, 50, stdin);
    jogadorPreto[strcspn(jogadorPreto, "\n")] = '\0';

    //Iniciando a partida.
    printf("\n===== Iniciando o Jogo. Boa sorte aos jogadores! =====\n");
    pausa();
    do{
        if(jogada % 2 != 0){
            limpaTela();
            exibirPontuacao(tamanhoTabuleiro, jogadorBranco, jogadorPreto, pontuacaoJogadorBranco, pontuacaoJogadorPreto);
            imprimeTabuleiro(tab);

            printf("\nJogador (Branco) %s escolha uma linha: ", jogadorBranco);
            scanf("%d", &linhaJogada);

            if(condicaoParadaLinhaVazia(tab, linhaJogada - 1, pontuacaoJogadorPreto)) //Função que verifica se o jogador escolheu uma linha vazia.
                break;

            coletarPecas(tab, linhaJogada - 1, mao, 'B'); //'B' é o sinal para a função que a jogada é do jogador branco.
            limpaTela();
            exibirPontuacao(tamanhoTabuleiro, jogadorBranco, jogadorPreto, pontuacaoJogadorBranco, pontuacaoJogadorPreto);
            imprimeTabuleiro(tab);

            fazerJogada(tab, mao, tamanhoTabuleiro, jogadorBranco, jogadorPreto, pontuacaoJogadorBranco, pontuacaoJogadorPreto);
            verificaPontuacao(tab, pontuacaoJogadorBranco, 'B'); //'B' é o sinal para a função que a jogada é do jogador branco.
            printf("\nPontuação Total do jogador (Branco) %s: %d\n", jogadorBranco, alturaPilha(pontuacaoJogadorBranco));

            if(linhaJogada > 0 && linhaJogada <= tamanhoTabuleiro) //Corrige o bug quando a escolha da linha é inválida.
                while(getchar() != '\n');
            pausa();

            if(jogada != 1) //Essa regra é dispensada para a primeira rodada.
                if(condicaoParadaUnicaPeca(tab, pontuacaoJogadorBranco, pontuacaoJogadorPreto)) //Função que verifica se existem apeas uma peça em cada casa do tabuleiro (condição para finalizar o jogo).
                    break;

            jogada++;

        }
        else {
            limpaTela();
            exibirPontuacao(tamanhoTabuleiro, jogadorBranco, jogadorPreto, pontuacaoJogadorBranco, pontuacaoJogadorPreto);
            imprimeTabuleiro(tab);

            printf("\nJogador (Preto) %s escolha uma coluna: ", jogadorPreto);
            scanf("%d", &colunaJogada);

            if(condicaoParadaColunaVazia(tab, colunaJogada - 1, pontuacaoJogadorBranco)) //Função que verifica se o jogador escolheu uma linha vazia.
                break;

            coletarPecas(tab, colunaJogada - 1, mao, 'P'); //'P' é o sinal para a função que a jogada é do jogador preto.
            limpaTela();
            exibirPontuacao(tamanhoTabuleiro, jogadorBranco, jogadorPreto, pontuacaoJogadorBranco, pontuacaoJogadorPreto);
            imprimeTabuleiro(tab);

            fazerJogada(tab, mao, tamanhoTabuleiro, jogadorBranco, jogadorPreto, pontuacaoJogadorBranco, pontuacaoJogadorPreto);
            verificaPontuacao(tab, pontuacaoJogadorPreto, 'P'); //'P' é o sinal para a função que a jogada é do jogador preto.
            printf("\nPontuação Total do jogador (Preto) %s: %d\n", jogadorPreto, alturaPilha(pontuacaoJogadorPreto));

            if(colunaJogada > 0 && colunaJogada <= tamanhoTabuleiro) //Corrige o bug quando a escolha da coluna é inválida.
                while(getchar() != '\n');
            pausa();

            if(condicaoParadaUnicaPeca(tab, pontuacaoJogadorBranco, pontuacaoJogadorPreto)) //Função que verifica se existem apeas uma peça em cada casa do tabuleiro (condição para finalizar o jogo).
                break;

            jogada++;

        }
    } while(linhaJogada != -1 && colunaJogada != -1);


    //Resultados da partida.
    printf("\n");
    for(int i = 0; i < tamanhoTabuleiro * 3.5 - 5; i++)
        printf("=");
    printf(" JOGO FINALIZADO ");
    for(int i = 0; i < tamanhoTabuleiro * 3.5 - 5; i++)
        printf("=");
    printf("\n");

    int pontJog01 = alturaPilha(pontuacaoJogadorBranco);
    int pontJog02 = alturaPilha(pontuacaoJogadorPreto);

    printf("\nPontuação Total do jogador (Branco) %s: %d\n", jogadorBranco, pontJog01);
    printf("\nPontuação Total do jogador (Preto) %s: %d\n", jogadorPreto, pontJog02);

    printf("\n");
    for(int i = 0; i < tamanhoTabuleiro * 3.5 - 2; i++)
        printf("=");
    printf(" RESULTADO ");
    for(int i = 0; i < tamanhoTabuleiro * 3.5 - 2; i++)
        printf("=");
    printf("\n");


    if(pontJog01 == pontJog02)
        printf("\nEmpate! Que tal outra partida de desempate?\n");
    else if(pontJog01 > pontJog02)
        printf("\nParabéns ao jogador %s por ter vencido o jogo!!!\n", jogadorBranco);
    else
        printf("\nParabéns ao jogador %s por ter vencido o jogo!!!\n", jogadorPreto);


    printf("\n");
    for(int i = 0; i < tamanhoTabuleiro * 7 + 7; i++)
        printf("=");
    printf("\n");


    //Liberando memória.
    destruirPilha(mao);
    destruirPilha(pontuacaoJogadorBranco);
    destruirPilha(pontuacaoJogadorPreto);
    destruirTabuleiro(tab);

    return 0;
}
