#ifndef TAD_BUKU_H_INCLUDED
#define TAD_BUKU_H_INCLUDED


typedef struct peca *Pilha;
typedef struct tabuleiro Tabuleiro;

//Função que cria o tabuleiro.
Tabuleiro* criaTabuleiro(int tam);

//Função para iniciar o tabuleiro com uma peça em cada casa.
void iniciarTabuleiro(Tabuleiro *tab);

//Função para destruir o tabuleiro.
void destruirTabuleiro(Tabuleiro *tab);

//Função que imprime o tabuleiro.
void imprimeTabuleiro(Tabuleiro *tab);

//Função para criar uma pilha.
Pilha* criaPilha();

//Função para destruir uma pilha.
void destruirPilha(Pilha *p);

//Função para remover peças.
int removerPeca(Pilha *p);

//Função responsável por coletar as peças no tabuleiro.
void coletarPecas(Tabuleiro *tab, int jogada, Pilha *mao, char jogador);

//Função para realizar a jogada.
void fazerJogada(Tabuleiro *tab, Pilha *mao, int tam_tab, char *jogador_01, char *jogador_02, Pilha pontuacao_jog_branco, Pilha pontuacao_jog_preto);

//Função que verifica as condições de parada do jogo.
//Primeira condição: Linha escolhida está vazia.
int condicaoParadaLinhaVazia(Tabuleiro *tab, int escolha, Pilha *pontuacao);

//Segunda condição: Coluna escolhida está vazia.
int condicaoParadaColunaVazia(Tabuleiro *tab, int escolha, Pilha *pontuacao);

//Terceira condição: Só existe uma peça em cada casa do tabuleiro.
int condicaoParadaUnicaPeca(Tabuleiro *tab, Pilha *pontuacaoBranco, Pilha *pontuacaoPreto);


//Função que verifica se houve pontuaçao dos jogadores.
void verificaPontuacao(Tabuleiro *tab, Pilha *pontuacao, char jogador);

//Função que exibe menu de pontuação dos jogadores.
void exiberPontuacao(int tam_tab, char *jogador_01, char *jogador_02, Pilha pontuacao_jog_branco, Pilha pontuacao_jog_preto);

//Função que exibe o menu do jogo.
void menu();

//Função que limpa a tela em certas ocasiões do jogo.
void limpaTela();

//Função pausa.
void pausa();

//Função que exibe as regras do jogo.
void exibirRegras();



#endif // TAD_BUKU_H_INCLUDED
