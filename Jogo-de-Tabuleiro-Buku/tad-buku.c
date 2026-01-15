#include <stdio.h>
#include <stdlib.h>
#include "tad-buku.h"


#define FUNDO_XADREZ "\x1b[48;2;240;217;181m"
#define FUNDO_PRETO  "\x1b[40m"
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
            Peca *novo = (Peca*)malloc(sizeof(Peca));
            if(novo != NULL)
            novo->prox = NULL;
            tab->casa[i][j] = novo;
        }
    }
    return tab;
}


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

void imprimeTabuleiro(Tabuleiro *tab){
    if(tab == NULL){
        printf("Tabuleiro não foi criado!");
    } else {
        printf("\n");
        for(int i = 0; i < tab->lin; i++){
            printf("\n");
            for(int j = 0; j < tab->col; j++){
                Pilha p = tab->casa[i][j];

                if(i == 0 && j == 0){
                    printf("\t ");
                    for(int k = 0; k < tab->col; k++)
                        printf("  C%02d  ", k + 1);
                    printf("\n\n");
                }
                if(j == 0){
                    printf(RESET);
                    printf(" L%02d  -  ", i + 1);
                }

                if((i+j) % 2 == 0)
                    printf(FUNDO_XADREZ TEXTO_PRETO);
                else
                    printf(FUNDO_PRETO TEXTO_BRANCO);

                if(p == NULL)
                    printf("  [  ]  ");
                else
                    printf("  [%d]  ", alturaPilha(p));
            }
            printf("\n");
        }
        printf(RESET);
    }
}

Pilha* criaMaoDoJogador(){
    Pilha *mao = (Pilha*)malloc(sizeof(Pilha));
    if(mao != NULL)
        *mao = NULL;
    return mao;
}


//Funções auxiliares.

void menu(){
    printf("\n");
    printf("========= JOGO DE TABULEIRO BUKU =========");
    printf("\n");
}

void limpaTela(){
    printf("\033[2J\033[H");
}
