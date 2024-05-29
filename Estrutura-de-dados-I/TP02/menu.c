#include <stdio.h>
#include "menu.h"
#include "recursivo.h"
#include "fila.h"
#include "pilha.h"

// Funcao que le o tamanho do labirinto e a escolha de impressao
void leTamanho(int* linha, int* coluna, char* escolha) {
    scanf("%d %d %c", linha, coluna, escolha);
}

// Funcao que chama a funcao recursao ou fila ou pilha
void executaEscolha(char* escolha, int linha, int coluna) {

    if (*escolha == 'r')
        executaRecursao(linha, coluna);

    else if (*escolha == 'f') 
        executaFila(linha, coluna);

    else if (*escolha == 'p')
        executaPilha(linha, coluna);
}