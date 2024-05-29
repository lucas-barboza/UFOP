#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

#include "labirinto.h"

typedef struct {
    Celula* inicio;
    int tamanho;
} Pilha;

void executaPilha(int, int);

void desalocaPilha (Pilha*);

void iniciaPilha(Pilha*, int*);

int pilhaVazia(Pilha*);

void limpaPilha(Pilha*);

Pilha* criaPilha();

void pilhaEmpilha(Pilha*, Posicao*);

Posicao* pilhaDesempilha(Pilha*);

void acharSaidaPilha(Labirinto*, Percurso*, Pilha*, int, int);

void imprimeLabirintoPilha(Labirinto*, Percurso*, Pilha*, int, int);

#endif
