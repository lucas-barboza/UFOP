/*
Nome: Lucas de Oliveira Barboza
Matrícula: 21.2.4173
Turma: 31
*/

#ifndef EMBARALHA_H_INCLUDED
#define EMBARALHA_H_INCLUDED

#define tam 3

void embaralhaMatriz(int **matriz, int nivelDificuldade);
int *posicaoAtual(int **matriz);
int *numerosAoLadoDoZero(int *posicaoZero, int **matriz, int *tamanho);
int numeroAleatorio(int *tamanho, int *numerosEmVoltaZero, int numeroAnterior);
int *posicaoAleatorio(int **matriz, int *tamanho, int aleatorio);

#endif
