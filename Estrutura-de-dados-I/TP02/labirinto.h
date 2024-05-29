#ifndef LABIRINTO_H_INCLUDED
#define LABIRINTO_H_INCLUDED

typedef struct {
    char** tabuleiro; // Aqui o tabuleiro(labirinto)
    int piorCaso; // Variavel para atribuir o pior caso(tamanho do caminho de saida)
} Labirinto;

typedef struct {
    int x, y;
} Posicao;

typedef struct {
    Posicao* posicao;
    int contadorTamanhoCaminho, index, menorCaminho, *menorCaminhoX, *menorCaminhoY, quantidadeAchados, verificaRato, contSemSaida;
} Percurso;

typedef struct celula {
    Posicao* posicao;
    struct celula* prox;
} Celula;

Labirinto* alocaLabirinto(int, int);

Percurso* alocaPercurso(Labirinto*);

void leLabirinto(Labirinto*, int, int);

int* achaRato(Labirinto*, Percurso*, int, int);

void desalocaLabirinto(Labirinto*, int);

void desalocaPercurso(Percurso*);

#endif
