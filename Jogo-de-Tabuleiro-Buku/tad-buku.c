#include <stdio.h>
#include <stdlib.h>
#include "tad-buku.h"

#define RESET        "\x1b[0m"
#define FUNDO_AMARELO "\x1b[43m"
#define FUNDO_PRETO  "\x1b[40m"
#define TEXTO_PRETO  "\x1b[30m"
#define TEXTO_BRANCO "\x1b[37m"


struct tabuleiro {
    int lin;
    int col;
    Pilha **casas;
};

struct casa {
    char cor;
    struct casa *prox;
};

typedef struct casa Casa;


Tabuleiro* criaTabuleiro(int tam){
    Tabuleiro* tab = (Tabuleiro*)malloc(sizeof(Tabuleiro));
    if (tab == NULL){
        printf("Erro ao criar o tabuleiro");
        exit(1);
    }
    tab->lin = tam;
    tab->col = tam;
    tab->casas = (Pilha**)malloc(tam * sizeof(Pilha*));
    for (int i = 0; i < tam; i++){
        tab->casas[i] = (Pilha*)malloc(tam * sizeof(Pilha));
        for(int j = 0; j < tam; j++){
            Casa *novo = (Casa*)malloc(sizeof(Casa));
            if((i + j) % 2 == 0)
                novo->cor = 'B';
            else
                novo->cor = 'P';
            novo->prox = NULL;
            tab->casas[i][j] = novo;
        }
    }
    return tab;
}


int alturaPilha(Pilha topo){
    if(topo == NULL)
        return 0;
    else {
        int cont = 0;
        Casa *aux = topo;
        while(aux != NULL){
            cont++;
            aux = aux->prox;
        }
        return cont;
    }
}

void imprimeTabuleiro(Tabuleiro *tab){
    if(tab == NULL){
        printf("Tabuleiro não foi criado");
        return;
    } else {
        printf("\n");
        for(int i = 0; i < tab->lin; i++){
            for(int j = 0; j < tab->col; j++){
                Pilha p = tab->casas[i][j];

                if((i+j) % 2 == 0)
                    printf(FUNDO_AMARELO TEXTO_PRETO);
                else
                    printf(FUNDO_PRETO TEXTO_BRANCO);

                if(p == NULL)
                    printf(" [  ] ");
                else
                    printf(" [%d] ", alturaPilha(p));
            }
            printf("\n");
        }
        printf(RESET);
    }
}
