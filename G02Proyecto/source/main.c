/*---------------------------------------------------
Este codigo se ha implementado basandose en el ejemplo "Simple sprite demo" de
dovoto y otro de Jaeden Amero
---------------------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include <stdlib.h>  // srand, rand,...
#include <time.h>    // time
#include <unistd.h>

#include "defines.h"
#include "fondos.h"
#include "rutservs.h"
#include "sprites.h"
#include "teclado.h"
#include "temporizadores.h"

//---------------------------------------------------
// Funciones
//---------------------------------------------------
// Esta funcion consulta si se ha tocado la pantalla tactil
int TactilTocada() {
    touchPosition pos_pantalla;
    touchRead(&pos_pantalla);
    return !(pos_pantalla.px == 0 && pos_pantalla.py == 0);
}
bool BilleteRecogido(int x1, int x2) {
    if (x1<x2 + 8 & x1> x2 - 8)
        return true;
    else if (x3<x2 + 8 & x3> x2 - 8)
        return true;
    else
        return false;
}

//---------------------------------------------------
// Variables globales
//---------------------------------------------------
int cont;
int cont2;
int estado;
int s;
int t;
int x1, x2, x3;
int y1, y2, y3;

//---------------------------------------------------
// main
//---------------------------------------------------
int main() {
    /* Definir variables */
    touchPosition pos_pantalla;

    /* Poner en marcha el motor grafico 2D. */
    powerOn(POWER_ALL_2D);

    /* Establecer la pantalla inferior como principal, inicializar el sistema
   grafico y configurar el sistema de fondos. */
    lcdMainOnBottom();
    initVideo();
    initFondos();

    /* Mostrar fondos en pantalla. */
    SetFondo();
    // mostrarFondoSub();

    /* Inicializar memoria de sprites y guardar en ella los sprites */
    initSpriteMem();
    guardarSpritesEnMemoria();

    /* Establecer las paletas para los sprites */
    establecerPaletaPrincipal();
    establecerPaletaSecundaria();

    /* Inicializa la consola (superior) de texto.
       Nota.- Para borrar la pantalla existe la funcion consoleClear() */
    consoleDemoInit();

    /* Para inicializar el generador de numeros aleatorios en funcion de una
       semilla, en este caso time(NULL). srand() solo se suele activar una vez
       por ejecucion y no devuelve ningun valor.
           La funcion para generar valores aleatorios en el resto del programa
       es rand() */
    srand(time(NULL));

    /* Incluimos la siguiente cabecera para que cada grupo la modifique con
        su numero de grupo "xx" en "Gxx". */
    iprintf("\x1b[02;00H  +--------------------------+  ");
    iprintf("\x1b[03;00H  : EC 17/18           G02   :  ");
    iprintf("\x1b[04;00H  +--------------------------+  ");
    //---------------------------------------------------

    interrupciones();
    x1 = 123;
    y1 = 6;
    x2 = 123;
    y2 = 170;
    x3 = 123;
    y3 = 100;

    estado = Inicio;

    while (true) {
        int i = rand();
        int tecla;
        tecla = TeclaPulsada();
        // if (tecla==A)
        // iprintf("\x1b[08;03H Por encuesta: A      ");
        // if (tecla==START)
        // iprintf("\x1b[08;03H Por encuesta: Start  ");
        // if (tecla==DERECHA)
        // iprintf("\x1b[08;03H Por encuesta: Derecha");
        // if (tecla==ARRIBA)
        // iprintf("\x1b[08;03H Por encuesta: Arriba ");
        // if (tecla==ABAJO)
        // iprintf("\x1b[08;03H Por encuesta: Abajo  ");
        // if (tecla==R)
        // iprintf("\x1b[08;03H Por encuesta: R      ");
        // if (tecla==L)
        // iprintf("\x1b[08;03H Por encuesta: L      ");
        // if (tecla==-1)
        // iprintf("\x1b[08;03H Ninguna tecla pulsada");

        switch (estado) {
            case Inicio:
                iprintf("\x1b[08;00H Pulsar Start para nueva partida");
                iprintf("\x1b[09;00H Tocar pantalla para apagar ");
                iprintf("\x1b[10;00H consola                            ");
                iprintf("\x1b[11;00H                                     ");
                iprintf("\x1b[12;00H                                     ");
                iprintf("\x1b[13;00H                                   ");
                iprintf("\x1b[14;00H                                   ");
                iprintf("\x1b[15;00H                                   ");
                iprintf("\x1b[16;00H                                   ");
                iprintf("\x1b[17;00H                                   ");
                if (TactilTocada())
                    estado = Terminar;
                if (tecla == START) {
                    iprintf("\x1b[07;00H                                    ");
                    iprintf("\x1b[08;00H Pulsar R para pausar            ");
                    iprintf("\x1b[09;00H                                    ");
                    MostrarSobre(x2, y2);
                    estado = Jugando;
                    t = 0;
                    s = 0;
                }
                break;
            case Jugando:
                iprintf("\x1b[15;00H Tiempo de partida: %d", s);
                if (tecla == R) {
                    iprintf("\x1b[08;00H Pulsar L para reanudar          ");
                    estado = Pausa;
                }
                if (y1 > y2) {
                    if (BilleteRecogido(x1, x2))
                        cont++;
                    else
                        cont2++;
                    BorrarBillete(1, x1, y1);
                    x1 = i % 256;
                    y1 = 10;
                    MostrarBillete(1, x1, y1);
                }
                if (y3 > y2) {
                    if (BilleteRecogido(x3, x2))
                        cont++;
                    else
                        cont2++;
                    BorrarBillete(2, x3, y3);
                    x3 = (i % 123) + 631;
                    y3 = 10;
                    MostrarBillete(2, x3, y3);
                }
                iprintf("\x1b[10;00H Billetes recogidos: %d", cont);
                iprintf("\x1b[12;00H Billetes perdidos: %d ", cont2);
                if (cont2 >= 10) {
                    iprintf("\x1b[07;00H Has perdido 10 billetes!         ");
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
                if (s >= 60) {
                    iprintf(
                        "\x1b[07;00H Se ha acabado el tiempo!             ");
                    t = 0;
                    s = 0;
                    cont = 0;
                    cont2 = 0;
                    BorrarBillete(1, x1, y1);
                    BorrarSobre(x2, y2);
                    BorrarBillete(2, x3, y3);
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
                iprintf("\x1b[07;00H                                   ");
                iprintf("\x1b[09;00H                                   ");
                iprintf("\x1b[10;00H                                   ");
                iprintf("\x1b[08;00H Consola apagada                   ");
                iprintf("\x1b[10;00H Tocar pantalla para encender      ");
                iprintf("\x1b[11;00H consola                          ");
                if (TactilTocada())
                    estado = Inicio;
                break;
            case Pausa:
                if (tecla == L) {
                    iprintf("\x1b[08;00H Pulsar R para pausar          ");
                    estado = Jugando;
                }
            default:
                break;
        }  // switch
    }      // while

}  // main
