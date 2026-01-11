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

struct peca {
    char cor;
    struct peca *prox;
};

typedef struct peca Peca;


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
        for(int j = 0; j < tam; j++)
            tab->casas[i][j] = NULL;
    }
    for (int i = 0; i < tam; i++){
        for(int j = 0; j < tam; j++){
            Peca *topo = (Peca*)malloc(sizeof(Peca));
            if(topo == NULL){
                printf("Erro ao criar topo de peça.");
                exit(1);
            }
            topo->prox = NULL;
            if((i + j) % 2 == 0)
                topo->cor = 'B';
            else
                topo->cor ='P';
            tab->casas[i][j] = topo;
        }
    }
    return tab;
}

int vazia(Pilha *topo){
    if(topo == NULL)
        return 1;
    else if(*topo == NULL)
        return 1;
    else
        return 0;
}

int alturaPilha(Pilha topo){
    if(vazia(topo))
        return 0;
    else {
        int cont = 0;
        Peca *aux = topo;
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

                if(p->cor == 'B')
                    printf(FUNDO_AMARELO TEXTO_PRETO);
                else
                    printf(FUNDO_PRETO TEXTO_BRANCO);

                if(vazia(p))
                    printf(" [  ] ");
                else
                    printf(" [%d] ", alturaPilha(p));
            }
            printf("\n");
        }
        printf(RESET);
    }
}
