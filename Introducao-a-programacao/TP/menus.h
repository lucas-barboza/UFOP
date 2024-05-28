/*
Nome: Lucas de Oliveira Barboza
Matrícula: 21.2.4173
Turma: 31
*/

#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED

#define tam 3

int menuInicial(int **matriz, int *continuarJogo);
int carregaJogo(int **matriz, int *contadorJogadas, int *continuarJogo);
int dificuldade(int **matriz, int *contadorJogadas, int *continuarJogo, int **novaMatriz);
int instrucoes(int *continuarJogo, int **matriz, int *contadorJogadas);

#endif

