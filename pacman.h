#ifndef _PACMAN_H_
#define _PACMAN_H_

#define UP 'w'
#define LEFT 'a'
#define DOWN 's'
#define RIGHT 'd'
#define BOMB 'b'

int acabou();
int validaComando(char direcao);
void movePacman(char direcao);
int movimentacaoFantasma(int xOrigem, int yOrigem, int *xDestino, int *yDestino);
void fantasmas();
void usaPilula();
void usaPilula2(int x, int y, int somaX, int somaY, int max);

#endif