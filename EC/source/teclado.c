/*-------------------------------------
 teclado.c
-------------------------------------*/

// Anadir los includes que sean necesarios
#include <nds.h>
#include <stdio.h>
#include "defines.h"
#include "sprites.h"

// Esta funcion tiene que devolver el valor de la tecla pulsada
int TeclaPulsada() {
    // Devuelve el valor asociado a la tecla pulsada:
    // A=0; B=1; Select=2; Start=3; Der=4; Izq=5;
    // Arriba=6; Abajo=7; R=8; L=9;
    // -1 en otros casos
    if (!(TECLAS_DAT & 0X01))
        return A;
    if (!(TECLAS_DAT & 0X02))
        return B;
    if (!(TECLAS_DAT & 0X04))
        return SELECT;
    if (!(TECLAS_DAT & 0X08))
        return START;
    if (!(TECLAS_DAT & 0X010))
        return DERECHA;
    if (!(TECLAS_DAT & 0X020))
        return IZQUIERDA;
    if (!(TECLAS_DAT & 0X040))
        return ARRIBA;
    if (!(TECLAS_DAT & 0X080))
        return ABAJO;
    if (!(TECLAS_DAT & 0X0100))
        return R;
    if (!(TECLAS_DAT & 0X0200))
        return L;
    else
        return -1;
}

// Rutina de atencion a la interrupcion del teclado
void IntTec() {
    int tecla = TeclaPulsada();

    switch (tecla) {
        case B:

            if (estado == ENCURSO) {
                estado = FINPARTIDA;
                finalizar();
            }
            break;

        case SELECT:

            if (estado != FINJUEGO) {
                limpiarPantalla();
                estado = FINJUEGO;
            }

            break;

        case IZQUIERDA:

            if (estado == ENCURSO) {
                if (posSX >= 10) {
                    posSX = posSX - 10;
                }

                MostrarSobre(posSX, 174);
            }
            break;

        case DERECHA:

            if (estado == ENCURSO) {
                if (posSX <= 233) {
                    posSX = posSX + 10;
                }

                MostrarSobre(posSX, 174);
            }
            break;

        default:
            break;
    }
}
