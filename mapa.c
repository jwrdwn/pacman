#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"

void leMapa(MAPA *m) {
    FILE *f;
    f = fopen("mapa.txt", "r");
    if(f == 0) {
        printf("Erro na leitura do arquivo.");
        exit(1);
    }

    fscanf(f, "%d %d", &(m -> linhas), &(m -> colunas));
    
    alocaMapa(m);

    for(int i = 0; i < m -> linhas; i++) {
        fscanf(f, "%s", m -> matriz[i]);
    }

    fclose(f);
}

void alocaMapa(MAPA *m) {
    m -> matriz = malloc(sizeof(char*) * (m -> linhas));
    for(int i = 0; i < m -> linhas; i++) {
        m -> matriz[i] = malloc(sizeof(char) * (m -> colunas + 1));
    }
}

void copiaMapa(MAPA *destino, MAPA *origem) {
    destino -> linhas = origem -> linhas;
    destino -> colunas = origem -> colunas;

    alocaMapa(destino);
    for(int i = 0; i < origem -> linhas; i++) {
        strcpy(destino -> matriz[i], origem -> matriz[i]);
    }
}

void liberaMemoriaMapa(MAPA *m) {
    for(int i = 0; i < m -> linhas; i++) {
        free(m -> matriz[i]);
    }

    free(m -> matriz);
}

int encontraMapa(MAPA *m, POSICAO *p, char c) {
    for(int i = 0; i < m -> linhas; i++) {
        for(int j = 0; j < m -> colunas; j++) {
            if(m -> matriz[i][j] == c) {
                p -> x = i;
                p -> y = j;
                return 1;
            }
        }
    }
    return 0;
}

int podeAndar(MAPA *m, char personagem, int x, int y) {
    return validaMovimentacao(m, x, y) && !validaParedes(m, x, y) && !validaPersonagem(m, personagem, x, y);
}

int validaMovimentacao(MAPA *m, int x, int y) {
    if(x >= m -> linhas) {
        return 0;
    }
    if(y >= m -> colunas) {
        return 0;
    }
    return 1;
}

int validaPersonagem(MAPA *m, char personagem, int x, int y) {
    return m -> matriz[x][y] == personagem;
}

int validaParedes(MAPA *m, int x, int y) {
    return m -> matriz[x][y] == PAREDE_VERTICAL ||
            m -> matriz[x][y] == PAREDE_HORIZONTAL;
}

void movimenta(MAPA *m, int xOrigem, int yOrigem,
                                int xDestino, int yDestino) {
    
    char personagem = m -> matriz[xOrigem][yOrigem];
    
    m -> matriz[xDestino][yDestino] = personagem;
    m -> matriz[xOrigem][yOrigem] = VAZIO;
}
