/*
Nome: Lucas de Oliveira Barboza
Matrícula: 21.2.4173
Turma: 31
*/

#ifndef VALIDACAO_H_INCLUDED
#define VALIDACAO_H_INCLUDED

char *minusculo(char *entrada);
int validaMenu(int *continuarJogo, int **matriz, int *contadorJogadas);
int validaDificuldade(int *continuarJogo, int **matriz, int *contadorJogadas);
int validaInstrucoes(int *continuarJogo, int **matriz, int *contadorJogadas);
int validaGameplay(int **matriz, int *contadorJogadas);
int validaArquivoExistente();
int **ordenaMatriz(int **matriz);

#endif
