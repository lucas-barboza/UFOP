/*
Nome: Lucas de Oliveira Barboza
Matrícula: 21.2.4173
Turma: 31
*/

#include "menus.h" //Incluo o arquivo que estão as funções dos menus
#include "matriz.h" //Incluo o arquivo que estão as funções que cria a matriz e a libera


int main() {
	int **matriz = criaMatriz(); //Crio a matriz
	int continuarJogo = 0; //Crio a variavel que salva se tem algum jogo ativo. Começa com 0 = false
	menuInicial(matriz, &continuarJogo); //Função que começa o jogo
	liberaMatriz(matriz); //Libera a matriz
	return 0;
}

