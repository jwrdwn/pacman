#ifndef _MAPA_H_
#define _MAPA_H_

#define PACMAN '@'
#define GHOST 'X'
#define PILL '0'
#define VAZIO '.'
#define PAREDE_VERTICAL '|'
#define PAREDE_HORIZONTAL '-'

typedef struct mapa {
    char **matriz;
    int linhas;
    int colunas;
} MAPA;

typedef struct posicao {
    int x;
    int y;
} POSICAO;

void alocaMapa(MAPA *m);
void leMapa(MAPA *m);
void liberaMemoriaMapa(MAPA *m);
int encontraMapa(MAPA *m, POSICAO *p, char c);
void copiaMapa(MAPA *destino, MAPA *origem);
int validaMovimentacao(MAPA *m, int x, int y);
int validaParedes(MAPA *m, int x, int y);
int validaPersonagem(MAPA *m, char personagem, int x, int y);
int podeAndar(MAPA *m, char personagem, int x, int y);
void movimenta(MAPA *m, int xOrigem, int yOrigem,
                                int xDestino, int yDestino);

#endif