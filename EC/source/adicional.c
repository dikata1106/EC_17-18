/*-------------------------------------
 adicional.c
-------------------------------------*/
// Anadir los includes que sean necesarios
#include <nds.h>
#include <stdio.h>
#include "defines.h"
#include "sprites.h"

// Imprime todo menos el titulo en blanco para limpiar la pantalla y poder
// escribir sobre limpio
void limpiarPantalla() {
    iprintf("\x1b[01;00H                                ");
    iprintf("\x1b[05;00H                                ");
    iprintf("\x1b[06;00H                                ");
    iprintf("\x1b[07;00H                                ");
    iprintf("\x1b[08;00H                                ");
    iprintf("\x1b[09;00H                                ");
    iprintf("\x1b[10;00H                                ");
    iprintf("\x1b[11;00H                                ");
    iprintf("\x1b[12;00H                                ");
    iprintf("\x1b[13;00H                                ");
    iprintf("\x1b[14;00H                                ");
    iprintf("\x1b[15;00H                                ");
    iprintf("\x1b[16;00H                                ");
    iprintf("\x1b[17;00H                                ");
    iprintf("\x1b[18;00H                                ");
    iprintf("\x1b[19;00H                                ");
    iprintf("\x1b[20;00H                                ");
    iprintf("\x1b[21;00H                                ");
    iprintf("\x1b[22;00H                                ");
    iprintf("\x1b[23;00H                                ");
}

// Despues de seleccionar la dificultad de la partida, imprime un breve resumen
// del funcionamiento de la partida
void inicioPartida() {
    limpiarPantalla();

    iprintf("\x1b[08;00H  RECOGE EL MAXIMO DE BILLETES POSIBLES   ");
    iprintf("\x1b[10;00H  Tiempo de juego 60 segundos   ");

    iprintf("\x1b[19;00H  PAUSA -> (Tecla R)            ");
    iprintf("\x1b[19;00H  TOCA LA PANTALLA PARA EMPEZAR ");
}

void borrarBilletes() {
    int j;
    for (j = 0; j < i; j++) {
        BorrarBillete(j, posBX[j], posBY[j]);
    }
}

void mostrarBilletes() {
    int j;
    for (j = 0; j < i; j++) {
        posBY[j] = posBY[j] + 1;
        MostrarBillete(j, posBX[j], posBY[j]);
    }
}

void billeteCogido() {
    cogidos++;
}

void inicializar() {
    limpiarPantalla();

    int x;

    for (x = 0; x < 4; x++) {
        posBX[x] = rand() % 239;
        posBY[x] = 1;
    }

    posSX = 120;
    mostrarBilletes();
    MostrarSobre(posSX, posSY);

    cogidos = 0;

    seg = 60;
    trans = 0;
    t = 0;

    estado = ENCURSO;
}

void finalizar() {
    limpiarPantalla();

    borrarBilletes();

    BorrarSobre(posSX, posSY);

    mostrarResultado();
}

void mostrarResultado() {
    iprintf("\x1b[06;00H       FIN DE LA PARTIDA        ");
    iprintf("\x1b[11;00H  COGIDOS:     %d     ", cogidos);
    iprintf("\x1b[21;00H  NUEVA PARTIDA     <START>     ");
    iprintf("\x1b[22;00H  SALIR             <SELECT>    ");
}

void mostrarPausa() {
    limpiarPantalla();
    iprintf("\x1b[09;00H            EN PAUSA            ");
    iprintf("\x1b[14;00H  NUEVA PARTIDA     <START>     ");
    iprintf("\x1b[15;00H  SALIR             <SELECT>    ");
    iprintf("\x1b[19;00H TOCA LA PANTALLA PARA CONTINUAR");
}
