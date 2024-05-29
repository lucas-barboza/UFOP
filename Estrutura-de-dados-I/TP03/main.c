#include "labirinto.h"
#include <stdio.h>

int main() {
  int linha, coluna; // Variaveis para salvar o tamanho do labirinto
  char escolha[1]; // A escolha de impressao do usuario
  leTamanho(&linha, &coluna, escolha); // Le o tamanho do labirinto e a escolha do usuario
  Labirinto* labirinto = alocaLabirinto(linha, coluna); // Aloca o labirinto
  leLabirinto(labirinto, linha, coluna); // Le o labirinto
  Percurso* percurso = alocaPercurso(labirinto); // Aloca o percurso
  achaRato(labirinto, percurso, linha, coluna); // Acha a posicao inicial do rato
  No* raiz = iniciaArvore(percurso->posicao[percurso->index]);
  Fila* fila = criaFila();
  acharSaida(labirinto, percurso, linha, coluna, raiz); // Acha a saida do rato, se existe
  imprimePercursoNoLabirinto(labirinto, percurso, linha, coluna, escolha, raiz, fila); // Imprimi a saida de acordo
  // printf("Nivel 1:\n (%d, %d) \n", raiz->posicao.x, raiz->posicao.y);
  // imprimiArvore(raiz, 0, fila);
  desalocaPercurso(percurso); // Desaloca o struct percurso
  desalocaLabirinto(labirinto, linha); // Desaloca o struct labirinto
  desalocaFila(fila);
  desalocaArvore(raiz);
  return 0;
}