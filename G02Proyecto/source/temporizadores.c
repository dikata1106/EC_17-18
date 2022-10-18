/*-------------------------------------
 temporizadores.c
-------------------------------------*/
// Anadir los includes que sean necesarios
#include <nds.h>
#include <stdio.h>
#include "defines.h"
#include "sprites.h"

// Rutina de atencion a la interrupcion del temporizador
void BajarBillete() {
    BorrarBillete(1, x1, y1);
    y1 = y1 + 15;
    MostrarBillete(1, x1, y1);
    BorrarBillete(2, x3, y3);
    y3 = y3 + 15;
    MostrarBillete(2, x3, y3);
}
void IntTemp() {
    switch (estado) {
        case Jugando:

            t++;
            if (t >= 64) {  // (t>=20)
                s++;
                t = 0;
            }

            if (y1 < y2) {
                if (t == 0 || t == 32)
                    BajarBillete();

                if (t == 16 || t == 48)
                    BajarBillete();
            }
            break;
        case Inicio:
            break;
        case Terminar:
            break;
        default:
            break;
    }  // switch
}