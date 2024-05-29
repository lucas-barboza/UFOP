#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

#include "labirinto.h"

typedef struct {
    Celula* inicio;
    Celula* fim;
    int tamanho;
} Fila;

void executaFila(int, int);

Fila* criaFila();

void filaInicia(Fila*, int*);

void limpaFila(Fila*);

int FilaVazia(Fila *);

void FilaEnfileira(Fila*, Posicao*);

Posicao* FilaDesenfileira(Fila *);

void acharSaidaFila(Labirinto*, Percurso*, Fila*, int, int);

void imprimeLabirintoFila(Labirinto*, Percurso*, Fila*, int, int);

void desalocaFila(Fila*);

#endif
