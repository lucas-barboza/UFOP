#include "labirinto.h"
#include <stdio.h>
#include <stdlib.h>

Labirinto *alocaLabirinto(int linha, int coluna){                                                                   // Funcao para alocar o labirinto de acordo com o tamanho que o usuario digitou
    Labirinto *labirinto = (Labirinto *)malloc(sizeof(Labirinto));  // Aloca o struct labirinto
    labirinto->tabuleiro = (char **)malloc(sizeof(char *) * linha); // Aloca as linhas do tabuleiro
    for (int i = 0; i < linha; i++) {
        labirinto->tabuleiro[i] = (char *)malloc(sizeof(char) * coluna); // Aloca as colunas do tabuleiro
    }
    labirinto->piorCaso = 0; // Inicializa o pior caso
    return labirinto;        // Retorna o labirinto alocado
}

Percurso *alocaPercurso(Labirinto *labirinto) {                                                                                       // Funcao para alocar o percurso
    Percurso *percurso = (Percurso *)malloc(sizeof(Percurso));                          // Aloca o struct percurso
    percurso->posicao = (Posicao *)malloc(sizeof(Posicao) * (labirinto->piorCaso + 1)); // Aloca o vetor de struct posicao. O tamanho de vetor e +1 pois no vetor vai ter a posicao inicial
    percurso->menorCaminhoX = malloc(sizeof(int) * (labirinto->piorCaso + 1));          // Aloca o vetor do menor caminho X. O tamanho inicial e o pior caso +1
    percurso->menorCaminhoY = malloc(sizeof(int) * (labirinto->piorCaso + 1));          // Aloca o vetor do menor caminho Y. O tamanho inicial e o pior caso +1
    percurso->contadorTamanhoCaminho = 0;                                               // Contador do tamanho do caminho atual que esta fazendo
    percurso->index = 0;                                                                // Index do vetor posicao
    percurso->contSemSaida = 0;                                               // Contador tamanho caminho sem saida
    percurso->quantidadeAchados = 0;                                                    // Para verificar se encontrou algum caminho
    percurso->menorCaminho = labirinto->piorCaso + 1;                                   // Menor caminho inicializa com o piorCaso
    return percurso;                                                                    // Retorna o percurso alocado
}

void leLabirinto(Labirinto *labirinto, int linha, int coluna) { // Funcao que le o labirinto
    int c;
    while ((c = getc(stdin)) != EOF && c != '\n')
        ; // Descarta o restante da linha
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            c = getc(stdin);
            if (c != '\n') { // Verifica se não é uma quebra de linha
                labirinto->tabuleiro[i][j] = c;
                if (labirinto->tabuleiro[i][j] == ' ')
                    labirinto->piorCaso++; // Verifica as os caminhos possiveis e soma no pior caso
            }
            else {
                j--; // Decrementa o índice para repetir a posição
            }
        }
        while ((c = getc(stdin)) != EOF && c != '\n')
            ; // Descarta o restante da linha
    }
}

int *achaRato(Labirinto *labirinto, Percurso *percurso, int linha, int coluna) {                                // Funcao para achar a posicao do rato
    percurso->verificaRato = -2; // Inicializa que o rato nao esta no labirinto
    int *posicaoRato = (int *)malloc(sizeof(int) * 2);
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            if (labirinto->tabuleiro[i][j] == 'M') {
                posicaoRato[0] = i;         // Salva a posicao X do rato no index 0 do vetor posicaoRato
                posicaoRato[1] = j;         // Salva a posicao Y do rato no index 1 do vetor posicaoRato
                percurso->verificaRato = 0; // Sinaliza que o rato esta no labirinto
            }
        }
    }
    return posicaoRato;
}

// Funcao apra desalocar o vetor de sctruct posicao, vetores menorCaminhoX/Y e o struct percurso
void desalocaPercurso(Percurso *percurso) {
    if (percurso->posicao != NULL)
        free(percurso->posicao);
    free(percurso->menorCaminhoX);
    free(percurso->menorCaminhoY);
    free(percurso);
}

// Funcao apra desalocar o tabuleiro e o struct labirinto
void desalocaLabirinto(Labirinto *labirinto, int linha) {
    for (int i = 0; i < linha; i++)
        free(labirinto->tabuleiro[i]);
    free(labirinto->tabuleiro);
    free(labirinto);
}