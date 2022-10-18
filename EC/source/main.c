/*---------------------------------------------------
Este codigo se ha implementado basandose en el ejemplo "Simple sprite demo" de
dovoto y otro de Jaeden Amero
---------------------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include <stdlib.h>  // srand, rand,...
#include <time.h>    // time
#include <unistd.h>

#include "adicional.h"
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

//---------------------------------------------------
// Variables globales
//---------------------------------------------------

int estado;
// int dif;
int tecla;
int posBX[4];
int posBY[4];
int i = 0;
int posSX;
int posSY = 174;
int cogidos = 0;
int seg = 60;
int segMas;
int segMenos;
int trans = 0;
int t = 0;

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
    iprintf("\x1b[03;00H  : EC 17/18           G07   :  ");
    iprintf("\x1b[04;00H  +--------------------------+  ");

    //---------------------------------------------------
    interrupciones();

    estado = INICIO;
    int x;
    for (x = 0; x < 4; x++) {
        posBX[x] = rand() % 239;
        posBY[x] = 1;
    }

    while (true) {
        tecla = TeclaPulsada();
        switch (estado) {
            case INICIO:

                if (TactilTocada()) {
                    inicializar();
                }

                break;

            case ENCURSO:

                switch (tecla) {
                    case R:

                        estado = PAUSA;
                        mostrarPausa();
                        break;

                    default:
                        break;
                }

                break;

            case PAUSA:

                if (TactilTocada()) {
                    limpiarPantalla();

                    estado = ENCURSO;
                }

                if (tecla == START) {
                    limpiarPantalla();
                    estado = SELECCION;
                    // mostrarDif();
                }

                break;

            case FINPARTIDA:

                if (tecla == START) {
                    limpiarPantalla();
                    estado = INICIO;
                }

                break;

            case FINJUEGO:

                BorrarSobre(posSX, posSY);
                borrarBilletes();

                InhibirInterrupciones();

                break;
        }
    }
}
