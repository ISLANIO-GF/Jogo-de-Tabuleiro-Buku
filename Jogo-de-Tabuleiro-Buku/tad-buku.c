#include <stdio.h>
#include <stdlib.h>
#include "tad-buku.h"


#define FUNDO_XADREZ    "\x1b[48;2;240;217;181m"
#define FUNDO_MARROM    "\x1b[48;2;101;67;33m"
#define TEXTO_PRETO     "\x1b[30m"
#define TEXTO_BRANCO    "\x1b[37m"
#define TEXTO_VERDE     "\x1b[32m"
#define TEXTO_VERMELHO  "\x1b[31m"
#define RESET           "\x1b[0m"


struct tabuleiro {
    int lin;
    int col;
    Pilha **casa;
};

struct peca {
    struct peca *prox;
};

typedef struct peca Peca;



//Função para criar pilha.
Pilha* criaPilha(){
    Pilha *p = (Pilha*)malloc(sizeof(Pilha));
    if(p != NULL)
        *p = NULL;
    return p;
}

//Função para destruir uma pilha.
void destruirPilha(Pilha *p){
    if(p != NULL){
        Peca *aux;
        while(*p != NULL){
            aux = *p;
            *p = aux->prox;
            free(aux);
        }
        free(p);
    }

}

//Função que faz uma copia de pilha.
Pilha* backupPilha(Pilha *p){
    if(p == NULL || *p == NULL)
        return NULL;
    Pilha *novaPilha = criaPilha();
    Peca *aux = *p;
    while(aux != NULL){
        inserirPeca(novaPilha);
        aux = aux->prox;
    }
    return novaPilha;
}

//Função para inserir peças.
int inserirPeca(Pilha *p){
    if(p == NULL)
        return 0;
    Peca *novo = (Peca*)malloc(sizeof(Peca));
    if(novo == NULL)
        return 0;
    novo->prox = *p;
    *p = novo;
    return 1;
}

//Função para remover peças.
int removerPeca(Pilha *p){
    if(p == NULL || *p == NULL)
        return 0;
    else {
        Peca *aux = *p;
        *p = aux->prox;
        free(aux);
        return 1;
    }
}


//Função responsavelpor mover as peças do jogo.
int moverPecas(Pilha *origem, Pilha *destino){
    if(origem == NULL || *origem == NULL)
        return 0;

    Peca *aux = *origem;
    *origem = aux->prox;
    aux->prox = *destino;
    *destino = aux;

    return 1;
}

//Função que determina a altura de uma pilha (número de peças).
int alturaPilha(Pilha p){
    if(p == NULL)
        return 0;
    else {
        int cont = 0;
        Peca *aux = p;
        while(aux != NULL){
            cont++;
            aux = aux->prox;
        }
        return cont;
    }
}



//Função que cria o tabuleiro.
Tabuleiro* criaTabuleiro(int tam){
    Tabuleiro* tab = (Tabuleiro*)malloc(sizeof(Tabuleiro));
    if (tab == NULL){
        printf("\nErro ao criar o tabuleiro!\n");
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
            if(inserirPeca(&tab->casa[i][j]) == 0)
                printf("\nErro na inserção de peças na função iniciartabuleiro.\n");
        }
    }
}


//Função que faz uma copia do tabuleiro.
Tabuleiro* backupTabuleiro(Tabuleiro *tab){
    if(tab == NULL)
        return NULL;
    Tabuleiro *novoTab = (Tabuleiro*)malloc(sizeof(Tabuleiro));
    if(novoTab == NULL){
        printf("\nErro ao copiar tabuleiro.\n");
        return NULL;
    }
    novoTab->lin = tab->lin;
    novoTab->col = tab->col;
    novoTab->casa = (Pilha**)malloc(tab->lin * sizeof(Pilha*));
    for(int l = 0; l < tab->lin; l++){
        novoTab->casa[l] = (Pilha*)malloc(tab->col * sizeof(Pilha));
        for(int c = 0; c < tab->col; c++){
            Pilha *copia = backupPilha(&tab->casa[l][c]);
            if(copia != NULL){
                novoTab->casa[l][c] = *copia;
                free(copia);
            }
            else
                novoTab->casa[l][c] = NULL;
        }
    }
    return novoTab;
}

//Função para destruir o tabuleiro.
void destruirTabuleiro(Tabuleiro *tab){
    if(tab != NULL){
        for(int l = 0; l <tab->lin;l++){
            for(int c = 0; c < tab->col;c++){
                destruirPilha(tab->casa[l][c]);
            }
            free(tab->casa[l]);
        }
        free(tab->casa);
        free(tab);
    }
}


//Função que imprime o tabuleiro.
void imprimeTabuleiro(Tabuleiro *tab){
    if(tab == NULL)
        printf("Tabuleiro não foi criado!");

    else {
        printf("\n\t");
        for(int k = 0; k < tab->col; k++){
            printf(" C%02d   ", k + 1); //Imprime o cabeçalho das colunas.
        }
        printf("\n\n");

        //Imprime a parte de cima das casa dando o efeito quadrado do tabuleiro.
        for(int l = 0; l < tab->lin; l++){
            printf("       ");
            for(int c = 0; c < tab->col; c++){
                if((l+c) % 2 == 0)
                    printf(FUNDO_XADREZ);
                else
                    printf(FUNDO_MARROM);
                printf("       ");
            }
            printf(RESET);
            printf("\n");

           //Imprime a as peças dentro de cada casa.
            printf(" L%02d - ", l + 1); //Imprime o cabeçalho das linhas.
            for(int c = 0; c < tab->col; c++){
                Pilha p = tab->casa[l][c];

                if((l+c) % 2 == 0)
                    printf(FUNDO_XADREZ TEXTO_PRETO);
                else
                    printf(FUNDO_MARROM TEXTO_BRANCO);

                if(p == NULL)
                    printf("       ");
                else{
                    int altura = alturaPilha(p);
                    if(altura == 1)
                        printf("   @   ");
                    else if(altura == 2)
                        printf("   @@  ");
                    else{
                        printf(TEXTO_VERDE);
                        printf("  @@@  ");
                    }
                }

                printf(RESET);
            }
            printf("\n");

            //Imprime a parte de baixo das casa dando o efeito quadrado do tabuleiro.
            printf("       ");
            for(int c = 0; c < tab->col; c++){
                if((l+c) % 2 == 0)
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



//Função responsável por coletar as peças do jogador 01.
void coletarPecas(Tabuleiro *tab, int jogada, Pilha *mao, char jogador){
    if(jogada < 0 || jogada >= tab->lin || jogada >= tab->col){
        printf("\nJogada incorreta. Jogador perdeu a vez!\n");
        while(getchar() != '\n');
        pausa();
        return;
    }
    if(jogador == 'B') { //Faz a coleta das peças na horizontal.
        for(int c = 0; c < tab->col; c++){
            while(tab->casa[jogada][c] != NULL){
                if(moverPecas(&tab->casa[jogada][c], mao) == 0)
                    printf("\nErro ao mover peça da linha do tabuleiro para a mão do jogador.\n");
            }
        }
    }
    else if(jogador == 'P'){
        for(int l = 0; l < tab->lin; l++){
            while(tab->casa[l][jogada] != NULL){
                if(moverPecas(&tab->casa[l][jogada], mao) == 0)
                    printf("\nErro ao mover peça da coluna do tabuleiro para a mão do jogador.\n");
            }
        }
    }
    else{
        printf("Erro na função coletar peças");
        return;
    }

}

//Função que veriffica se o jogador está sem opções de jogada.
int validarJogada(Tabuleiro *tab, int histLinha[], int histColuna[], int l, int c, int jogada){
    int opLinha[] = {-1, 1, 0, 0};
    int opColuna[] = {0, 0, -1, 1};
    int novaLinha, novaColuna, jogadorPreso = 0;

    for(int i = 0; i < 4; i++){
        novaLinha = l + opLinha[i];
        novaColuna = c + opColuna[i];


        if(novaLinha > 0 && novaLinha <= tab->lin && novaColuna > 0 && novaColuna <= tab->col){
            int repetida = 0;
            for(int j = 0; j < jogada; j++){
                if(histLinha[j] == novaLinha && histColuna[j] == novaColuna){
                    repetida = 1;
                    break;
                }
            }
            if(repetida){
                jogadorPreso++;
            }
        }
        else {
            jogadorPreso++;
        }
    }
    if(jogadorPreso == 4)
        return 0;
    else
        return 1;
}

//Função que restaura o backup do Tabuleiro.
void restaurarBackupTab(Tabuleiro *tab, Tabuleiro *backup){
    if(tab == NULL || backup == NULL)
        return;
    int alt = 0;
    for(int l = 0; l < tab->lin; l++){
        for(int c = 0; c < tab->col; c++){
            while(tab->casa[l][c] != NULL)
                removerPeca(&tab->casa[l][c]);


            alt = alturaPilha(backup->casa[l][c]);
            while(alt > 0){
                inserirPeca(&tab->casa[l][c]);
                alt--;
            }
        }
    }
}

//Função que restaura o backup da mão.
void restaurarBackupMao(Pilha *mao, Pilha *backup){
    if(backup == NULL)
        return;

    while(*mao != NULL)
        removerPeca(mao);

    Peca *aux = *backup;
    while(aux != NULL){
        inserirPeca(mao);
        aux = aux->prox;
    }
}


//Função responsavel por realizar a jogada.
void fazerJogada(Tabuleiro *tab, Pilha *mao, int tam_tab, char *jogador_01, char *jogador_02, Pilha pontuacao_jog_branco, Pilha pontuacao_jog_preto){
    if(mao == NULL || *mao == NULL)
        return;

    int l = 0, c = 0, linhaAnterior = -1, colunaAnterior = -1, jogada = 0;
    int max = alturaPilha(*mao);
    int histLinha[max], histColuna[max];

    Tabuleiro *copiaTab = backupTabuleiro(tab);
    Pilha *copiaMao = backupPilha(mao);

    while(*mao != NULL){
        printf("\nSua mão tem %d peças.\n", alturaPilha(*mao));

        printf("Escolha uma posição para colocar uma peça de 1 a %d:\n", tab->col);
        printf("Linha: ");
        scanf("%d", &l);
        printf("Coluna: ");
        scanf("%d", &c);

        //Verifica se a posição escolhida está dentro do tabuleiro.
        if(l <= 0 || l > tab->lin || c <= 0 || c > tab->col){
            printf("\nPosição inválida! Tente novamente.\n");
            continue;
        }

        //Analisa se a jogada escolhida foi feita de forma ortogonal e ao lado da posição atual.
        if(linhaAnterior != -1){
            if(abs(l - linhaAnterior) + abs(c - colunaAnterior) != 1){
                printf("\nAs jogadas devem ser feitas de forma ortogonal! Tente novamente.\n");
                continue;
            }
        }

        //Verifica se a posição escolhida já foi preenchida dentro da jogada.
        int repetida = 0;
        for(int i = 0; i < jogada; i++){
            if(histLinha[i] == l && histColuna[i] == c){
                repetida = 1;
                break;
            }
        }
        if(repetida){
            printf("\nPosição já foi usada! Tente novamente.\n");
            continue;
        }

        //Realiza a jogada.
        if(moverPecas(mao, &tab->casa[l-1][c-1]) == 0)
            printf("\nErro ao mover peças da mão para o tabuleiro durante a jogada.\n");


        limpaTela();
        exiberPontuacao(tam_tab, jogador_01, jogador_02, pontuacao_jog_branco, pontuacao_jog_preto);
        imprimeTabuleiro(tab);

        if(alturaPilha(*mao) == 0 || validarJogada(tab, histLinha, histColuna, l, c, jogada)){
            linhaAnterior = l;
            colunaAnterior = c;

            histLinha[jogada] = l;
            histColuna[jogada] = c;
            jogada++;

        }
        else{
            printf("\nSua mão tem %d peças.\n", alturaPilha(*mao));
            printf("\nJogador impossibilitado de realizar novas jogadas.\n");
            printf("O jogo será reiniciado para o início da rodada!\n");
            while(getchar() != '\n');
            pausa();

            restaurarBackupTab(tab, copiaTab);
            restaurarBackupMao(mao, copiaMao);

            limpaTela();
            exiberPontuacao(tam_tab, jogador_01, jogador_02, pontuacao_jog_branco, pontuacao_jog_preto);
            imprimeTabuleiro(tab);

            linhaAnterior = -1;
            colunaAnterior = -1;
            jogada = 0;
            histLinha[jogada] = 0;
            histColuna[jogada] = 0;

            continue;

        }
    }
    destruirTabuleiro(copiaTab);
    destruirPilha(copiaMao);

   printf("\nAltura da pilha backupa: %d\n", alturaPilha(copiaMao));
}


//Função que verifica se houve pontuação dos jogadores.
void verificaPontuacao(Tabuleiro *tab, Pilha *pontuacao, char jogador){
    int alt = 0, parcial = 0;
    for(int l = 0; l < tab->lin; l++){
        for(int c = 0; c < tab->col; c++){

            //Verifica a pontuação por 3 peças para o jogador branco.
            if(jogador == 'B'){
                if((l+c) % 2 == 0){
                    alt = alturaPilha(tab->casa[l][c]);
                    if(alt >= 3){
                        while(alt > 0){
                            if(moverPecas(&tab->casa[l][c], pontuacao) == 0)
                                printf("\nErro ao mover peças do tabuleiro para a pilha de pontuação na função verificaPontuacao.\n");
                            alt--;
                            parcial++;
                        }
                    }
                }
            }
            //Verifica a pontuação para três peças para o jogador preto.
            else if(jogador == 'P'){
                if((l+c) % 2 != 0){
                    alt = alturaPilha(tab->casa[l][c]);
                    if(alt >= 3){
                        while(alt > 0){
                            if(moverPecas(&tab->casa[l][c], pontuacao) == 0)
                                printf("\nErro ao mover peças do tabuleiro para a pilha de pontuação na função verificaPontuacao.\n");
                            alt--;
                            parcial++;
                        }
                    }
                }
            }
            else{
                printf("Erro na função de pontuação!");
                return;
            }
        }
    }
    printf("\nPontuação na rodadada: %d", parcial);
}



//Função que verifica as condições de parada do jogo.
//Primeira condição: Linha escolhida está vazia.
int condicaoParadaLinhaVazia(Tabuleiro *tab, int escolha, Pilha *pontuacao){
    if(escolha < 0 || escolha >= tab->lin)
        return 0;

    int cond = 0, alt = 0;
    for(int c = 0; c < tab->col; c++){
        if(alturaPilha(tab->casa[escolha][c]) != 0){
            cond = 1;
            break;
        }
    }
    if(cond == 0){
        for(int l = 0; l < tab->lin; l++){
            for(int c = 0; c < tab->col; c++){
                alt = alturaPilha(tab->casa[l][c]);
                while(alt != 0){
                    if(moverPecas(&tab->casa[l][c], pontuacao) == 0)
                        printf("\nErro ao mover peças do tabuleiro para a pontuação do jogador na função condicaoParadaPorLinhaVazia.\n");
                    alt--;
                }
            }
        }
        return 1;
    }
    else
        return 0;
}

//Segunda condição: Coluna escolhida está vazia.
int condicaoParadaColunaVazia(Tabuleiro *tab, int escolha, Pilha *pontuacao){
    if(escolha < 0 || escolha >= tab->col)
        return 0;

    int cond = 0, alt = 0;
    for(int l = 0; l < tab->lin; l++){
        if(alturaPilha(tab->casa[l][escolha]) != 0){
            cond = 1;
            break;
        }
    }
    if(cond == 0){
        for(int l = 0; l < tab->lin; l++){
            for(int c = 0; c < tab->col; c++){
                alt = alturaPilha(tab->casa[l][c]);
                while(alt != 0){
                    if(moverPecas(&tab->casa[l][c], pontuacao) == 0)
                        printf("\nErro ao mover peças do tabuleiro para a pontuação do jogador na função condicaoParadaPorLinhaVazia.\n");
                    alt--;
                }
            }
        }
        return 1;
    }
    else
        return 0;
}

//Terceira condição: Só existe uma peça em cada casa do tabuleiro.
int condicaoParadaUnicaPeca(Tabuleiro *tab, Pilha *pontuacaoBranco, Pilha *pontuacaoPreto){
    int cond = 0;
    for(int l = 0; l < tab->lin; l++){
        for(int c = 0; c < tab->col;c++){
            if(alturaPilha(tab->casa[l][c]) > 1)
                return 0;
        }
    }
    int alt;
    for(int l = 0; l < tab->lin; l++){
        for(int c = 0; c < tab->col;c++){
            alt = alturaPilha(tab->casa[l][c]);
            if((l+c) % 2 == 0){
                while(alt > 0){
                    if(moverPecas(&tab->casa[l][c], pontuacaoBranco) == 0)
                        printf("\nErro ao mover peças do tabuleiro para a pilha de pontuação na função condicaoParadaUnicaPeca.\n");
                    alt--;
                }
            } else {
                while(alt > 0){
                    if(moverPecas(&tab->casa[l][c], pontuacaoPreto) == 0)
                        printf("\nErro ao mover peças do tabuleiro para a pilha de pontuação na função condicaoParadaUnicaPeca.\n");
                    alt--;
                }
            }
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
    char prox;
    do{
       prox = getchar();
    }while(prox != '\n');
}

//Função que exibe menu de pontuação dos jogadores.
void exiberPontuacao(int tam_tab, char *jogador_01, char *jogador_02, Pilha pontuacao_jog_branco, Pilha pontuacao_jog_preto){
    printf("\n");
    for(int i = 0; i < tam_tab * 7 + 7; i++)
        printf("=");

    printf("\nPontuação Total do jogador (Branco) %s: %d\n", jogador_01, alturaPilha(pontuacao_jog_branco));
    printf("\nPontuação Total do jogador (Preto) %s: %d\n", jogador_02, alturaPilha(pontuacao_jog_preto));

    for(int i = 0; i < tam_tab * 7 + 7; i++)
    printf("=");

    printf("\n");
}


//Função que exibe regras do jogo.
void exibirRegras(){

    printf("========================================================================================\n");
    printf("                               REGRAS DO JOGO BUKU\n");
    printf("========================================================================================\n");

    printf("1. O jogo é disputado por dois jogadores:\n");
    printf("   - Jogador Branco\n");
    printf("   - Jogador Preto\n\n");

    printf("2. O tabuleiro é composto por uma matriz de casas,\n");
    printf("   onde cada casa contém uma pilha de peças.\n\n");

    printf("3. Na sua vez, o jogador deve:\n");
    printf("   - Escolher uma linha do tabuleiro (caso seja o jogador branco\n");
    printf("     ou escolher uma coluna do tabuleiro (caso seja o jogador preto.\n");
    printf("   - Todas as peças decorrentes da sua escolha serão coletadas para sua mão.\n\n");

    printf("4. Após coletar as peças:\n");
    printf("   - O jogador deve distribuí-las pelo tabuleiro\n");
    printf("     seguindo as regras do jogo.\n\n");

    printf("5. Regras para a jogada:\n");
    printf("   - As peças devem ser distribuidas no tabuleiro de forma ortogonal a última jogada.\n");
    printf("   - Não é permitido passar por uma casa já utilizada dentro da rodada.\n");
    printf("   - Deve-se tomar cuidoda para não escolher posições fora do tabuleiro.\n\n");

    printf("5. Durante a jogada:\n");
    printf("   - O jogador pode continuar jogando dependendo\n");
    printf("     da posição final\n");
    printf("   - Ou pode ficar sem movimentos válidos\n\n");

    printf("6. Caso a jogada seja inválida:\n");
    printf("   - Toda a jogada deve ser desfeita\n");
    printf("   - O tabuleiro volta ao início da jogada.\n\n");

    printf("7. Quando o jogo termina?\n");
    printf("   - Quando existir apenas um peça em cada casa no final de uma rodada.\n");
    printf("     Nesse caso as peças serão distribuidas para os jogadores de acordo com a sua posição.\n");
    printf("   - Quando o jogador branco escolher uma linha que esteja vazia.\n");
    printf("   - Quando o jogador preto escolher uma coluna que esteja vazia.\n");
    printf("     Para ambos os casos de escolha vazia as peças ques restarem no tabuleiro\n");
    printf("     seguirão para a mão do oponente.\n\n");

    printf("8. Vence o jogador que tiver a maior quantidade de peças.\n\n");

    printf("========================================================================================\n");

}
