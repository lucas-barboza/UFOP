/*
Nome: Lucas de Oliveira Barboza
Matrícula: 21.2.4173
Turma: 31
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "validacao.h"
#include "salvarjogo.h"
#include "estilizacao.h"
#include "menus.h"

char *minusculo(char *entrada) { //Função que transforma a entrada MAIÚSCULA em MINÚSCULA
	int i = 0;
	while (entrada[i] != '\0') {
		entrada[i] = tolower(entrada[i]); //A função tolower() é da biblioteca <ctype.h> que faz a transformação
		i++;
	}
	entrada[i] = '\0';
	return entrada;
}

int validaMenu(int *continuarJogo, int **matriz, int *contadorJogadas) { //Função que faz a validação da entrada do MENU
	char entradaMenu[1000];
	fgets(entradaMenu, 1000, stdin);
	entradaMenu[strcspn(entradaMenu, "\n")] = '\0'; //Troca o '\n' para '\0'
	strcpy(entradaMenu, minusculo(entradaMenu)); //Faz a transformação da entrada MAIÚSCULA em MINÚSCULA
	char voltar[] = "voltar";
	char sair[] = "sair";
	char salvar[] = "salvar ", cont = 0;
	for (int i = 0; i < strlen(salvar); i++) {
		if (salvar[i] == entradaMenu[i]) cont++;
	}
	if (*continuarJogo && cont == 7) { //O usuário digitou salvar e retorna a função pra salvar.
		return salvarJogo(entradaMenu, matriz, contadorJogadas);
	}
	else if (!strcmp(entradaMenu, "0") || !strcmp(entradaMenu, sair)) return 0; //O usuário digitou 0 ou 'sair'
	else if (!strcmp(entradaMenu, "1")) return 1; //O usuário digitou 1
	else if (!strcmp(entradaMenu, "2")) return 2; //O usuário digitou 2
	else if (!strcmp(entradaMenu, "3")) return 3; //O usuário digitou 3
	else if (!strcmp(entradaMenu, "4")) return 4; //O usuário digitou 4
	else if (!strcmp(entradaMenu, voltar)) return 5; //O usuário digitou 'voltar'
	else if (!*continuarJogo) return 2; //Usuário digitou salvar mas não existe um jogo ativo
	else return 6; //Retorna o default se a pessoa não digitou um comando válido
}

int validaDificuldade(int *continuarJogo, int **matriz, int *contadorJogadas) { //Função que faz a validação da entrada do MENU DIFICULDADE
	char entradaDificuldade[1000];
	fgets(entradaDificuldade, 1000, stdin);
	entradaDificuldade[strcspn(entradaDificuldade, "\n")] = '\0'; //Troca o '\n' para '\0'
	strcpy(entradaDificuldade, minusculo(entradaDificuldade)); //Faz a transformação da entrada MAIÚSCULA em MINÚSCULA
	char voltar[] = "voltar";
	char sair[] = "sair";
	char salvar[] = "salvar ", cont = 0;
	for (int i = 0; i < strlen(salvar); i++) {
		if (salvar[i] == entradaDificuldade[i]) cont++;
	}
	if (*continuarJogo && cont == 7) {
		return salvarJogo(entradaDificuldade, matriz, contadorJogadas); //O usuário digitou salvar e retorna a função pra salvar.
	}
	else if (!strcmp(entradaDificuldade, sair)) return 0; //O usuário digitou 'sair'
	else if (!strcmp(entradaDificuldade, "1")) return 1; //O usuário digitou 1
	else if (!strcmp(entradaDificuldade, "2")) return 2; //O usuário digitou 2
	else if (!strcmp(entradaDificuldade, "3")) return 3; //O usuário digitou 3
	else if (!strcmp(entradaDificuldade, voltar)) return 4; //O usuário digitou 'voltar'
	else if (!*continuarJogo) return -1; //Usuário digitou salvar mas não existe um jogo ativo
	else return 5; //Retorna o default se a pessoa não digitou um comando válido
}

int validaInstrucoes(int *continuarJogo, int **matriz, int *contadorJogadas) { //Função que faz a validação da entrada do MENU INSTRUÇÕES
	char entradaInstrucoes[1000];
	fgets(entradaInstrucoes, 1000, stdin);
	entradaInstrucoes[strcspn(entradaInstrucoes, "\n")] = '\0'; //Troca o '\n' para '\0'
	strcpy(entradaInstrucoes, minusculo(entradaInstrucoes)); //Faz a transformação da entrada MAIÚSCULA em MINÚSCULA
	char voltar[] = "voltar";
	char sair[] = "sair";
	char salvar[] = "salvar ", cont = 0;
	for (int i = 0; i < strlen(salvar); i++) {
		if (salvar[i] == entradaInstrucoes[i]) cont++;
	}
	if (*continuarJogo && cont == 7) {
		salvarJogo(entradaInstrucoes, matriz, contadorJogadas); //O usuário digitou salvar e retorna a função pra salvar.
		return instrucoes(continuarJogo, matriz, contadorJogadas);
	}
	else if (!strcmp(entradaInstrucoes, "1") || !strcmp(entradaInstrucoes, voltar)) return 1; //O usuário digitou 'voltar' ou 1
	else if (!strcmp(entradaInstrucoes, sair)) return 0; //O usuário digitou 'sair'
	else if (!*continuarJogo) { //Usuário digitou salvar mas não existe um jogo ativo
		printf("\n                        Você " BG_RED("não")" iniciou nenhum jogo.");
		return instrucoes(continuarJogo, matriz, contadorJogadas);
	}
	else { //Usuário digitou um comando inválido
		printf("\n                               "BG_RED("Comando inválido.")"\n");
		return instrucoes(continuarJogo, matriz, contadorJogadas);
	}
}

int validaGameplay(int **matriz, int *contadorJogadas) { //Função que faz a validação da entrada da GAMEPLAY
	char entradaGamePlay[1000];
	fgets(entradaGamePlay, 1000, stdin);
	entradaGamePlay[strcspn(entradaGamePlay, "\n")] = '\0'; //Troca o '\n' para '\0'
	strcpy(entradaGamePlay, minusculo(entradaGamePlay)); //Faz a transformação da entrada MAIÚSCULA em MINÚSCULA
	int cont = 0;
	char salvar[] = "salvar ";
	for (int i = 0; i < strlen(salvar); i++) {
		if (salvar[i] == entradaGamePlay[i]) cont++;
	}
	if (!strcmp(entradaGamePlay, "voltar")) return -1; //O usuário digitou 'voltar'
	else if (!strcmp(entradaGamePlay, "sair")) return -2; //O usuário digitou 'sair'
	else if (cont == 7) { 
		return salvarJogo(entradaGamePlay, matriz, contadorJogadas); //O usuário digitou salvar e retorna a função pra salvar.
	}
	else if (!strcmp(entradaGamePlay, "1") || !strcmp(entradaGamePlay, "2") || !strcmp(entradaGamePlay, "3") || !strcmp(entradaGamePlay, "4") || !strcmp(entradaGamePlay, "5") || !strcmp(entradaGamePlay, "6") || !strcmp(entradaGamePlay, "7") || !strcmp(entradaGamePlay, "8")) return atoi(entradaGamePlay); //Usuário digitou uma peça que existe no tabuleiro
	else {
		return -4; //Usuário digitou um comando inválido
	}
}

int validaArquivoExistente() { //Função que faz a validação da entrada do arquivoExistente
	char entradaArquivo[1000];
	fgets(entradaArquivo, 1000, stdin);
	entradaArquivo[strcspn(entradaArquivo, "\n")] = '\0'; //Troca o '\n' para '\0'
	if (!strcmp(entradaArquivo, "1")) return 1; //O usuário digitou 1
	else if (!strcmp(entradaArquivo, "2")) return 2; //O usuário digitou 2
	else return 3; //Usuário digitou um comando inválido
}

int **ordenaMatriz(int **matriz) { //Função que ordena a matriz
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
