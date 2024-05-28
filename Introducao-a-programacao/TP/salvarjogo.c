/*
Nome: Lucas de Oliveira Barboza
Matrícula: 21.2.4173
Turma: 31
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "salvarjogo.h"
#include "estilizacao.h"
#include "validacao.h"

int salvarJogo(char *entrada, int **matriz, int *contadorJogadas) { //Função para salvar um jogo
	int posicaoPonto = -1, verificaTxt = 0; //Inteiro para salvar a posicao do PONTO. Inteiro contador para verificar se a pessoa digitou .txt
	for (int i = 0; i < strlen(entrada); i++) { //Acha a posição do último PONTO digitado
		if (entrada[i] == '.') posicaoPonto = i;
	}
	if (posicaoPonto == -1) { //Se não existir nenhum ponto. Mensagem de erro
		printf("\n                        Nome do arquivo " BG_RED("inválido")"\n");
		return -3;
	}
	char txt[] = ".txt";
	for (int i = posicaoPonto, j = 0; i < strlen(entrada); i++, j++) { //Verifica se a pessoa digitou .txt
		if (entrada[i] == txt[j]) verificaTxt++;
	}
	if (verificaTxt != 4) { //Se a pessoa não digitou .txt. Aparece uma mensagem de erro
		printf("\n                        Extensão do arquivo " BG_RED("inválido")"\n");
		return -3;
	}
	int contadorNome = 0;
	for (int i = 7; i < strlen(entrada); i++) { //Contar o tamanho do nome que o usuário digitou
		contadorNome++;
	}
	if (contadorNome == 4) { //Se a pessoa digitar um nome vazio retorna uma mensagem de erro
		printf("\n                       Nome do arquivo " BG_RED("inválido")"\n");
		return -3;
	}
	char *nome;
	nome = malloc(contadorNome * sizeof(char)); //Cria um char do tamanho do nome
	for (int i = 7, j = 0; i < strlen(entrada); i++, j++) { //Coloca o nome do arquivo no char nome
		nome[j] = entrada[i];
		if (i == strlen(entrada) - 1) nome[j + 1] = '\0'; //Coloca '\0' depois do último char
	}
	//ARQUIVO
	FILE *salvar;
	salvar = fopen(nome, "r+"); //Abre o arquivo
	if (fopen(nome, "r+") == NULL) { //Se não existir o arquivo, cria o arquivo
		salvar = fopen(nome, "w");
		fprintf(salvar, "%d\n", tam); //Salva o tamanho da matriz
		for (int i = 0; i < tam; i++) {
			for (int j = 0; j < tam; j++) {//Salva os valores da matriz no arquivo
				if (j == 2) fprintf(salvar,"%d", matriz[i][j]); 
				else fprintf(salvar,"%d ", matriz[i][j]);
			}
			fprintf(salvar,"\n");
		}
		fprintf(salvar, "%d\n", *contadorJogadas); //Salva a quantidade de jogadas na ultima linha do arquivo
		printf("\n                         O jogo \"%s\" "BG_GREEN("salvo com sucesso!"), nome); //Mensagem que salvou corretamente
	}
	else { //Verifica se o arquivo já existe
		printf("\n                O arquivo \"%s\" já existe. Deseja sobrescrever?", nome); //Pergunta o usuário se ele quer sobrescrever o arquivo
		printf("\n                             1 - Sim | 2 - Não : ");
		int retorno = validaArquivoExistente(); //Valida a entrada
		if (retorno == 1) { //Sobrescreve o arquivo
			salvar = fopen(nome, "w");
			fprintf(salvar, "%d\n", tam);
			for (int i = 0; i < tam; i++) {
				for (int j = 0; j < tam; j++) {
					if (j == 2) fprintf(salvar,"%d", matriz[i][j]);
					else fprintf(salvar,"%d ", matriz[i][j]);
				}
				fprintf(salvar,"\n");
			}
			fprintf(salvar, "%d\n", *contadorJogadas);
			printf("                 O jogo \"%s\" foi "BG_GREEN("sobrescrito com sucesso!"), nome);
		}
		else if (retorno == 2) printf("\n                       Salve novamente com um nome diferente.\n"); //Pede pro usuário digitar um nome diferente
		else {
			printf("\n                         "BG_RED("Comando inválido.")" Digite novamente: "); //Mensagem de erro se a pessoa digitar uma entrada inválida
			return salvarJogo(entrada, matriz, contadorJogadas);
		}  
	}
	fclose(salvar); //Libera salvar
	free(nome); //Libera nome
	return -3;
}

