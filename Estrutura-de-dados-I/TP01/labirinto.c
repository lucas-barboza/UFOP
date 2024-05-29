#include "labirinto.h"
#include <stdio.h>
#include <stdlib.h>

struct labirinto { // Cria o struct labirinto
  char** tabuleiro; // Aqui o tabuleiro(labirinto)
  int piorCaso; // Variavel para atribuir o pior caso(tamanho do caminho de saida)
};

struct posicao { // Cria o struct posicao
  int x, y;
};

struct percurso { // Cria o struct percurso
  Posicao* posicao;
  int contadorTamanhoCaminho, index, menorCaminho, *menorCaminhoX, *menorCaminhoY, quantidadeAchados, verificaRato;
};

void leTamanho(int* linha, int* coluna, char* escolha) { // Funcao que le o tamanho do labirinto e a escolha de impressao
  scanf("%d %d %c", linha, coluna, escolha);
}

Labirinto* alocaLabirinto(int linha, int coluna) { // Funcao para alocar o labirinto de acordo com o tamanho que o usuario digitou
  Labirinto* labirinto = (Labirinto*) malloc(sizeof(Labirinto)); // Aloca o struct labirinto
  labirinto->tabuleiro = (char**) malloc(sizeof(char*) * linha); // Aloca as linhas do tabuleiro
  for (int i = 0; i < linha; i++) {
    labirinto->tabuleiro[i] = (char*) malloc(sizeof(char) * coluna); // Aloca as colunas do tabuleiro
  }
  labirinto->piorCaso = 0; // Inicializa o pior caso
  return labirinto; // Retorna o labirinto alocado
}

Percurso* alocaPercurso(Labirinto* labirinto) { // Funcao para alocar o percurso
  Percurso* percurso = (Percurso*) malloc(sizeof(Percurso)); // Aloca o struct percurso
  percurso->posicao = (Posicao*) malloc(sizeof(Posicao) * (labirinto->piorCaso + 1)); // Aloca o vetor de struct posicao. O tamanho de vetor e +1 pois no vetor vai ter a posicao inicial
  percurso->menorCaminhoX = malloc(sizeof(int) * (labirinto->piorCaso + 1)); // Aloca o vetor do menor caminho X. O tamanho inicial e o pior caso +1
  percurso->menorCaminhoY = malloc(sizeof(int) * (labirinto->piorCaso + 1)); // Aloca o vetor do menor caminho Y. O tamanho inicial e o pior caso +1
  percurso->contadorTamanhoCaminho = 0; // Contador do tamanho do caminho atual que esta fazendo
  percurso->index = 0; // Index do vetor posicao
  percurso->quantidadeAchados = 0; // Para verificar se encontrou algum caminho
  percurso->menorCaminho = labirinto->piorCaso + 1; // Menor caminho inicializa com o piorCaso
  return percurso; // Retorna o percurso alocado
}


void leLabirinto(Labirinto* labirinto, int linha, int coluna) { // Funcao que le o labirinto
  int c;
  while ((c = getc(stdin)) != EOF && c != '\n');  // Descarta o restante da linha
  for (int i = 0; i < linha; i++) {
    for (int j = 0; j < coluna; j++) {
      c = getc(stdin);
      if (c != '\n') {  // Verifica se não é uma quebra de linha
        labirinto->tabuleiro[i][j] = c;
        if (labirinto->tabuleiro[i][j] == ' ') labirinto->piorCaso++; // Verifica as os caminhos possiveis e soma no pior caso
      } else {
        j--;  // Decrementa o índice para repetir a posição
      }
    }
    while ((c = getc(stdin)) != EOF && c != '\n');  // Descarta o restante da linha
  }
}

void achaRato(Labirinto* labirinto, Percurso* percurso, int linha, int coluna) { // Funcao para achar a posicao do rato
  percurso->verificaRato = -2; // Inicializa que o rato nao esta no labirinto
  for (int i = 0; i < linha; i++) {
    for (int j = 0; j < coluna; j++) {
      if (labirinto->tabuleiro[i][j] == 'M') {
        percurso->posicao[0].x = i; // Salva a posicao X do rato no index 0 do vetor posicao
        percurso->posicao[0].y = j; // Salva a posicao Y do rato no index 0 do vetor posicao
        percurso->verificaRato = 0; // Sinaliza que o rato esta no labirinto
      }
    }
  }
}

void acharSaida(Labirinto* labirinto, Percurso* percurso, int linha, int coluna) { // Funcao para achar a saida do rato

  // Condicional se nao existe um rato no labirinto
  if (percurso->verificaRato == -2) return;

  // Condicional se o rato ja esta na saida
  if ((percurso->posicao[percurso->index].x == linha - 2 && percurso->posicao[percurso->index].y == coluna - 1) && percurso->contadorTamanhoCaminho == 0) {
    percurso->verificaRato = -1;
    return;
  }

  // Variavel para verificar se ele pode ir para direita quando estiver na saida. 1 = Pode ir(TRUE), 0 = Nao pode ir(FALSE)
  int podeIrParaDireita = percurso->posicao[percurso->index].y + 1 < coluna ? 1 : 0;

  // Condicionais para verificar se tem caminho livre
      
  // CIMA
  if (labirinto->tabuleiro[percurso->posicao[percurso->index].x - 1][percurso->posicao[percurso->index].y] == ' ') {
      percurso->index++; // Soma um no index para salvar a posicao livre no vetor percurso
      percurso->contadorTamanhoCaminho++; // Soma um no tamanho percorrido
      percurso->posicao[percurso->index].x = percurso->posicao[percurso->index - 1].x - 1; // Adiciona no vetor o valor X do percurso(x - 1 pois ele foi linha de cima)
      percurso->posicao[percurso->index].y = percurso->posicao[percurso->index - 1].y; // Adiciona no vetor o valor X do percurso(j = j pois so muda a linha)
      labirinto->tabuleiro[percurso->posicao[percurso->index].x][percurso->posicao[percurso->index].y] = '.'; // Coloca o . no caminho percorrido
      acharSaida(labirinto, percurso, linha, coluna); // Chama novamente a funcao
  }

  // DIREITA
  if (podeIrParaDireita) { // Condional que verifica se nao esta na saida. Assim nao verifica uma posicao na matriz inexistente
    if (labirinto->tabuleiro[percurso->posicao[percurso->index].x][percurso->posicao[percurso->index].y + 1] == ' ') {
    percurso->index++; // Soma um no index para salvar a posicao livre no vetor percurso
    percurso->contadorTamanhoCaminho++; // Soma um no tamanho percorrido
    percurso->posicao[percurso->index].x = percurso->posicao[percurso->index - 1].x; // Adiciona no vetor o valor X do percurso(x = x pois so muda a coluna)
    percurso->posicao[percurso->index].y = percurso->posicao[percurso->index - 1].y + 1; // Adiciona no vetor o valor X do percurso(y + 1 pois ele foi para a coluna da direita)
    labirinto->tabuleiro[percurso->posicao[percurso->index].x][percurso->posicao[percurso->index].y] = '.'; // Coloca o . no caminho percorrido
    acharSaida(labirinto, percurso, linha, coluna); // Chama novamente a funcao
    }
  }

  // BAIXO
  if (labirinto->tabuleiro[percurso->posicao[percurso->index].x + 1][percurso->posicao[percurso->index].y] == ' ') {
    percurso->index++; // Soma um no index para salvar a posicao livre no vetor percurso
    percurso->contadorTamanhoCaminho++; // Soma um no tamanho percorrido
    percurso->posicao[percurso->index].x = percurso->posicao[percurso->index - 1].x + 1; // Adiciona no vetor o valor X do percurso(x + 1 pois ele foi linha de baixo)
    percurso->posicao[percurso->index].y = percurso->posicao[percurso->index - 1].y; // Adiciona no vetor o valor X do percurso(j = j pois so muda a linha)
    labirinto->tabuleiro[percurso->posicao[percurso->index].x][percurso->posicao[percurso->index].y] = '.'; // Coloca o . no caminho percorrido
    acharSaida(labirinto, percurso, linha, coluna); // Chama novamente a funcao
  }
    
  // ESQUERDA
  if (labirinto->tabuleiro[percurso->posicao[percurso->index].x][percurso->posicao[percurso->index].y - 1] == ' ') {
    percurso->index++; // Soma um no index para salvar a posicao livre no vetor percurso
    percurso->contadorTamanhoCaminho++; // Soma um no tamanho percorrido
    percurso->posicao[percurso->index].x = percurso->posicao[percurso->index - 1].x; // Adiciona no vetor o valor X do percurso(x = x pois so muda a coluna)
    percurso->posicao[percurso->index].y = percurso->posicao[percurso->index - 1].y - 1; // Adiciona no vetor o valor X do percurso(y + 1 pois ele foi para a coluna da esquerda)
    labirinto->tabuleiro[percurso->posicao[percurso->index].x][percurso->posicao[percurso->index].y] = '.'; // Coloca o . no caminho percorrido
    acharSaida(labirinto, percurso, linha, coluna); // Chama novamente a funcao
  }

  //ACHOU SAIDA
  else if (percurso->posicao[percurso->index].x == linha - 2 && percurso->posicao[percurso->index].y == coluna - 1) {

    // Verifica se a saida que ele achou e menor.(A primeira verificao vai dar true no if pois o menorCaminho e o piorCaso + 1)
    if (percurso->contadorTamanhoCaminho < percurso->menorCaminho) {
      free(percurso->menorCaminhoX); // Libera o vetor menor caminho X
      free(percurso->menorCaminhoY); // Libera o vetor menor caminho Y
      percurso->menorCaminho = percurso->contadorTamanhoCaminho; // Agora o menor caminho e o tamanho do caminho percorrido
      percurso->menorCaminhoX = (int*) malloc(sizeof(int) * percurso->menorCaminho); // Aloca a posicao menorCaminhoX com o tamanho do menor caminho
      percurso->menorCaminhoY = (int*) malloc(sizeof(int) * percurso->menorCaminho); // Aloca a posicao menorCaminhoY com o tamanho do menor caminho

      for (int k = 0, l = 1; k < percurso->menorCaminho; k++, l++) { // Adiciona nos vetores menor caminho X/Y a posicao que ele percorreu para achar o menor caminho
        percurso->menorCaminhoX[k] = percurso->posicao[l].x;
        percurso->menorCaminhoY[k] = percurso->posicao[l].y;
      }
    }
  
    percurso->quantidadeAchados++; // Condicional para confirmar que achou um caminho
  }

  // Encontrou um caminho sem saida. Agora ele vai voltar tirando '.' que colocou e trocando por ' '
  if (percurso->index > 0) {
    percurso->contadorTamanhoCaminho--; // Tira um do tamanho do camiho pois esta voltando
    labirinto->tabuleiro[percurso->posicao[percurso->index].x][percurso->posicao[percurso->index].y] = ' ';
    percurso->posicao[percurso->index].x = 0; // Troca o valor do caminho por 0
    percurso->posicao[percurso->index].y = 0; // Troca o valor do caminho por 0
    percurso->index--; // Tira um do index para ir voltando
  }
}

// Funcao para imprimir o labirinto
void imprimePercursoNoLabirinto(Labirinto* labirinto, Percurso* percurso, int linha, int coluna, char* escolha) {
  // Verificacao para quando o rato ja esta na saida do tabuleiro digitado pelo usuario
  if (percurso->verificaRato == -2)
    printf("O rato nao esta no labirinto.\n");

  // Verificacao para quando o rato ja esta na saida do tabuleiro digitado pelo usuario
  else if (percurso->verificaRato == -1)
    printf("O rato ja esta na saída.\n");

  // Verificacao quando nao achou nenhum caminho
  else if (percurso->quantidadeAchados == 0) {
    printf("EPIC FAIL!\n");

  // Como achou caminho, agora ele vai imprimir de acordo com o que o usuario digitou
  } else {

    printf("%d\n", percurso->menorCaminho);

    if (*escolha == 'c') {
      for (int i = 0; i < percurso->menorCaminho; i++) {
        printf("%d, %d\n", percurso->menorCaminhoX[i], percurso->menorCaminhoY[i]);
      }
    }

    else if (*escolha == 'p') {

      for(int i = 0; i < percurso->menorCaminho; i++) {
        labirinto->tabuleiro[percurso->menorCaminhoX[i]][percurso->menorCaminhoY[i]] = '.';
      }

      labirinto->tabuleiro[percurso->posicao[0].x][percurso->posicao[0].y] = 'M';

      for (int i = 0; i < linha; i++) {
        for(int j = 0; j < coluna; j++) {
          printf("%c", labirinto->tabuleiro[i][j]);
        }
        printf("\n");
      }

    }
  }
}

// Funcao apra desalocar o vetor de sctruct posicao, vetores menorCaminhoX/Y e o struct percurso
void desalocaPercurso(Percurso* percurso) {
  free(percurso->posicao);
  free(percurso->menorCaminhoX);
  free(percurso->menorCaminhoY);
  free(percurso);
}

// Funcao apra desalocar o tabuleiro e o struct labirinto
void desalocaLabirinto(Labirinto* labirinto, int linha) {
  for (int i = 0; i < linha; i++) {
    free(labirinto->tabuleiro[i]);
  }
  free(labirinto->tabuleiro);
  free(labirinto);
}