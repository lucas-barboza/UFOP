#ifndef LABIRINTO_H_INCLUDED
#define LABIRINTO_H_INCLUDED

typedef struct labirinto {
  char** tabuleiro; // Aqui o tabuleiro(labirinto)
  int piorCaso; // Variavel para atribuir o pior caso(tamanho do caminho de saida)
} Labirinto;

typedef struct posicao {
  int x, y;
} Posicao;

typedef struct percurso {
  Posicao* posicao;
  int contadorTamanhoCaminho, index, menorCaminho, *menorCaminhoX, *menorCaminhoY, quantidadeAchados, verificaRato;
} Percurso;

typedef struct no {
  Posicao posicao;
  struct no* direita;
  struct no* baixo;
  struct no* esquerda;
  struct no* cima;
  struct no* pai;
  int tamanho, verificaSaida;
} No;

typedef No* Arvore;

typedef struct celula {
  No* no;
  struct celula* prox;
} Celula;

typedef struct fila {
  Celula* inicio;
  Celula* fim;
  int tamanho;
} Fila;

No* iniciaArvore(Posicao);

No* criaNo(Posicao, No*);

Fila* criaFila();

void enfileirar(Fila*, No*);

No* desenfileira(Fila*);

No* achaMenorCaminho(No*);

No* achaMaiorCaminho(No*, No**);

void imprimeFila(Fila*);

void imprimiArvore(No*, int, Fila*);

void leTamanho(int*, int*, char*);

Labirinto* alocaLabirinto(int, int);

Percurso* alocaPercurso(Labirinto*);

void leLabirinto(Labirinto*, int, int);

void achaRato(Labirinto*, Percurso*, int, int);

void acharSaida(Labirinto*, Percurso*, int, int, No*);

void imprimePercursoNoLabirinto(Labirinto*, Percurso*, int, int, char*, No*, Fila*);

void limpaFila(Fila*);

void desalocaLabirinto(Labirinto*, int);

void desalocaPercurso(Percurso*);

void desalocaFila(Fila*);

void desalocaArvore(No*);

#endif
