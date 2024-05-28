/*
Nome: Lucas de Oliveira Barboza
Matrícula: 21.2.4173
Turma: 31
*/

#ifndef GAMEPLAY_H_INCLUDED
#define GAMEPLAY_H_INCLUDED

#define tam 3

int gameplay(int **matriz, int *contadorJogadas);
int checaMovimento(int **matriz, int numeroMover);
int movePeca(int **matriz, int numeroMover, int *contadorJogadas);
int verificaFim(int **matriz);

#endif

