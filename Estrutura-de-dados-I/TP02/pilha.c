#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

void executaPilha(int linha, int coluna) {
    Labirinto *labirinto = alocaLabirinto(linha, coluna); // Aloca o labirinto
    leLabirinto(labirinto, linha, coluna); // Le o labirinto
    Pilha *pilha = criaPilha(); // Aloca a pilha
    Percurso *percurso = alocaPercurso(labirinto); // Aloca o percurso
    int *posicaoRato = achaRato(labirinto, percurso, linha, coluna); // Acha a posicao inicial do rato
    iniciaPilha(pilha, posicaoRato); // Inicia a pilha
    acharSaidaPilha(labirinto, percurso, pilha, linha, coluna); // Acha a saida pelo metodo pilha
    imprimeLabirintoPilha(labirinto, percurso, pilha, linha, coluna); // Imprime o labirinto
    free(posicaoRato); // Desaloca o vetor de inteiros posicaoRato
    desalocaPilha(pilha); // Desaloca a pilha
    desalocaPercurso(percurso); // Desaloca o struct percurso
    desalocaLabirinto(labirinto, linha); // Desaloca o struct labirinto
};

// Funcao que cria a pilha e inicia o inicio como NULL e o tamanho 0
Pilha* criaPilha() {
    Pilha* pilha = (Pilha*) malloc(sizeof(Pilha));
    pilha->inicio = NULL;
    pilha->tamanho = 0;
    return pilha;
}

// Funcao que inicia a pilha criando uma celula nova para posicao inicial do rato
void iniciaPilha(Pilha* pilha, int* posicaoRato) {
    Celula *aux = (Celula *)malloc(sizeof(Celula));
    aux->posicao = (Posicao *)malloc(sizeof(Posicao));
    // A nova celula tem a posicao inicial do rato
    aux->posicao->x = posicaoRato[0];
    aux->posicao->y = posicaoRato[1];
    aux->prox = pilha->inicio; // O proximo depois da celula é NULL(pilha->inicio pois ela incia como NULL)
    pilha->inicio = aux; // Agora o inicio aponta para nova celula
}

// Funcao que verifica se a pilha é vazia
int pilhaVazia(Pilha* pilha) {
    return pilha->inicio == NULL;
}

// Funcao que empilha na pilha
void pilhaEmpilha(Pilha* pilha, Posicao* posicao) {
    Posicao* posicaoAux = (Posicao*)malloc(sizeof(Posicao));
    posicaoAux->x = posicao->x; // Salva a posicao X em uma struct posicao
    posicaoAux->y = posicao->y; // Salva a posicao Y em uma struct posicao
    Celula *aux = (Celula*) malloc(sizeof(Celula));
    aux->posicao = posicaoAux; // Salva a posicao nessa nova celula
    aux->prox = pilha->inicio; // A celula que o inicio apontava agora é a proxima da nova celula
    pilha->inicio = aux; // Inicio aponta para nova celula
    pilha->tamanho++; // Soma um no tamanho da pilha
}

// Funcao apra desempilhar da pilha
Posicao* pilhaDesempilha(Pilha* pilha) {
    if (pilhaVazia(pilha)) // Verifica se a pilha é vazia
        return NULL;
    Celula* aux = pilha->inicio; // Cria um ponteiro que aponta pro ponteiro inicio que aponta pro primeiro da pilha
    Posicao* auxPosicao = aux->posicao; // Cria um ponteiro Posicao que aponta pro struct posicao da celula que aux esta apontando
    pilha->inicio = aux->prox; // O ponteiro inicio agora aponta pro proximo da primeira celula
    free(aux); // Libera aux que libera a primeira celula da pilha
    return auxPosicao;
}

// Funcao para achar a saida pelo metodo pilha
void acharSaidaPilha(Labirinto* labirinto, Percurso* percurso, Pilha* pilha, int linha, int coluna) { // Acha a saida do rato, se existe
    Posicao* posicao;
    while (pilha->inicio != NULL) {
        posicao = pilhaDesempilha(pilha); // Pega a ultima posicao da celula desempilhada
        Posicao* posicaoAtual = posicao;

        Posicao* posicaoEmpilhar = (Posicao*) malloc(sizeof(Posicao));
        posicaoEmpilhar->x = posicaoAtual->x; // Salva a posicao atual X
        posicaoEmpilhar->y = posicaoAtual->y; // Salva a posicao atual Y

        // DIREITA
        int podeIrParaDireita = posicaoAtual->y + 1 < coluna ? 1 : 0; // Verifica se pode ir para direita, para quando chegar na saida nao verificar uma posicao invalida
        if (podeIrParaDireita && labirinto->tabuleiro[posicaoAtual->x][posicaoAtual->y + 1] == ' ') {
            posicaoEmpilhar->y++; // Soma um no Y
            pilhaEmpilha(pilha, posicaoEmpilhar); // Desempilha um item
            labirinto->tabuleiro[posicaoEmpilhar->x][posicaoEmpilhar->y] = 'o'; // Adiciona 'o' no caminho do labirinto
            posicaoEmpilhar->y--; // Subtrai um no Y
        }

        // BAIXO
        if (labirinto->tabuleiro[posicaoAtual->x + 1][posicaoAtual->y] == ' ') {
            posicaoEmpilhar->x++; // Soma um no X
            pilhaEmpilha(pilha, posicaoEmpilhar);
            labirinto->tabuleiro[posicaoEmpilhar->x][posicaoEmpilhar->y] = 'o';
            posicaoEmpilhar->x--; // Subtrai um no X
        }
            // printf("IF BAIXO x = %d y = %d \n", pilha->cabeca->posicao->x, pilha->cabeca->posicao->y);
    // printf("QUEBREI2\n");
        // ESQUERDA
        if (labirinto->tabuleiro[posicaoAtual->x][posicaoAtual->y - 1] == ' ') {
            posicaoEmpilhar->y--; // Subtrai um no Y
            pilhaEmpilha(pilha, posicaoEmpilhar);
            labirinto->tabuleiro[posicaoEmpilhar->x][posicaoEmpilhar->y] = 'o';
            posicaoEmpilhar->y++; // Soma um no Y
        }

        // CIMA
        if (labirinto->tabuleiro[posicaoAtual->x - 1][posicaoAtual->y] == ' ') {
            posicaoEmpilhar->x--; // Subtrai um no X
            pilhaEmpilha(pilha, posicaoEmpilhar);
            labirinto->tabuleiro[posicaoEmpilhar->x][posicaoEmpilhar->y] = 'o';
            posicaoEmpilhar->x++; // Soma um no X
        }
        int d;
        scanf("%d", &d);
        imprimeLabirintoPilha(labirinto, percurso, pilha, linha, coluna);
        // Verifica para nao liberar uma posicao nula
        if (posicaoAtual != NULL)
            free(posicaoAtual);
        free(posicaoEmpilhar); // Libera a posicaoEmpilhar
    }
    limpaPilha(pilha); // Libera as posicoes da pilha
}

void imprimeLabirintoPilha(Labirinto *labirinto, Percurso *percurso, Pilha *pilha, int linha, int coluna) {
    // Verificacao para quando o rato ja esta na saida do tabuleiro digitado pelo usuario
    if (percurso->verificaRato == -2)
        printf("O rato nao esta no labirinto.\n");

    // Verificacao para quando o rato ja esta na saida do tabuleiro digitado pelo usuario
    else if (percurso->verificaRato == -1)
        printf("O rato ja esta na saída.\n");

    // Imprimi o labirinto
    else {
        printf("%d\n", pilha->tamanho);
        for (int i = 0; i < linha; i++) {
            for (int j = 0; j < coluna; j++) {
                printf("%c", labirinto->tabuleiro[i][j]);
            }
            printf("\n");
        }
    }
}

// Funcao para desalocar a pilha ate que o inicio aponte para nulo
void limpaPilha(Pilha* pilha) {
    Celula *aux;
    while (pilha->inicio != NULL) {
        aux = pilha->inicio;
        pilha->inicio = aux->prox;
        free(aux->posicao);
        free(aux);
    }
}

// Funcao para desalocar a pilha
void desalocaPilha(Pilha* pilha) {
    free(pilha);
}
