#ifndef TAD-BUKU_H_INCLUDED
#define TAD-BUKU_H_INCLUDED


typedef struct peca *Pilha;
typedef struct tabuleiro Tabuleiro;


Tabuleiro* criaTabuleiro(int tam);

int alturaPilha(Pilha pilha);

void imprimeTabuleiro(Tabuleiro *tab);

Pilha* criaMaoDoJogador();



//Funções auxiliares.

void menu();

void limpaTela();


#endif // TAD-BUKU_H_INCLUDED
