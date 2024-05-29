#ifndef LABIRINTO_H_INCLUDED
#define LABIRINTO_H_INCLUDED

typedef struct labirinto Labirinto;

typedef struct posicao Posicao;

typedef struct percurso Percurso;

void leTamanho(int*, int*, char*);

Labirinto* alocaLabirinto(int, int);

Percurso* alocaPercurso(Labirinto*);

void leLabirinto(Labirinto*, int, int);

void achaRato(Labirinto*, Percurso*, int, int);

void acharSaida(Labirinto*, Percurso*, int, int);

void imprimePercursoNoLabirinto(Labirinto*, Percurso*, int, int, char*);

void desalocaLabirinto(Labirinto*, int);

void desalocaPercurso(Percurso*);

#endif
