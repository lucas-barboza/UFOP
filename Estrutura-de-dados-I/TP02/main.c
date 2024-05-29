#include "menu.h"
#include <stdio.h>

int main() {
    int linha, coluna; // Variaveis para salvar o tamanho do labirinto
    char escolha[1]; // A escolha de impressao do usuario
    leTamanho(&linha, &coluna, escolha); // Le o tamanho do labirinto e a escolha do usuario
    executaEscolha(escolha, linha, coluna); // Chama a função para executar a saída dp labirinto de acordo com o que o usuario pedir
    return 0;
}