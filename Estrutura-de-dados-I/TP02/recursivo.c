#include <stdio.h>
#include <stdlib.h>
#include "recursivo.h"

void executaRecursao(int linha, int coluna) {
    Labirinto *labirinto = alocaLabirinto(linha, coluna); // Aloca o labirinto
    leLabirinto(labirinto, linha, coluna); // Le o labirinto
    Percurso *percurso = alocaPercurso(labirinto); // Aloca o percurso
    int *posicaoRato = achaRato(labirinto, percurso, linha, coluna); // Acha a posicao inicial do rato
    percurso->posicao[percurso->index].x = posicaoRato[0]; // Define a posição X incial do rato
    percurso->posicao[percurso->index].y = posicaoRato[1]; // Define a posição Y incial do rato
    acharSaidaRecursiva(labirinto, percurso, linha, coluna); // Acha a saida do rato, se existe
    imprimeLabirintoRecursivo(labirinto, percurso, linha, coluna); // Imprimi a saida de acordo
    free(posicaoRato); // Desaloca o vetor de inteiro da posicaoRato
    desalocaPercurso(percurso);          // Desaloca o struct percurso
    desalocaLabirinto(labirinto, linha); // Desaloca o struct labirinto
}

void acharSaidaRecursiva(Labirinto *labirinto, Percurso *percurso, int linha, int coluna) { // Funcao para achar a saida do rato

    // Condicional se nao existe um rato no labirinto
    if (percurso->verificaRato == -2)
        return;

    // Condicional se o rato ja esta na saida
    if ((percurso->posicao[percurso->index].x == linha - 2 && percurso->posicao[percurso->index].y == coluna - 1) && percurso->contadorTamanhoCaminho == 0) {
        percurso->verificaRato = -1;
        return;
    }

    // Variavel para verificar se ele pode ir para direita quando estiver na saida. 1 = Pode ir(TRUE), 0 = Nao pode ir(FALSE)
    int podeIrParaDireita = percurso->posicao[percurso->index].y + 1 < coluna ? 1 : 0;

    // Condicionais para verificar se tem caminho livre

    // DIREITA
    if (podeIrParaDireita) { // Condional que verifica se nao esta na saida. Assim nao verifica uma posicao na matriz inexistente
        if (labirinto->tabuleiro[percurso->posicao[percurso->index].x][percurso->posicao[percurso->index].y + 1] == ' ') {
            percurso->index++;                                                                                      // Soma um no index para salvar a posicao livre no vetor percurso
            percurso->contadorTamanhoCaminho++;                                                                     // Soma um no tamanho percorrido
            percurso->contSemSaida++;                                                                     // Soma um no tamanho do caminho sem saida percorrido
            percurso->posicao[percurso->index].x = percurso->posicao[percurso->index - 1].x;                        // Adiciona no vetor o valor X do percurso(x = x pois so muda a coluna)
            percurso->posicao[percurso->index].y = percurso->posicao[percurso->index - 1].y + 1;                    // Adiciona no vetor o valor X do percurso(y + 1 pois ele foi para a coluna da direita)
            labirinto->tabuleiro[percurso->posicao[percurso->index].x][percurso->posicao[percurso->index].y] = 'o'; // Coloca o . no caminho percorrido
            acharSaidaRecursiva(labirinto, percurso, linha, coluna);                                                // Chama novamente a funcao
        }
    }

    // BAIXO
    if (labirinto->tabuleiro[percurso->posicao[percurso->index].x + 1][percurso->posicao[percurso->index].y] == ' ') {
        percurso->index++;                                                                                      // Soma um no index para salvar a posicao livre no vetor percurso
        percurso->contadorTamanhoCaminho++;                                                                     // Soma um no tamanho percorrido
        percurso->contSemSaida++;                                                                     // Soma um no tamanho do caminho sem saida percorrido
        percurso->posicao[percurso->index].x = percurso->posicao[percurso->index - 1].x + 1;                    // Adiciona no vetor o valor X do percurso(x + 1 pois ele foi linha de baixo)
        percurso->posicao[percurso->index].y = percurso->posicao[percurso->index - 1].y;                        // Adiciona no vetor o valor X do percurso(j = j pois so muda a linha)
        labirinto->tabuleiro[percurso->posicao[percurso->index].x][percurso->posicao[percurso->index].y] = 'o'; // Coloca o . no caminho percorrido
        acharSaidaRecursiva(labirinto, percurso, linha, coluna);                                                // Chama novamente a funcao
    }

    // ESQUERDA
    if (labirinto->tabuleiro[percurso->posicao[percurso->index].x][percurso->posicao[percurso->index].y - 1] == ' ') {
        percurso->index++;                                                                                      // Soma um no index para salvar a posicao livre no vetor percurso
        percurso->contadorTamanhoCaminho++;                                                                     // Soma um no tamanho percorrido
        percurso->contSemSaida++;                                                                     // Soma um no tamanho do caminho sem saida percorrido
        percurso->posicao[percurso->index].x = percurso->posicao[percurso->index - 1].x;                        // Adiciona no vetor o valor X do percurso(x = x pois so muda a coluna)
        percurso->posicao[percurso->index].y = percurso->posicao[percurso->index - 1].y - 1;                    // Adiciona no vetor o valor X do percurso(y + 1 pois ele foi para a coluna da esquerda)
        labirinto->tabuleiro[percurso->posicao[percurso->index].x][percurso->posicao[percurso->index].y] = 'o'; // Coloca o . no caminho percorrido
        acharSaidaRecursiva(labirinto, percurso, linha, coluna);                                                // Chama novamente a funcao
    }

    // CIMA
    if (labirinto->tabuleiro[percurso->posicao[percurso->index].x - 1][percurso->posicao[percurso->index].y] == ' ') {
        percurso->index++;                                                                                      // Soma um no index para salvar a posicao livre no vetor percurso
        percurso->contadorTamanhoCaminho++;                                                                     // Soma um no tamanho percorrido
        percurso->contSemSaida++;                                                                     // Soma um no tamanho do caminho sem saida percorrido
        percurso->posicao[percurso->index].x = percurso->posicao[percurso->index - 1].x - 1;                    // Adiciona no vetor o valor X do percurso(x - 1 pois ele foi linha de cima)
        percurso->posicao[percurso->index].y = percurso->posicao[percurso->index - 1].y;                        // Adiciona no vetor o valor X do percurso(j = j pois so muda a linha)
        labirinto->tabuleiro[percurso->posicao[percurso->index].x][percurso->posicao[percurso->index].y] = 'o'; // Coloca o . no caminho percorrido
        acharSaidaRecursiva(labirinto, percurso, linha, coluna);                                                // Chama novamente a funcao
    }

    // ACHOU SAIDA
    else if (percurso->posicao[percurso->index].x == linha - 2 && percurso->posicao[percurso->index].y == coluna - 1) {

        // Verifica se a saida que ele achou e menor.(A primeira verificao vai dar true no if pois o menorCaminho e o piorCaso + 1)
        if (percurso->contadorTamanhoCaminho < percurso->menorCaminho)
        {
            free(percurso->menorCaminhoX);                                                 // Libera o vetor menor caminho X
            free(percurso->menorCaminhoY);                                                 // Libera o vetor menor caminho Y
            percurso->menorCaminho = percurso->contadorTamanhoCaminho;                     // Agora o menor caminho e o tamanho do caminho percorrido
            percurso->menorCaminhoX = (int *)malloc(sizeof(int) * percurso->menorCaminho); // Aloca a posicao menorCaminhoX com o tamanho do menor caminho
            percurso->menorCaminhoY = (int *)malloc(sizeof(int) * percurso->menorCaminho); // Aloca a posicao menorCaminhoY com o tamanho do menor caminho

            for (int k = 0, l = 1; k < percurso->menorCaminho; k++, l++)
            { // Adiciona nos vetores menor caminho X/Y a posicao que ele percorreu para achar o menor caminho
                percurso->menorCaminhoX[k] = percurso->posicao[l].x;
                percurso->menorCaminhoY[k] = percurso->posicao[l].y;
            }
        }
        percurso->quantidadeAchados++; // Condicional para confirmar que achou um caminho
    }

    // Encontrou um caminho sem saida. Agora ele vai voltar as posicoes que ele andou
    if (percurso->index > 0) {
        percurso->index--; // Tira um do index para ir voltando
        percurso->contadorTamanhoCaminho--; // Tira um do contador tamanho caminho
    }
}

// Funcao para imprimir o labirinto
void imprimeLabirintoRecursivo(Labirinto *labirinto, Percurso *percurso, int linha, int coluna) {
    // Verificacao para quando o rato ja esta na saida do tabuleiro digitado pelo usuario
    if (percurso->verificaRato == -2)
        printf("O rato nao esta no labirinto.\n");

    // Verificacao para quando o rato ja esta na saida do tabuleiro digitado pelo usuario
    else if (percurso->verificaRato == -1)
        printf("O rato ja esta na saída.\n");

    // Verificacao quando nao achou nenhum caminho
    if (percurso->quantidadeAchados == 0) {
        printf("%d\n", percurso->contSemSaida);
        for (int i = 0; i < linha; i++) {
            for (int j = 0; j < coluna; j++) {
                printf("%c", labirinto->tabuleiro[i][j]);
            }
            printf("\n");
        }
    }
    // Como achou caminho, agora ele vai imprimir de acordo com o que o usuario digitou
    else{
        printf("%d\n", percurso->menorCaminho);
        // Adiciona os . no caminho que o rato percorreu
        for (int i = 0; i < percurso->menorCaminho; i++)
            labirinto->tabuleiro[percurso->menorCaminhoX[i]][percurso->menorCaminhoY[i]] = '.';
            
        // Adiociona o M na posicao inicial do rato
        labirinto->tabuleiro[percurso->posicao[0].x][percurso->posicao[0].y] = 'M';

        for (int i = 0; i < linha; i++) {
            for (int j = 0; j < coluna; j++) {
                if (labirinto->tabuleiro[i][j] == 'o')
                    labirinto->tabuleiro[i][j] = ' ';
                else if (labirinto->tabuleiro[i][j] == '.')
                    labirinto->tabuleiro[i][j] = 'o';
                printf("%c", labirinto->tabuleiro[i][j]);
            }
            printf("\n");
        }
    }
}