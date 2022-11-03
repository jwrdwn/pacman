#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "mapa.h"

char desenhoParede[3][7] = {
    {"......"  },
    {"......"  },
    {"......"  }
};

char desenhoGhost[3][7] = {
    {" .-.  "  },
    {"| OO| "  },
    {"'^^^' "  }
};

char desenhoPacman[3][7] = {
    {" .--. "  },
    {"/    \\" },
    {" '--' "  }
};

char desenhoPill[3][7] = {
    {"      "  },
    {" .-.  "  },
    {" '-'  "  }
};

char desenhoVazio[3][7] = {
    {"      "  },
    {"      "  },
    {"      "  }
};

void imprimeParte(char desenho[3][7], int parte) {
    printf("%s", desenho[parte]);
}

void mostraMapa(MAPA *m) {
    for(int i = 0; i < m -> linhas; i++) {
        for(int parte = 0; parte < 3; parte++) {
            for(int j = 0; j < m -> colunas; j ++) {
                switch(m -> matriz[i][j]) {
                    case GHOST:
                        imprimeParte(desenhoGhost, parte);
                        break;
                    case PACMAN:
                        imprimeParte(desenhoPacman, parte);
                        break;
                    case PILL:
                        imprimeParte(desenhoPill, parte);
                        break;
                    case PAREDE_VERTICAL:
                    case PAREDE_HORIZONTAL:
                        imprimeParte(desenhoParede, parte);
                        break;
                    case VAZIO:
                        imprimeParte(desenhoVazio, parte);
                        break;
                }
            }
            printf("\n");
        }
    }
}
