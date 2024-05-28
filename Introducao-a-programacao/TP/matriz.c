/*
Nome: Lucas de Oliveira Barboza
Matrícula: 21.2.4173
Turma: 31
*/

#include <stdlib.h>
#include "matriz.h"

int **criaMatriz() { //Função que cria a matriz ordenada
	int **matriz = malloc(tam * sizeof(int*));
	for (int i = 0; i < tam; i++) {
		matriz[i] = malloc(tam * sizeof(int));
	}
	int inicial = 1; //Começa do 1
	for (int i = 0; i < tam; i++) {
		for (int j = 0; j < tam; j++) {
			if (inicial < 9) { 
				matriz[i][j] = inicial;
				inicial++;
			} else matriz[i][j] = 0; //Termina no 0 na posição 2-2
		}
	}
	return matriz;
}

void liberaMatriz(int **matriz) { //Funçao que libera a matriz
	for (int i = 0; i < tam; i++) {
		free(matriz[i]);
	}
	free(matriz);
}
