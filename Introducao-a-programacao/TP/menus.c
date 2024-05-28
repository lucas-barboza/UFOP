/*
Nome: Lucas de Oliveira Barboza
Matrícula: 21.2.4173
Turma: 31
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menus.h"
#include "validacao.h" //Incluo o arquivo que faz as validações das entradas nos menus
#include "gameplay.h" //Incluo o arquivo da gameplay do usuario
#include "embaralha.h" //Incluo o arquivo que embaralha a matriz a partir da dificuldade
#include "estilizacao.h" //Incluo o arquivo que estiliza o código
#include "salvarjogo.h" //Incluo o arquivo que salva o jogo
#include "matriz.h" //Incluo o arquivo que cria uma matriz

int menuInicial(int **matriz, int *continuarJogo) { //Menu inicial do jogo
	int resultado = 1, opcao = 1, contadorJogadas[1] = { 0 }; //Crio o inteiro RESULTADO que controla quando o jogo acaba. O inteiro OPCAO para entrada do usuário. O inteiro CONTADORJOGADAS para contar as jogadas do usuário
	int **novaMatriz = criaMatriz();
	setbuf(stdin, NULL); //Limpeza de buffer. Coloca o valor NULL no bufer stdin(que é o buffer do teclado);
	do {
		printf("\n");
		printf("   .--------------------------------------------------------------------.\n");
		printf("   |                                                                    |\n");
		printf("   |                             ");printf(BG_BLUE(YELLOW(BOLD("  Resta 8  "))));printf("                            |\n");
		printf("   |                                                                    |\n");
		printf("   |                    .---------------------------.                   |\n");
		printf("   |                    |      1 - Novo jogo        |                   |\n");
		printf("   |                    |      2 - Continuar jogo   |                   |\n");
		printf("   |                    |      3 - Carregar jogo    |                   |\n");
		printf("   |                    |      4 - Instruções       |                   |\n");
		printf("   |                    |      0 - Sair             |                   |\n");
		printf("   |                    .---------------------------.                   |\n");
		printf("   |                                                                    |\n");
		printf("   |                                                                    |\n");
		printf("   |                                                        by:21.2.4173|\n");
		printf("   .--------------------------------------------------------------------.\n");
		printf("                           Digite a opção desejada: ");
		opcao = validaMenu(continuarJogo, matriz, contadorJogadas); //A função validaMenu retorna o resultado da validação do que o usuário digitou
		switch(opcao) {
			case 0:
				break;
			case 1:
				resultado = dificuldade(matriz, contadorJogadas, continuarJogo, novaMatriz); //Chama a função dificuldade que é um menu que pergunta ao usuário a dificuldade que deseja. RESULTADO controla se o jogo vai continuar ou acabar
				break;
			case 2: //Verifica se existe um jogo atual. Se SIM continua o jogo, se NAO aparece uma mensagem de erro
				if (*continuarJogo)
					resultado = gameplay(matriz, contadorJogadas);
				else {
					printf("\n                        Você " BG_RED("não")" iniciou nenhum jogo.");
					resultado = 1;
				}
				break;
			case 3:
				resultado = carregaJogo(matriz, contadorJogadas, continuarJogo); //Chama a função carregaJogo que é um menu para pessoa carregar o jogo salvo. RESULTADO controla se o jogo vai continuar ou acabar
				break;
			case 4:
				resultado = instrucoes(continuarJogo, matriz, contadorJogadas); //Chama a função instruções que é um menu para pessoa ter instruções do jogo. RESULTADO controla se o jogo vai continuar ou acabar
				break;
			case 5:
				printf("\n                            Você já está no menu inicial.\n"); //Este case é quando a pessoa digita 'voltar' já no menu inicial
				return menuInicial(matriz, continuarJogo);
				break;
			case -3:
				return menuInicial(matriz, continuarJogo); //Este case é quando a pessoa salva o seu jogo atual no menu inicial
				break;
			default:
				printf("\n                               "BG_RED("Comando inválido.")"\n"); //Mensagem de erro se a pessoa digitar uma entrada inválida
				return menuInicial(matriz, continuarJogo);
				break;
		}
	} while (opcao != 0 && resultado);
	liberaMatriz(novaMatriz);
	return 0;
}

int dificuldade(int **matriz, int *contadorJogadas, int *continuarJogo, int **novaMatriz) { //Menu para selecionar a difuldade do jogo
	printf("\n");
	printf("   .--------------------------------------------------------------------.\n");
	printf("   |                                                                    |\n");
	printf("   |                             ");printf(BG_BLUE(YELLOW(BOLD("  Resta 8  "))));printf("                            |\n");
	printf("   |                                                                    |\n");
	printf("   |                    .---------------------------.                   |\n");
	printf("   |                    |       ");printf(TAB_TL TAB_HOR TAB_HOR TAB_HOR TAB_TJ TAB_HOR TAB_HOR TAB_HOR TAB_TJ TAB_HOR TAB_HOR TAB_HOR TAB_TR);printf("       |                   |\n");
	for (int i = 0; i < tam; i++) {
		printf("   |                    |       ");printf(TAB_VER);
		for (int j = 0; j < tam; j++) {
			if (novaMatriz[i][j] != 0) printf(" %d ", novaMatriz[i][j]);
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
	printf("   |                             1 - Fácil                              |\n");
	printf("   |                             2 - Médio                              |\n");
	printf("   |                             3 - Difícil                            |\n");
	printf("   .--------------------------------------------------------------------.\n");
	printf("\n                             Tabuleiro ordenado!\n");
	printf("\n                          Digite o nível de dificuldade: ");
	int inputDificuldade = validaDificuldade(continuarJogo, matriz, contadorJogadas), nivelDificuldade; //Chama a função para validar as entradas e o inteiro NIVELDIFICULDADE para passar como parametro de acordo com o input do usuário
	switch (inputDificuldade) {
		case 0:
			return 0; //Retorna 0 para o menu inicial e assim fecha o jogo.
			break;
		case 1:
			ordenaMatriz(matriz); //Ordena a matriz novamente
			nivelDificuldade = 20; 
			contadorJogadas[0] = 0; //Reseta o contador de jogadas para 0
			embaralhaMatriz(matriz, nivelDificuldade); //Chama a função EMBARALHAR para embaralhar o jogo 20 vezes
			*continuarJogo = 1; //Agora existe um jogo ativo
			return gameplay(matriz, contadorJogadas); //Retorna a função GAMEPLAY para começar o jogo
			break;
		case 2:
			ordenaMatriz(matriz); //Ordena a matriz novamente
			nivelDificuldade = 40;
			contadorJogadas[0] = 0;//Reseta o contador de jogadas para 0
			embaralhaMatriz(matriz, nivelDificuldade); //Chama a função EMBARALHAR para embaralhar o jogo 40 vezes
			*continuarJogo = 1; //Agora existe um jogo ativo
			return gameplay(matriz, contadorJogadas); //Retorna a função GAMEPLAY para começar o jogo
			break;
		case 3:
			ordenaMatriz(matriz);
			nivelDificuldade = 80; //Ordena a matriz novamente
			contadorJogadas[0] = 0;//Reseta o contador de jogadas para 0
			embaralhaMatriz(matriz, nivelDificuldade); //Chama a função EMBARALHAR para embaralhar o jogo 80 vezes
			*continuarJogo = 1; //Agora existe um jogo ativo
			return gameplay(matriz, contadorJogadas); //Retorna a função GAMEPLAY para começar o jogo
			break;
		case 4:
			return menuInicial(matriz, continuarJogo); //A pessoa digitou voltar e retorna o MenuInicial
			break;
		case -1:
				printf("\n                        Você " BG_RED("não")" iniciou nenhum jogo."); // O usuário tentou salvar um jogo só que ela não iniciou nenhum ainda.
				return dificuldade(matriz, contadorJogadas, continuarJogo, novaMatriz);
				break;
		case -3: //Este case é quando a pessoa salva o seu jogo atual no menu dificuldade
				return dificuldade(matriz, contadorJogadas, continuarJogo, novaMatriz);
				break;
		default: //Este case é quando o usuário digitou nenhum comando existente.
			printf("\n                               "BG_RED("Comando inválido.")"\n");
			return dificuldade(matriz, contadorJogadas, continuarJogo, novaMatriz);
			break;
	}
	return 0;
}

int carregaJogo(int **matriz, int *contadorJogadas, int *continuarJogo) { //Menu para carregar um jogo salvo
	printf("\n");
	printf("   .--------------------------------------------------------------------.\n");
	printf("   |                                                                    |\n");
	printf("   |                             ");printf(BG_BLUE(YELLOW(BOLD("  Resta 8  "))));printf("                            |\n");
	printf("   |                                                                    |\n");
	printf("   |                    .---------------------------.                   |\n");
	printf("   |                    |                           |                   |\n");
	printf("   |                    |    Carregar jogo salvo    |                   |\n");
	printf("   |                    |                           |                   |\n");
	printf("   |                    |     Exemplo: jogo.txt     |                   |\n");
	printf("   |                    |                           |                   |\n");
	printf("   |                    .---------------------------.                   |\n");
	printf("   |                                                                    |\n");
	printf("   |                             1 - Voltar                             |\n");
	printf("   |                                                                    |\n");
	printf("   .--------------------------------------------------------------------.\n");
	printf("\n                         Digite o nome do arquivo: ");
	char entrada[1000];
	fgets(entrada, 1000, stdin);
	entrada[strcspn(entrada, "\n")] = '\0'; //Tira o barra '\n' e coloca o '\0' no lugar
	strcpy(entrada, minusculo(entrada)); //Chama a função MINUSCULO que transforma toda a entrada em minusculo.
	char salvar[] = "salvar ", cont = 0; //Aqui ele também pode salvar seu jogo atual antes de abrir outro.
	for (int i = 0; i < strlen(salvar); i++) { //For para verificar se a pessoa digitou 'salvar '
		if (salvar[i] == entrada[i]) cont++;
	}
	if (*continuarJogo && cont == 7) { //Verifica se tem algum jogo em andamento e se a pessoa digitou 'salvar '
		salvarJogo(entrada, matriz, contadorJogadas); //Chama a função para salvar o jogo
		return carregaJogo(matriz, contadorJogadas, continuarJogo); //Retorna o proprio menu depois de salvar
	}
	int retorno = atoi(entrada); //Cria um inteiro para transforma a entrada em um inteiro
	if (!strcmp(entrada, "sair")) //Compara se a pessoa digitou 'sair'. Se sim retorna 0 para o menu inicial e fecha o jogo.
		return 0;
	else if (!strcmp(entrada, "voltar") || retorno) //Compara se a pessoa digitou 'voltar'. Se sim retorna 1.
		return 1;
	
	FILE *jogoSalvo;
	jogoSalvo = fopen(entrada, "r"); //Abro o arquivo depois das validações
	if (jogoSalvo == NULL) { //Se não existe aparece uma mensagem de erro OU verifica se a pessoa não iniciou nenhum jogo e retorna o proprio menu.
		printf("\n             O arquivo "BG_RED("não")" existe ou você " BG_RED("não")" iniciou nenhum jogo.\n");
		return carregaJogo(matriz, contadorJogadas, continuarJogo);
	}
	else { //Se existir, coloca os valores da matriz do arquivo na matriz criada e retorna a função gameplay para começar o jogo.
		int tamanhoMatriz;
		fscanf(jogoSalvo, "%d", &tamanhoMatriz);
		for (int i = 0; i < tamanhoMatriz; i++) {
			for (int j = 0; j < tamanhoMatriz; j++) {
				fscanf(jogoSalvo, "%d", &matriz[i][j]);
			}
		}
		fscanf(jogoSalvo, "%d", contadorJogadas);
		return gameplay(matriz, contadorJogadas);
	}
	fclose(jogoSalvo); //Fecho o arquivo
}

int instrucoes(int *continuarJogo, int **matriz, int *contadorJogadas) { //Menu instruções de jogo
	printf("\n");
	printf("   .--------------------------------------------------------------------.\n");
	printf("   |                                                                    |\n");
	printf("   |                             ");printf(BG_BLUE(YELLOW(BOLD("  Resta 8  "))));printf("                            |\n");
	printf("   |                                                                    |\n");
	printf("   | - Para vencer é necessário deixar o tabuleiro novamente ordenadado.|\n");
	printf("   | - No tabuleiro digite o número da peça que deseja mover.           |\n");
	printf("   | - Digite 'salvar 'nomeaArquivo.txt'' para salvar o jogo atual.     |\n");
	printf("   | - Digite 'sair' para sair do jogo.                                 |\n");
	printf("   | - Digite 'voltar' para voltar ao menu inicial.                     |\n");
	printf("   | - Maior a dificuldade mais vezes o tabuleiro é embaralhado.        |\n");
	printf("   |                   Criado por: "BG_CYAN(BOLD("Lucas de Oliveira"))".                   |\n");
	printf("   |                                                                    |\n");
	printf("   |                              1 - Voltar                            |\n");
	printf("   |                                                                    |\n");
	printf("   .--------------------------------------------------------------------.\n");
	printf("                           Digite a opção desejada: ");
	return validaInstrucoes(continuarJogo, matriz, contadorJogadas); //Valida a entrada das instruções
}

