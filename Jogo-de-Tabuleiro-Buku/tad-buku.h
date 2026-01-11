#ifndef TAD-BUKU_H_INCLUDED
#define TAD-BUKU_H_INCLUDED


typedef struct peca *Pilha;
typedef struct tabuleiro Tabuleiro;

Tabuleiro* criaTabuleiro(int tam);

int vazia(Pilha *topo);

int alturaPilha(Pilha topo);

void imprimeTabuleiro(Tabuleiro *tab);


#endif // TAD-BUKU_H_INCLUDED
