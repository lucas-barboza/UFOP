#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

void executaFila(int linha, int coluna) {
    Labirinto *labirinto = alocaLabirinto(linha, coluna); // Aloca o labirinto
    leLabirinto(labirinto, linha, coluna); // Le o labirinto
    Fila *fila = criaFila(); // Aloca a fila
    Percurso *percurso = alocaPercurso(labirinto); // Aloca o percurso
    int *posicaoRato = achaRato(labirinto, percurso, linha, coluna); // Acha a posicao inicial do rato
    filaInicia(fila, posicaoRato); // Inicia a fila
    acharSaidaFila(labirinto, percurso, fila, linha, coluna); // Acha a saida do rato, se existe
    imprimeLabirintoFila(labirinto, percurso, fila, linha, coluna); // Imprimi o labirinto
    free(posicaoRato); // Desaloca o vetor de inteiros posicaoRato
    desalocaFila(fila); // Desaloca o struct fila
    desalocaPercurso(percurso); // Desaloca o struct percurso
    desalocaLabirinto(labirinto, linha); // Desaloca o struct labirinto
}

// Funcao para alocar a fila, inciar os ponteiros inicio e fim com NULO e inciar o tamanho com 0
Fila *criaFila() {
    Fila *fila = (Fila *)malloc(sizeof(Fila));
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
    return fila;
}

// Funcao para iniciar a fila criando uma nova celula com a posicao do rato
void filaInicia(Fila *fila, int *posicaoRato) {
    Celula *aux = (Celula *)malloc(sizeof(Celula));
    aux->posicao = (Posicao *)malloc(sizeof(Posicao));
    aux->posicao->x = posicaoRato[0]; // Coloca a posicao X na nova celula
    aux->posicao->y = posicaoRato[1]; // Coloca a posicao Y na nova celula
    aux->prox = NULL; // Aponta para NULL
    fila->inicio = aux; // Agora o ponteiro inicio aponta para nova celula
    fila->fim = aux; // Agora o ponteiro fim aponta para nova celula
}

// Funcao que verifica se a fila esta vazia
int FilaVazia(Fila *pFila) {
    return pFila->inicio == NULL;
}

// Funcao que enfilera a fila
void FilaEnfileira(Fila *fila, Posicao *posicao) {
    Posicao *posicaoAux = (Posicao *)malloc(sizeof(Posicao));
    posicaoAux->x = posicao->x; // Salva a posicao de enfilerar em uma Struct Posicao auxiliar
    posicaoAux->y = posicao->y;

    Celula *aux = (Celula *)malloc(sizeof(Celula));
    aux->posicao = posicaoAux; // Salva a posicao atual na nova Celula

    if (fila->inicio == NULL) // Se o inicio for nulo, o inicio aponta para nova celula
        fila->inicio = aux;
    
    aux->prox = NULL; // A nova celula aponta para NULO

    if (fila->fim != NULL) // Se o ponteiro fim nao for nulo, ele aponta para nova celula
        fila->fim->prox = aux;

    fila->fim = aux; // Ponteiro fim aponta para nova celula
    fila->tamanho++; // Soma um no tamanho da fila
}

// Funcao para desenfilerar da fila
Posicao *FilaDesenfileira(Fila *fila) {
    if (FilaVazia(fila)) // Verifica se a fila é vazia
        return NULL;
    Posicao *posicaoAux;
    Celula *aux = fila->inicio; // Ponteiro auxiliar aponta para primeira celula
    if (fila->inicio == fila->fim) { // Verifica se a 
        fila->fim = NULL;
    }
    fila->inicio = fila->inicio->prox; // Ponteiro inicio aponta para o proximo da proxima celula
    posicaoAux = aux->posicao; // Salva a posicao da celular que vai ser desalocada
    free(aux); // Libera a celula
    return posicaoAux; // Retorna a posicao
}

// Funcao para achar a saida
void acharSaidaFila(Labirinto *labirinto, Percurso* percurso, Fila *fila, int linha, int coluna) {
    Posicao *posicao;
    while (fila->inicio != NULL) { // Continua ate o ponteiro inicio ser nulo

        posicao = FilaDesenfileira(fila); // Desenfilera e pega a posicao desenfilirada

        if (posicao == NULL) // Se retornar uma posicao NULA acaba o laço
            return;

        Posicao *posicaoEnfileirar = (Posicao *)malloc(sizeof(Posicao));
        posicaoEnfileirar->x = posicao->x; // Adiciona a posicao X em um struct Posicao
        posicaoEnfileirar->y = posicao->y; // Adiciona a posicao Y em um struct Posicao

        // DIREITA
        int podeIrParaDireita = posicao->y + 1 < coluna ? 1 : 0;
        if (podeIrParaDireita && labirinto->tabuleiro[posicao->x][posicao->y + 1] == ' ') {
            posicaoEnfileirar->y++; // Soma um no Y
            FilaEnfileira(fila, posicaoEnfileirar); // Enfilera a nova posicao
            labirinto->tabuleiro[posicaoEnfileirar->x][posicaoEnfileirar->y] = 'o'; // Coloca 'o' no caminho percorrido pelo rato
            // Encontrou o menor caminho e finaliza o laco
            if (posicaoEnfileirar->x == linha - 2 && posicaoEnfileirar->y == coluna - 1) {
                free(posicao);
                free(posicaoEnfileirar);
                limpaFila(fila);
                break;
            }
            posicaoEnfileirar->y--; // Subtrai um no Y
        }

        // BAIXO
        if (labirinto->tabuleiro[posicao->x + 1][posicao->y] == ' ') {
            posicaoEnfileirar->x++; // Soma um no X
            FilaEnfileira(fila, posicaoEnfileirar); // Enfilera a nova posicao
            labirinto->tabuleiro[posicaoEnfileirar->x][posicaoEnfileirar->y] = 'o'; // Coloca 'o' no caminho percorrido pelo rato
            posicaoEnfileirar->x--; // Subtrai um no X
        }

        // ESQUERDA
        if (labirinto->tabuleiro[posicao->x][posicao->y - 1] == ' ') {
            posicaoEnfileirar->y--; // Subtrai um no Y
            FilaEnfileira(fila, posicaoEnfileirar); // Enfilera a nova posicao
            labirinto->tabuleiro[posicaoEnfileirar->x][posicaoEnfileirar->y] = 'o'; // Coloca 'o' no caminho percorrido pelo rato
            posicaoEnfileirar->y++; // Soma um no Y
        }

        // CIMA
        if (labirinto->tabuleiro[posicao->x - 1][posicao->y] == ' ') {
            posicaoEnfileirar->x--; // Subtrai um no X
            FilaEnfileira(fila, posicaoEnfileirar); // Enfilera a nova posicao
            labirinto->tabuleiro[posicaoEnfileirar->x][posicaoEnfileirar->y] = 'o'; // Coloca 'o' no caminho percorrido pelo rato
            posicaoEnfileirar->x++; // Soma um no X
        }

        int d;
        scanf("%d", &d);
        imprimeLabirintoFila(labirinto, percurso, fila, linha, coluna);
        if (posicao != NULL)
            free(posicao); // Desaloca a posicao
        free(posicaoEnfileirar); // Desaloca a posicao para enfileirar
    }
}

// Funcao para imprimir o labirinto
void imprimeLabirintoFila(Labirinto *labirinto, Percurso *percurso, Fila *fila, int linha, int coluna) {
    // Verificacao para quando o rato ja esta na saida do tabuleiro digitado pelo usuario
    if (percurso->verificaRato == -2)
        printf("O rato nao esta no labirinto.\n");

    // Verificacao para quando o rato ja esta na saida do tabuleiro digitado pelo usuario
    else if (percurso->verificaRato == -1)
        printf("O rato ja esta na saída.\n");

    // Imprimi o labirinto
    else {
        printf("%d\n", fila->tamanho);
        for (int i = 0; i < linha; i++) {
            for (int j = 0; j < coluna; j++) {
                printf("%c", labirinto->tabuleiro[i][j]);
            }
            printf("\n");
        }
    }
}

// Funcao para limpar a fila até que ponteiro inicio aponte para nulo
void limpaFila(Fila *fila) {
    Celula *aux;
    while (fila->inicio != NULL) {
        aux = fila->inicio;
        fila->inicio = aux->prox;
        free(aux->posicao);
        free(aux);
    }
}

// Funcao para desalocar a fila
void desalocaFila(Fila *fila) {
    free(fila);
}