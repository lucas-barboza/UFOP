/*
Nome: Lucas de Oliveira Barboza
Matrícula: 21.2.4173
Turma: 31
*/

#include <stdio.h>
#include <stdlib.h>
#include "gameplay.h"
#include "embaralha.h"
#include "validacao.h"
#include "estilizacao.h"
#include "matriz.h"

int gameplay(int **matriz, int *contadorJogadas) { //Função para o usuário jogar
	printf("\n   .--------------------------------------------------------------------.\n");
	printf("   |                                                                    |\n");
	printf("   |                             ");printf(BG_BLUE(YELLOW(BOLD("  Resta 8  "))));printf("                            |\n");
	printf("   |                                                                    |\n");
	printf("   |                    .---------------------------.                   |\n");
	printf("   |                    |       ");printf(TAB_TL TAB_HOR TAB_HOR TAB_HOR TAB_TJ TAB_HOR TAB_HOR TAB_HOR TAB_TJ TAB_HOR TAB_HOR TAB_HOR TAB_TR);printf("       |                   |\n");
	for (int i = 0; i < tam; i++) {
		printf("   |                    |       ");printf(TAB_VER);
		for (int j = 0; j < tam; j++) {
			if (matriz[i][j] != 0) printf(" %d ", matriz[i][j]);
			else printf("   ");
			printf(TAB_VER);
		}
		printf("       |                   |");
		if (i != 2) {
			printf("\n   |                    |       "TAB_ML TAB_HOR TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_HOR TAB_MR);
			printf("       |                   |\n");
		}
	}
	printf("\n   |                    |       ");printf(TAB_BL TAB_HOR TAB_HOR TAB_HOR TAB_BJ TAB_HOR TAB_HOR TAB_HOR TAB_BJ TAB_HOR TAB_HOR TAB_HOR TAB_BR);printf("       |                   |\n");
	printf("   |                    .---------------------------.                   |\n");
	printf("   |                                                                    |\n");
	printf("   |                                                                    |\n");
	printf("   |                                                                    |\n");
	printf("   .--------------------------------------------------------------------.\n");
	printf("\n                        Quantidade de jogadas até agora: %d\n", *contadorJogadas);
	printf("\n              Digite um comando ou número de peça que deseja mover: ");
	int opcao = validaGameplay(matriz, contadorJogadas); //Valida a entrada
	if (opcao == -1) return 1; //Usuário digitou 'voltar'
	else if(opcao == -2) return 0; //Usuário digitou 'sair'
	else if(opcao == -4) { //Usuário digitou um comando inexistente
		printf("\n                               "BG_RED("Comando inválido.")"\n");
		return gameplay(matriz, contadorJogadas);
	}
	return movePeca(matriz, opcao, contadorJogadas); //Usuário digitou uma peça e chama a função movePeca para a validação e fazer a jogada.
}

int movePeca(int **matriz, int numeroMover, int *contadorJogadas) {
	if (numeroMover == -3) return gameplay(matriz, contadorJogadas); //A pessoa digitou 'salvar'
	int retorno = checaMovimento(matriz, numeroMover); //Chama a função checaMovimento para ver se a peça que o usuário digitou pode ser movida
	if (retorno) { //Se não puder. Exibe uma mensagem de erro e chama a função gameplay pro usuário digitar novamente
		printf("\n                        "BG_RED("Não")" é possível mover a peça "BOLD("%d")".\n", numeroMover);
		return gameplay(matriz, contadorJogadas);
	}
	else { //Se puder trocar a peça. Vai fazer a mudança pelo método bubble sort
		int aux, zero = 0;
		int *posicaoZero = posicaoAtual(matriz); //Retorna um vetor com a posição do ZERO
		for (int i = 0; i < tam; i++) {
			for (int j = 0; j < tam; j++) {
				if (matriz[i][j] == numeroMover) { //Acha o número que o usuário quer mover na matriz
					aux = matriz[i][j]; //Aux salva o valor do número
					matriz[i][j] = zero; //A posição do número é igual a ZERO
					matriz[posicaoZero[0]][posicaoZero[1]] = aux; //A posição do ZERO é agora o número
				}
			}
		}
		free(posicaoZero); //Libera posicaoZero
		contadorJogadas[0]++; //Soma +1 no contador de jogadas
		if (verificaFim(matriz) == 0) { //Chama a função verificaFim pra saber se o usuário venceu
			return gameplay(matriz, contadorJogadas); //Se não, retorna gameplay pro usuário jogar novamente
		}
		else { //Se o usuário ganhou, mostra o menu dando os parabéns e retorna 0 que sinaliza o final do programa.
			printf("\n   .--------------------------------------------------------------------.\n");
			printf("   |                                                                    |\n");
			printf("   |                             ");printf(BG_BLUE(YELLOW(BOLD("  Resta 8  "))));printf("                            |\n");
			printf("   |                                                                    |\n");
			printf("   |                    .---------------------------.                   |\n");
			printf("   |                    |       ");printf(TAB_TL TAB_HOR TAB_HOR TAB_HOR TAB_TJ TAB_HOR TAB_HOR TAB_HOR TAB_TJ TAB_HOR TAB_HOR TAB_HOR TAB_TR);printf("       |                   |\n");
			for (int i = 0; i < tam; i++) {
				printf("   |                    |       ");printf(TAB_VER);
				for (int j = 0; j < tam; j++) {
					if (matriz[i][j] != 0) printf(" %d ", matriz[i][j]);
					else printf("   ");
					printf(TAB_VER);
				}
				printf("       |                   |");
				if (i != 2) {
					printf("\n   |                    |       "TAB_ML TAB_HOR TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_HOR TAB_MR);
					printf("       |                   |\n");
				}
			}
			printf("\n   |                    |       ");printf(TAB_BL TAB_HOR TAB_HOR TAB_HOR TAB_BJ TAB_HOR TAB_HOR TAB_HOR TAB_BJ TAB_HOR TAB_HOR TAB_HOR TAB_BR);printf("       |                   |\n");
			printf("   |                    .---------------------------.                   |\n");
			printf("   |                              "BG_BLUE("PARABÉNS!!")"                            |\n");
			printf("   |                             "BG_GREEN("VOCÊ GANHOU!")"                           |\n");
			printf("   |                          "BG_YELLOW("OBRIGADO POR JOGAR!")"                       |\n");
			printf("   .--------------------------------------------------------------------.\n");
			printf("\n                  Você completou o "BG_BLUE(YELLOW(BOLD(" Resta 8 ")))" com %d movimentos.\n\n", *contadorJogadas);
			setbuf(stdin, NULL); //Limpeza de buffer. Coloca o valor NULL no bufer stdin(que é o buffer do teclado);
			return 0;
		}
	}
}

int checaMovimento(int **matriz, int numeroMover) { //Função que checa se o movimento que o usuário quer é possível
	int *posicaoZero = posicaoAtual(matriz); //Acha a posicao do ZERO
	int tamanho; //Variavel que mostra o tamanho do vetor que vai salvar os números do lado do ZERO(2, 3 ou 4).
	int *numerosEmVoltaZero = numerosAoLadoDoZero(posicaoZero, matriz, &tamanho); //Retorna um vetor com os números que estão do lado do ZERO
	int numeroErrado = 1; //Começa como TRUE que o número não pode ser movido
	for (int i = 0; i < tamanho; i++) {
		if (numerosEmVoltaZero[i] == numeroMover) { //Se o número digitado pelo usuário estiver no vetor numerosEmVoltaZero, o numeroErrado fica FALSE
			numeroErrado = 0;
		}
	}
	free(posicaoZero); //Libera posicaoZero
	free(numerosEmVoltaZero); //Libera numerosEmVoltaZero
	return numeroErrado;
}

int verificaFim(int **matriz) { //Função que verifica o fim do jogo
	int **matrizFim = criaMatriz(); //Cria a matriz ordenada
	int venceu = 1; //Começa como TRUE se ele venceu
	for (int i = 0; i < tam; i++) {
		for (int j = 0; j < tam; j++) {
			if (matrizFim[i][j] != matriz[i][j]) // Se estiver alguma posição com valor diferente, venceu fica FALSE
				venceu = 0;
		}
	}
	liberaMatriz(matrizFim); //Chama a função para liberar a matrizFIM
	if (venceu)
		return 1; //Retorna 1 se a pessoa venceu
	return 0; //Retorna 0 se a pessoa não venceu
}

