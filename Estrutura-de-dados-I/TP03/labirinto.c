#include "labirinto.h"
#include <stdio.h>
#include <stdlib.h>

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

No* iniciaArvore(Posicao posicao) {
  No* novoNo = (No*) malloc(sizeof(No));
  novoNo->posicao.x = posicao.x;
  novoNo->posicao.y = posicao.y;
  novoNo->direita = NULL;
  novoNo->baixo = NULL;
  novoNo->esquerda = NULL;
  novoNo->cima = NULL;
  novoNo->pai = NULL;
  novoNo->tamanho = 0;
  novoNo->verificaSaida = 0;
  return novoNo;
}

No* criaNo(Posicao posicao, No* pai) {
  No* novoNo = (No*) malloc(sizeof(No));
  novoNo->posicao.x = posicao.x;
  novoNo->posicao.y = posicao.y;
  novoNo->direita = NULL;
  novoNo->baixo = NULL;
  novoNo->esquerda = NULL;
  novoNo->cima = NULL;
  novoNo->pai = pai;
  novoNo->tamanho = pai->tamanho + 1;
  novoNo->verificaSaida = 0;
  return novoNo;
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

void acharSaida(Labirinto* labirinto, Percurso* percurso, int linha, int coluna, No* no) { // Funcao para achar a saida do rato

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
  // DIREITA
  if (podeIrParaDireita) { // Condional que verifica se nao esta na saida. Assim nao verifica uma posicao na matriz inexistente
    if (labirinto->tabuleiro[percurso->posicao[percurso->index].x][percurso->posicao[percurso->index].y + 1] == ' ') {
      percurso->index++; // Soma um no index para salvar a posicao livre no vetor percurso
      percurso->contadorTamanhoCaminho++; // Soma um no tamanho percorrido
      percurso->posicao[percurso->index].x = percurso->posicao[percurso->index - 1].x; // Adiciona no vetor o valor X do percurso(x = x pois so muda a coluna)
      percurso->posicao[percurso->index].y = percurso->posicao[percurso->index - 1].y + 1; // Adiciona no vetor o valor X do percurso(y + 1 pois ele foi para a coluna da direita)
      no->direita = criaNo(percurso->posicao[percurso->index], no);
      labirinto->tabuleiro[percurso->posicao[percurso->index].x][percurso->posicao[percurso->index].y] = '.'; // Coloca o . no caminho percorrido
      acharSaida(labirinto, percurso, linha, coluna, no->direita); // Chama novamente a funcao
    }
  }

  // BAIXO
  if (labirinto->tabuleiro[percurso->posicao[percurso->index].x + 1][percurso->posicao[percurso->index].y] == ' ') {
    percurso->index++; // Soma um no index para salvar a posicao livre no vetor percurso
    percurso->contadorTamanhoCaminho++; // Soma um no tamanho percorrido
    percurso->posicao[percurso->index].x = percurso->posicao[percurso->index - 1].x + 1; // Adiciona no vetor o valor X do percurso(x + 1 pois ele foi linha de baixo)
    percurso->posicao[percurso->index].y = percurso->posicao[percurso->index - 1].y; // Adiciona no vetor o valor X do percurso(j = j pois so muda a linha)
    no->baixo = criaNo(percurso->posicao[percurso->index], no);
    labirinto->tabuleiro[percurso->posicao[percurso->index].x][percurso->posicao[percurso->index].y] = '.'; // Coloca o . no caminho percorrido
    acharSaida(labirinto, percurso, linha, coluna, no->baixo); // Chama novamente a funcao
  } 

  // CIMA
  if (labirinto->tabuleiro[percurso->posicao[percurso->index].x - 1][percurso->posicao[percurso->index].y] == ' ') {
      percurso->index++; // Soma um no index para salvar a posicao livre no vetor percurso
      percurso->contadorTamanhoCaminho++; // Soma um no tamanho percorrido
      percurso->posicao[percurso->index].x = percurso->posicao[percurso->index - 1].x - 1; // Adiciona no vetor o valor X do percurso(x - 1 pois ele foi linha de cima)
      percurso->posicao[percurso->index].y = percurso->posicao[percurso->index - 1].y; // Adiciona no vetor o valor X do percurso(j = j pois so muda a linha)
      no->cima = criaNo(percurso->posicao[percurso->index], no);
      labirinto->tabuleiro[percurso->posicao[percurso->index].x][percurso->posicao[percurso->index].y] = '.'; // Coloca o . no caminho percorrido
      acharSaida(labirinto, percurso, linha, coluna, no->cima); // Chama novamente a funcao
  }

  // ESQUERDA
  if (labirinto->tabuleiro[percurso->posicao[percurso->index].x][percurso->posicao[percurso->index].y - 1] == ' ') {
    percurso->index++; // Soma um no index para salvar a posicao livre no vetor percurso
    percurso->contadorTamanhoCaminho++; // Soma um no tamanho percorrido
    percurso->posicao[percurso->index].x = percurso->posicao[percurso->index - 1].x; // Adiciona no vetor o valor X do percurso(x = x pois so muda a coluna)
    percurso->posicao[percurso->index].y = percurso->posicao[percurso->index - 1].y - 1; // Adiciona no vetor o valor X do percurso(y + 1 pois ele foi para a coluna da esquerda)
    no->esquerda = criaNo(percurso->posicao[percurso->index], no);
    labirinto->tabuleiro[percurso->posicao[percurso->index].x][percurso->posicao[percurso->index].y] = '.'; // Coloca o . no caminho percorrido
    acharSaida(labirinto, percurso, linha, coluna, no->esquerda); // Chama novamente a funcao
  }


  //ACHOU SAIDA
  else if (percurso->posicao[percurso->index].x == linha - 2 && percurso->posicao[percurso->index].y == coluna - 1) {
    no->verificaSaida = 1;
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

Fila* criaFila() {
  Fila* fila = (Fila*) malloc(sizeof(Fila));
  fila->inicio = NULL;
  fila->fim = NULL;
  fila->tamanho = 0;
  return fila;
}

void enfileirar(Fila* fila, No* no) {
  Celula *aux = (Celula*) malloc(sizeof(Celula));
  aux->no = no;
  
  if (fila->inicio == NULL)
    fila->inicio = aux;

  aux->prox = NULL;

  if (fila->fim != NULL)
    fila->fim->prox = aux;

  fila->fim = aux;
  fila->tamanho++;
}

No* desenfileira(Fila* fila) {
  if (fila->inicio == NULL)
    return NULL;
  
  Celula* aux = fila->inicio;

  if (fila->inicio == fila->fim)
    fila->fim = NULL;
  fila->inicio = fila->inicio->prox;
  No* noAux = aux->no;
  free(aux);
  fila->tamanho--;
  return noAux;
}

void imprimeFila(Fila* fila) {
  Celula *aux = fila->inicio;
  printf("\n");
  while(aux != NULL) {
    printf("##%d, %d##", aux->no->posicao.x,aux->no->posicao.y);
    aux = aux->prox;
  }
  printf("\n");
}

void imprimiArvore(No* no, int i, Fila* fila) {
  if (no == NULL)
    return;
  Posicao posicao;
  posicao.x = -1;
  posicao.y = -1;
  No* marcadorNivel = criaNo(posicao, no);

  enfileirar(fila, marcadorNivel);
  enfileirar(fila, no);
  while (fila->tamanho != 1) {
    No* noAtual = desenfileira(fila);

    if (noAtual->posicao.x == -1 && noAtual->posicao.y == -1) {
      enfileirar(fila, marcadorNivel);
      i++;
      printf("\nNivel %d:\n", i);
    } 
    
    else {
      printf(" (%d, %d)", noAtual->posicao.x, noAtual->posicao.y);

      if (noAtual->baixo != NULL) {
        enfileirar(fila, noAtual->baixo);
      }
      if (noAtual->cima != NULL) {
        enfileirar(fila, noAtual->cima);
      }
      if (noAtual->direita != NULL) {
        enfileirar(fila, noAtual->direita);
      }
      if (noAtual->esquerda != NULL) {
        enfileirar(fila, noAtual->esquerda);
      }
    }
  }
  desenfileira(fila);
  free(marcadorNivel);  
}

No* achaMenorCaminho(No* no) {
  if (no == NULL)
    return NULL;
  if (no->verificaSaida == 1) {
    return no;
  }
  if (no->direita != NULL)
    return achaMenorCaminho(no->direita);

  if (no->baixo != NULL)
    return achaMenorCaminho(no->baixo);

  if (no->esquerda != NULL)
    return achaMenorCaminho(no->esquerda);

  if (no->cima != NULL)
    return achaMenorCaminho(no->cima);

  return no;
}

No* achaMaiorCaminho(No* no, No** maiorNo) {
  if (no == NULL)
    return NULL;
  
  if (no->verificaSaida == 1 && no->tamanho > (*maiorNo)->tamanho) {
    (*maiorNo) = no;
  }

  if (no->direita != NULL)
    achaMaiorCaminho(no->direita, maiorNo);

  if (no->baixo != NULL)
    achaMaiorCaminho(no->baixo, maiorNo);

  if (no->esquerda != NULL)
    achaMaiorCaminho(no->esquerda, maiorNo);

  if (no->cima != NULL)
    achaMaiorCaminho(no->cima, maiorNo);

  return (*maiorNo);
}

// Funcao para imprimir o labirinto
void imprimePercursoNoLabirinto(Labirinto* labirinto, Percurso* percurso, int linha, int coluna, char* escolha, No* no, Fila* fila) {
  // Verificacao para quando o rato ja esta na saida do tabuleiro digitado pelo usuario
  if (percurso->verificaRato == -2)
    printf("O rato nao esta no labirinto.\n");

  // Verificacao para quando o rato ja esta na saida do tabuleiro digitado pelo usuario
  else if (percurso->verificaRato == -1)
    printf("O rato ja esta na saída.\n");

  // Verificacao quando nao achou nenhum caminho
  else if (percurso->quantidadeAchados == 0) 
    printf("EPIC FAIL!\n");

  else if (*escolha == 'f')
    imprimiArvore(no, 0, fila);

  // Como achou caminho, agora ele vai imprimir de acordo com o que o usuario digitou
   else {

    if (*escolha == 'g') {
      No* maior = achaMaiorCaminho(no, &no);
      printf("%d\n", maior->tamanho);
      free(percurso->menorCaminhoX);
      free(percurso->menorCaminhoY);
      percurso->menorCaminhoX = (int*) malloc(sizeof(int) * maior->tamanho + 1);
      percurso->menorCaminhoY = (int*) malloc(sizeof(int) * maior->tamanho + 1);
      No* aux = maior;
      int i = 0;
      while (aux->pai != NULL) {
        percurso->menorCaminhoX[i] = aux->posicao.x;
        percurso->menorCaminhoY[i] = aux->posicao.y;
        aux = aux->pai;
        i++;
      }
      for(int i = 0; i < maior->tamanho; i++) {
        labirinto->tabuleiro[percurso->menorCaminhoX[i]][percurso->menorCaminhoY[i]] = '.';
      }

      for (int i = 0; i < linha; i++) {
        for(int j = 0; j < coluna; j++) {
          printf("%c", labirinto->tabuleiro[i][j]);
        }
        printf("\n");
      }

    }
    else if (*escolha == 's') {
      No* menor = achaMenorCaminho(no);
      printf("%d\n", menor->tamanho);
      free(percurso->menorCaminhoX);
      free(percurso->menorCaminhoY);
      percurso->menorCaminhoX = (int*) malloc(sizeof(int) * menor->tamanho + 1);
      percurso->menorCaminhoY = (int*) malloc(sizeof(int) * menor->tamanho + 1);
      No* aux = menor;
      int i = 0;
      while (aux->pai != NULL) {
        percurso->menorCaminhoX[i] = aux->posicao.x;
        percurso->menorCaminhoY[i] = aux->posicao.y;
        aux = aux->pai;
        i++;
      }

      for(int i = 0; i < menor->tamanho; i++) {
        labirinto->tabuleiro[percurso->menorCaminhoX[i]][percurso->menorCaminhoY[i]] = '.';
      }

      for (int i = 0; i < linha; i++) {
        for(int j = 0; j < coluna; j++) {
          printf("%c", labirinto->tabuleiro[i][j]);
        }
        printf("\n");
      }

    }
  }
}

void limpaFila(Fila* fila) {
  Celula *aux;
  while(fila->inicio != NULL) {
    aux = fila->inicio;
    fila->inicio = aux->prox;
    free(aux->no);
    free(aux);
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

void desalocaFila(Fila* fila) {
  free(fila);
}

void desalocaArvore(No* no) {
  if (no == NULL)
    return;

  desalocaArvore(no->cima);
  desalocaArvore(no->esquerda);
  desalocaArvore(no->baixo);
  desalocaArvore(no->direita);

  free(no);
}