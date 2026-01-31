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
        printf("Erro ao inicializar tabuleiro");
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
                    printf(" [  ]  ");
                else
                    printf("  [%d]  ", alturaPilha(p));
            }
            printf("\n");
        }
        printf(RESET);
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

//Função que cria uma pilha (pode ser usada para criar a mão dos jogadores e a pilha de pontuação.
Pilha* criarPilha(){
    Pilha* novo = (Pilha*)malloc(sizeof(Pilha));
    if (novo == NULL){
        printf("Erro ao criar pilha.");
        exit(1);
    }
    *novo = NULL;
    return novo;
}

//Funções auxiliares.

//Função que exibe o menu do jogo.
void menu(){
    printf("\n========= JOGO DE TABULEIRO BUKU =========\n");
    printf("\nBem vido ao jogo de Tabuleiro Buku.\nPrepare-se para uma avalanche de diversão!\n");
}

//Função que limpa a tela durante em certas ocasiões do jogo.
void limpaTela(){
    printf("\033[2J\033[H");
}

void pausa(){
    printf("\nPrecione enter para continuar...");
    while(getchar() != '\n');
    char prox;
    do{
       prox = getchar();
    }while(prox != '\n');
}
