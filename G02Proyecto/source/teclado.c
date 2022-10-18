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
    if (!(TECLAS_DAT & 0x01))
        return A;
    if (!(TECLAS_DAT & 0x02))
        return B;
    if (!(TECLAS_DAT & 0x04))
        return SELECT;
    if (!(TECLAS_DAT & 0x08))
        return START;
    if (!(TECLAS_DAT & 0x10))
        return DERECHA;
    if (!(TECLAS_DAT & 0x20))
        return IZQUIERDA;
    if (!(TECLAS_DAT & 0x40))
        return ARRIBA;
    if (!(TECLAS_DAT & 0x80))
        return ABAJO;
    if (!(TECLAS_DAT & 0x100))
        return R;
    if (!(TECLAS_DAT & 0x200))
        return L;
    else
        return -1;
}

void MoverIzq() {
    BorrarSobre(x2, y2);
    x2 = x2 - 10;
    MostrarSobre(x2, y2);
}
void MoverDer() {
    BorrarSobre(x2, y2);
    x2 = x2 + 10;
    MostrarSobre(x2, y2);
}

// Rutina de atencion a la interrupcion del teclado
void IntTec() {
    int tecla;
    tecla = TeclaPulsada();
    // if (tecla==B)
    // iprintf("\x1b[10;03H Por interrupcion: B        ");
    // if (tecla==SELECT)
    // iprintf("\x1b[10;03H Por interrupcion: Select   ");
    // if (tecla==IZQUIERDA)
    // iprintf("\x1b[10;03H Por interrupcion: Izquierda");

    switch (estado) {
        case Inicio:
            break;
        case Jugando:
            if (tecla == IZQUIERDA)
                MoverIzq();
            if (tecla == DERECHA)
                MoverDer();
            if (tecla == B) {
                iprintf("\x1b[07;00H Partida terminada             ");
                t = 0;
                s = 0;
                cont = 0;
                cont2 = 0;
                BorrarBillete(1, x1, y1);
                BorrarBillete(2, x3, y3);
                BorrarSobre(x2, y2);
                x1 = 123;
                y1 = 6;
                x2 = 123;
                y2 = 170;
                x3 = 123;
                y3 = 100;
                estado = Inicio;
            }
            break;
        case Pausa:
            if (tecla == B) {
                iprintf("\x1b[07;00H Partida terminada             ");
                t = 0;
                s = 0;
                cont = 0;
                cont2 = 0;
                iprintf("\x1b[10;00H                                  ");
                iprintf("\x1b[11;00H                                    ");
                iprintf("\x1b[12;00H                                     ");
                iprintf("\x1b[13;00H                                   ");
                iprintf("\x1b[14;00H                                   ");
                iprintf("\x1b[15;00H                                   ");
                BorrarBillete(1, x1, y1);
                BorrarBillete(2, x3, y3);
                BorrarSobre(x2, y2);
                x1 = 123;
                y1 = 6;
                x2 = 123;
                y2 = 170;
                x3 = 123;
                y3 = 100;
                estado = Inicio;
            }
            break;
        case Terminar:
            break;
        default:
            break;
    }  // switch
}