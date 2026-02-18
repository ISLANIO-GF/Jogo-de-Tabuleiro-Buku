#include <stdio.h>
#include <stdlib.h>
#include "tad-buku.h"


#define FUNDO_XADREZ "\x1b[48;2;240;217;181m"
#define FUNDO_MARROM  "\x1b[48;2;101;67;33m"
#define TEXTO_PRETO  "\x1b[30m"
#define TEXTO_BRANCO "\x1b[37m"
#define RESET        "\x1b[0m"


struct tabuleiro {
    int lin;
    int col;
    Pilha **casa;
};

struct peca {
    struct peca *prox;
};

typedef struct peca Peca;

//Função que cria o tabuleiro.
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

//Função para iniciar o tabuleiro com uma peça em cada casa.
void iniciarTabuleiro(Tabuleiro *tab){
    for(int i = 0; i <tab->lin;i++){
        for(int j = 0; j < tab->col;j++){
            tab->casa[i][j] = inserirPeca(tab->casa[i][j]);
        }
    }
}

//Função para inserir peças.
Pilha inserirPeca(Pilha p){
    Peca *novo = (Peca*)malloc(sizeof(Peca));
    if(novo == NULL){
        printf("Erro ao inserir pecas");
        return p;
    }
    novo->prox = p;
    return novo;
}

//Função para remover peças.
Pilha removerPeca(Pilha p){
    if(p == NULL)
        return NULL;
    else {
        Peca *aux = p;
        p = p->prox;
        free(aux);
        return p;
    }
}

//Função que determina a altura de uma pelha (número de peças).
int alturaPilha(Pilha pilha){
    if(pilha == NULL)
        return 0;
    else {
        int cont = 0;
        Peca *aux = pilha;
        while(aux != NULL){
            cont++;
            aux = aux->prox;
        }
        return cont;
    }
}

//Função que imprime o tabuleiro.
void imprimeTabuleiro(Tabuleiro *tab){
    if(tab == NULL)
        printf("Tabuleiro não foi criado!");

    else {
        printf("\n\t");
        for(int k = 0; k < tab->col; k++){
            printf(" C%02d   ", k + 1);
        }
        printf("\n\n");

        for(int i = 0; i < tab->lin; i++){
            printf("       ");
            for(int j = 0; j < tab->col; j++){
                if((i+j) % 2 == 0)
                    printf(FUNDO_XADREZ);
                else
                    printf(FUNDO_MARROM);
                printf("       ");
            }
            printf(RESET);
            printf("\n");

            printf(" L%02d - ", i + 1);
            for(int j = 0; j < tab->col; j++){
                Pilha p = tab->casa[i][j];

                if((i+j) % 2 == 0)
                    printf(FUNDO_XADREZ TEXTO_PRETO);
                else
                    printf(FUNDO_MARROM TEXTO_BRANCO);

                if(p == NULL)
                    printf("       ");
                else{
                    int altura = alturaPilha(p);
                    if(altura == 1)
                        printf("   @   ");
                    else if(altura == 2)
                        printf("   @@  ");
                    else
                        printf("  @@@  ");
                }

                printf(RESET);
            }
            printf("\n");
            printf("       ");
            for(int j = 0; j < tab->col; j++){
                if((i+j) % 2 == 0)
                    printf(FUNDO_XADREZ);
                else
                    printf(FUNDO_MARROM);
                printf("       ");
            }
            printf(RESET);
            printf("\n");

        }
    }
}

//Função para destruir o tabuleiro.
void destruirTabuleiro(Tabuleiro *tab){
    if(tab != NULL){
        for(int i = 0; i <tab->lin;i++){
            for(int j = 0; j < tab->col;j++){
                while(tab->casa[i][j] != NULL)
                    tab->casa[i][j] = removerPeca(tab->casa[i][j]);
            }
            free(tab->casa[i]);
        }
        free(tab->casa);
        free(tab);
    }
}


//Função responsável por realizar a jogada do jogador 01.
Pilha* coletarPecas(Tabuleiro *tab, int linha, Pilha *mao){
    if(linha < 0 || linha >= tab->lin){
        printf("\nJogada incorreta. Jogador perdeu a vez!\n");
        pausa();
        return NULL;
    } else {
        for(int c = 0; c < tab->col; c++){
            while(alturaPilha(tab->casa[linha][c]) > 0){
                tab->casa[linha][c] = removerPeca(tab->casa[linha][c]);
                mao = inserirPeca(mao);
            }
        }
    }
    return mao;
}

void fazerJogada(Tabuleiro *tab, Pilha *mao){
    if(mao == NULL)
        printf("\nNão existe peças na mão do jogador!.\n");

    else{
        int l = 0, c = 0, lin_ant = -1, col_ant = -1, jogada = 0;
        int hist_linha[tab->lin], hist_col[tab->col];

        while(mao != NULL){
            printf("\nSua mão tem %d peças.\n", alturaPilha(mao));
            printf("Escolha uma posição para colocar uma peça de 1 a %d:\n", tab->col);
            printf("Linha: ");
            scanf("%d", &l);
            printf("Coluna: ");
            scanf("%d", &c);

            if(l <= 0 || l > tab->lin || c <= 0 || c > tab->col){
                printf("\nPosição inválida! Tente novamente.\n");
                continue;
            }

            if(lin_ant != -1){
                if(abs(l - lin_ant) + abs(c - col_ant) != 1){
                    printf("\nAs jogadas devem ser feitas de forma ortogonal! Tente novamente.\n");
                    continue;
                }
            }

            int repetida = 0;
            for(int i = 0; i < jogada; i++){
                if(hist_linha[i] == l && hist_col[i] == c){
                    repetida = 1;
                    break;
                }
            }
            if(repetida){
                printf("\nPosição já foi usada! Tente novamente.\n");
                continue;
            }

            tab->casa[l-1][c-1] = inserirPeca(tab->casa[l-1][c-1]);
            mao = removerPeca(mao);

            lin_ant = l;
            col_ant = c;

            hist_linha[jogada] = l;
            hist_col[jogada] = c;
            jogada++;

            limpaTela();
            imprimeTabuleiro(tab);
        }
    }
}

//Funções auxiliares.

//Função que exibe o menu do jogo.
void menu(){
    printf("\n========= JOGO DE TABULEIRO BUKU =========\n");
    printf("\nBem vido ao jogo de Tabuleiro Buku.\n");
}

//Função que limpa a tela durante em certas ocasiões do jogo.
void limpaTela(){
    printf("\033[2J\033[H");
}

void pausa(){
    printf("\n\nPrecione enter para continuar...");
    while(getchar() != '\n');
    char prox;
    do{
       prox = getchar();
    }while(prox != '\n');
}
