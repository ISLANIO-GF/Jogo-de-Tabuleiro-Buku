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
                    printf(" [   ] ");
                else
                    printf("  [%d]  ", alturaPilha(p));

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

//Função responsável por realizar a jogada do jogador 01.
int jogadaLinha(Tabuleiro *tab, int linha){
    if(linha < 0 || linha >= tab->lin){
        return 0;
    } else {
        for(int c = 0; c < tab->col; c++){
            while(alturaPilha(tab->casa[linha][c]) != NULL)
                tab->casa[linha][c] = removerPeca(tab->casa[linha][c]);
        }
    }
    return 1;
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
