#ifndef TAD-BUKU_H_INCLUDED
#define TAD-BUKU_H_INCLUDED

typedef struct peca *Pilha;

struct tabuleiro {
    int lin;
    int col;
    Pilha **casa;
};

typedef struct tabuleiro Tabuleiro;

Tabuleiro* criaTabuleiro(int tam);

void iniciarTabuleiro(Tabuleiro *tab);

int alturaPilha(Pilha pilha);

Pilha inserirPeca(Pilha p);

Pilha removerPeca(Pilha p);

void imprimeTabuleiro(Tabuleiro *tab);

void destruirTabuleiro(Tabuleiro *tab);




//Funções auxiliares.

void menu();

void limpaTela();


#endif // TAD-BUKU_H_INCLUDED
