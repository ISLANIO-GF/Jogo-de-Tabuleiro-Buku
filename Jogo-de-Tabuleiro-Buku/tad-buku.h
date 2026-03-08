#ifndef TAD_BUKU_H_INCLUDED
#define TAD_BUKU_H_INCLUDED


typedef struct peca *Pilha;
typedef struct tabuleiro Tabuleiro;

//Função que cria o tabuleiro.
Tabuleiro* criaTabuleiro(int tam);

//Função para iniciar o tabuleiro com uma peça em cada casa.
void iniciarTabuleiro(Tabuleiro *tab);

//Função que determina a altura de uma pelha (número de peças).
int alturaPilha(Pilha pilha);

//Função para inserir peças.
Pilha inserirPeca(Pilha p);

//Função para remover peças.
Pilha removerPeca(Pilha p);

//Função que imprime o tabuleiro.
void imprimeTabuleiro(Tabuleiro *tab);

//Função para destruir o tabuleiro.
void destruirTabuleiro(Tabuleiro *tab);

//Função para criar pilha da mão e de potuação dos jogadores.
Pilha* criaPilha();

//Função responsável por coletar as peças no tabuleiro.
void coletarPecas(Tabuleiro *tab, int jogada, Pilha *mao, char jogador);

//Função para realizar a jogada.
void fazerJogada(Tabuleiro *tab, Pilha *mao);

//Função que verifica as condições de parada do jogo.
//Primeira condição: Linha escolhida está vazia.
int condicaoParadaLinhaVazia(Tabuleiro *tab, int escolha);

//Segunda condição: Coluna escolhida está vazia.
int condicaoParadaColunaVazia(Tabuleiro *tab, int escolha);

//Terceira condição: Só existe uma peça em cada casa do tabuleiro.
int condicaoParadaUnicaPeca(Tabuleiro *tab);


//Função que verifica se houve pontuaçao dos jogadores.
void verificaPontuacao(Tabuleiro *tab, Pilha *pontuacao, char jogador);

//Função que exibe o menu do jogo.
void menu();

//Função que limpa a tela durante em certas ocasiões do jogo.
void limpaTela();

//Função pausa.
void pausa();



#endif // TAD_BUKU_H_INCLUDED
