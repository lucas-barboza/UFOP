/*
Nome: Lucas de Oliveira Barboza
Matrícula: 21.2.4173
Turma: 31
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "embaralha.h"

void embaralhaMatriz(int **matriz, int nivelDificuldade) { //Função para embaralhar a matriz
	srand(time(NULL)); //COLOCA A SEMENTE
	int numeroAnterior = 0, posicaoZero[] = { 2, 2 }; //Crio a variavel numeroAnteiror para verificar o número aleatorio anterior e não cair em loop. posicaoZero é a posição inicial que o zero se encontra.
	for (int k = 0; k < nivelDificuldade; k++) { //Embaralha o nivelDificuldade(20, 40 ou 80) vezes.
		int tamanho; //Variavel que mostra o tamanho do vetor que vai salvar os números do lado do ZERO(2, 3 ou 4).
		int *numerosEmVoltaZero = numerosAoLadoDoZero(posicaoZero, matriz, &tamanho); //Retorna um vetor com os números que estão do lado do ZERO
		int aleatorio = numeroAleatorio(&tamanho, numerosEmVoltaZero, numeroAnterior); //Retorna um número aleatório dos números que estão do lado do ZERO
		int *posicaoRandom = posicaoAleatorio(matriz, &tamanho, aleatorio); //Retorna um vetor com a posicação desse número aleatório na matriz
		for (int i = 0; i < tam; i++) {
		int aux; // Crio a variavel aux no inicio do primeiro for para fazer o método bubble sort
			for (int j = 0; j < tam; j++) {
				if (posicaoZero[0] == i && posicaoZero[1] == j) { //Encontra a posição do zero na matriz
					aux = matriz[i][j]; //Aux salva o valor ZERO
					matriz[i][j] = aleatorio; //A posição que o ZERO estava agora fica o número aleatório
					matriz[posicaoRandom[0]][posicaoRandom[1]] = aux; // A posição do número aleatório é igual a aux que vale ZERO.
					posicaoZero[0] = posicaoRandom[0]; //Salva a posição i do ZERO
					posicaoZero[1] = posicaoRandom[1]; //Salva a posição j do ZERO
				}
			}
		}
		numeroAnterior = aleatorio; //Numero anterior é agora o ultimo número aleatorio sorteado
		free(numerosEmVoltaZero); //Libera o vetor numerosEmVoltaZero
		free(posicaoRandom); //Libera o vetor posicaoRandom
	}
	printf("\n                  Tabuleiro embaralhado. Vamos começar o jogo!\n");
}

int *posicaoAtual(int **matriz) { //Função que retorna um vetor de onde está posicionado o ZERO
	int *posicaoAtual = malloc(2 * sizeof(int));
	for (int i = 0; i < tam; i++) {
		for (int j = 0; j < tam; j++) {
			if (!matriz[i][j]) { //Achou o ZERO e muda os valores do vetor posicaoAtual
				posicaoAtual[0] = i;
				posicaoAtual[1] = j;
			}
		}
	}
	return posicaoAtual;
}

int *numerosAoLadoDoZero(int *posicaoZero, int **matriz, int *tamanho) { //Função que retorna um vetor com os números do lado ao ZERO possíveis de serem movidos.
	int *numerosAoLado; //Crio o vetor
	for (int i = 0; i < tam; i++) {
		for (int j = 0; j < tam; j++) {
			if (posicaoZero[0] == i && posicaoZero[1] == j) { //Acha onde o ZERO está
				if ((i == 0 && j == 0) || (i == 0 && j == 2) || (i == 2 && j == 0) || (i == 2 && j == 2)) { //Este if cria um vetor de duas posições. Salva os dois números possíveis que podem ser movidos.
					//QUINAS
					*tamanho = 2;
					numerosAoLado = malloc(*tamanho * sizeof(int));
					if (i == 0 && j == 0) {
						numerosAoLado[0] = matriz[i][j + 1];
						numerosAoLado[1] = matriz[i + 1][j];
					}
					else if (i == 0 && j == 2) {
						numerosAoLado[0] = matriz[i][j - 1];
						numerosAoLado[1] = matriz[i + 1][j];
					}
					else if (i == 2 && j == 0) {
						numerosAoLado[0] = matriz[i - 1][j];
						numerosAoLado[1] = matriz[i][j + 1];
					}
					else {
						numerosAoLado[0] = matriz[i - 1][j];
						numerosAoLado[1] = matriz[i][j - 1];
					}
				}
				else if ((i == 0 && j == 1) || (i == 1 && j == 0) || (i == 1 && j == 2) || (i == 2 && j == 1)) { //Este if cria um vetor de três posições. Salva os três números possíveis que podem ser movidos.
					//PONTAS NO MEIO
					*tamanho = 3;
					numerosAoLado = malloc(*tamanho * sizeof(int));
					if (i == 0 && j == 1) {
						numerosAoLado[0] = matriz[i][j - 1];
						numerosAoLado[1] = matriz[i][j + 1];
						numerosAoLado[2] = matriz[i + 1][j];
					}
					else if (i == 1 && j == 0) {
						numerosAoLado[0] = matriz[i - 1][j];
						numerosAoLado[1] = matriz[i][j + 1];
						numerosAoLado[2] = matriz[i + 1][j];
					}
					else if (i == 1 && j == 2) {
						numerosAoLado[0] = matriz[i - 1][j];
						numerosAoLado[1] = matriz[i][j - 1];
						numerosAoLado[2] = matriz[i + 1][j];
					}
					else {
						numerosAoLado[0] = matriz[i - 1][j];
						numerosAoLado[1] = matriz[i][j - 1];
						numerosAoLado[2] = matriz[i][j + 1];
					}
				}
				else { //Este else cria um vetor de quatro posições. Salva os quatro números possíveis que podem ser movidos.
					//MEIO
					*tamanho = 4;
					numerosAoLado = malloc(*tamanho * sizeof(int));
					numerosAoLado[0] = matriz[i - 1][j];
					numerosAoLado[1] = matriz[i][j - 1];
					numerosAoLado[2] = matriz[i][j + 1];
					numerosAoLado[3] = matriz[i + 1][j];
				}
			}
		}
	}
	return numerosAoLado;
}

int numeroAleatorio(int *tamanho, int *numerosEmVoltaZero, int numeroAnterior) { //Função que chama a função rand() para gerar o número aletorio entre os possíveis.
	int numeroAleatorio = 0;
	do {
		int array[*tamanho]; //Cria um vetor para salvar os números em volta do ZERO
		for (int i = 0; i < *tamanho; i++) { //Salva os números em volta do ZERO
			array[i] = numerosEmVoltaZero[i];
		}
		int posicaoAleatoria = rand() % *tamanho; //Sorteia a posição aleatória pelo tamanho do vetor
		numeroAleatorio = array[posicaoAleatoria]; //O número aletório é o número no vetor em que a posição foi sorteada.
	} while (numeroAleatorio == numeroAnterior); //While para sortear um número diferente do aleatório anterior
	return numeroAleatorio;
}

int *posicaoAleatorio(int **matriz, int *tamanho, int aleatorio) { //Função que retorna a posição do aleatório
	int *posicaoAleatorio = malloc(2 * sizeof(int));
	for (int i = 0; i < tam; i++) {
		for (int j = 0; j < tam; j++) {
			if (matriz[i][j] == aleatorio) { //Acha a posição do aleatório e retorna ela por um vetor
				posicaoAleatorio[0] = i;
				posicaoAleatorio[1] = j;
			}
		}
	}
	return posicaoAleatorio;
}
