#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "pacman.h"
#include "mapa.h"
#include "ui.h"

MAPA m;
POSICAO pacman;
char comando;
int temPilula = 0;

int main() {

    leMapa(&m);
    encontraMapa(&m, &pacman, PACMAN);

    do {
        printf("Pílula: %s\n", (temPilula ? "SIM" : "NAO"));
        mostraMapa(&m);

        scanf(" %c", &comando);
        
        if(validaComando(comando)) movePacman(comando);
        if(comando == BOMB) usaPilula();

        fantasmas();
    } while(!acabou());

    liberaMemoriaMapa(&m);

    return 0;
}

int acabou() {
    POSICAO pos;
    int perdeu = !encontraMapa(&m, &pos, PACMAN);
    int ganhou = !encontraMapa(&m, &pos, GHOST);

    return ganhou || perdeu;
}

int validaComando(char direcao) {
    return direcao == UP || direcao == LEFT ||
        direcao == DOWN || direcao == RIGHT;
}

void movePacman(char direcao) {

    if(!validaComando(direcao)) {
        return;
    }

    int proximoX = pacman.x, proximoY = pacman.y;

    switch(direcao) {
        case UP:
            proximoX--;
            break;
        case LEFT:
            proximoY--;
            break;
        case DOWN:
            proximoX++;
            break;
        case RIGHT:
            proximoY++;
            break;
    }

    if(!podeAndar(&m, PACMAN, proximoX, proximoY)) {
        return;
    }

    if(validaPersonagem(&m, PILL, proximoX, proximoY)) {
        temPilula = 1;
    }

    movimenta(&m, pacman.x, pacman.y, proximoX, proximoY);
    pacman.x = proximoX;
    pacman.y = proximoY;

}

int movimentacaoFantasma(int xOrigem, int yOrigem, int *xDestino, int *yDestino) {
    int direcoesPossiveis[4][2] = {
        {xOrigem, yOrigem + 1},
        {xOrigem + 1, yOrigem},
        {xOrigem, yOrigem - 1},
        {xOrigem - 1, yOrigem}
    };

    int maximoDeTentativas = 10;

    srand(time(0));
    for(int i = 0; i < maximoDeTentativas; i++) {
        int posicao = rand() % 4;

        if(podeAndar(&m, GHOST, direcoesPossiveis[posicao][0], direcoesPossiveis[posicao][1]) && validaComando(comando)) {
            *xDestino = direcoesPossiveis[posicao][0];
            *yDestino = direcoesPossiveis[posicao][1];
            return 1;
        }
    }
    return 0;
}

void fantasmas() {
    MAPA copia;

    copiaMapa(&copia, &m);

    for(int i = 0; i < m.linhas; i++) {
        for(int j = 0; j < m.colunas; j++) {
            if(copia.matriz[i][j] == GHOST) {

                int xDestino, yDestino;

                int encontrou = movimentacaoFantasma(i, j, &xDestino, &yDestino);

                if(encontrou) {
                    movimenta(&m, i, j, xDestino, yDestino);
                }
            }
        }
    }
    liberaMemoriaMapa(&copia);
}

void usaPilula2(int x, int y, int somaX, int somaY, int max) {
    if(max == 0) return;

    int novoX = x + somaX;
    int novoY = y + somaY;

    if(!validaMovimentacao(&m, novoX, novoY)) return;
    if(validaParedes(&m, novoX, novoY)) return;

    m.matriz[novoX][novoY] = VAZIO;
    usaPilula2(novoX, novoY, somaX, somaY, max - 1);
}

void usaPilula() {
    if(!temPilula) return;

    usaPilula2(pacman.x, pacman.y, 0, 1, 3);
    usaPilula2(pacman.x, pacman.y, 0, -1, 3);
    usaPilula2(pacman.x, pacman.y, 1, 0, 3);
    usaPilula2(pacman.x, pacman.y, -1, 0, 3);

    temPilula = 0;
}
