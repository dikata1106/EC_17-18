/*-------------------------------------
 temporizadores.c
-------------------------------------*/
// Anadir los includes que sean necesarios
#include <nds.h>
#include <stdio.h>
#include "adicional.h"
#include "defines.h"
#include "sprites.h"
void comprobar() {
    int k;
    for (k = 0; k < i; k++) {
        if (posBY[k] >= (posSY - 6) && (posSX >= (posBX[k] - 6)) &&
            (posSX <= (posBX[k] + 6))) {
            BorrarBillete(k, posBX[k], posBY[k]);
            posBY[k] = 0;
            posBX[k] = rand() % 239;
            billeteCogido();
        }
    }
}

// Añade contador de billetes
void anadirCont() {
    if (i < 4) {
        i++;

    }  // if(i < 4)
}  // anadirCont

// Rutina de atencion a la interrupcion del temporizador
void IntTemp() {
    if (estado == ENCURSO) {
        iprintf("\x1b[08;00H  TIEMPO RESTANTE:       %d      ", seg);
        iprintf("\x1b[12;00H  > Billete COGIDOS:     %d      ", cogidos);
        iprintf("\x1b[17;00H  Pulsa <R> para pausar partida ");

        t++;

        if (t >= 512) {
            seg--;
            trans++;

            t = 0;
        }

        if (seg <= 0) {
            estado = FINPARTIDA;

        }  // if(seg <= 0)

        if (t == 510) {
            anadirCont();
        }

        if (estado == FINPARTIDA) {
            finalizar();
        }
    }
}
