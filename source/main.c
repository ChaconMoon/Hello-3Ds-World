/* Libería estándar de Input / Output */
#include <stdio.h>

/*Librerías estándar de C*/
#include <stdlib.h>

/* Librería necesaria para la manipulación de arrays de caracteres*/
#include <string.h>

/* Libería con los las utilidades necesarias para trabajar con la 3DS*/
#include <3ds.h>

int main(int argc, char *argv[])
{
        /* Inicializa losservicios gráficos de la consola en el chip PICA200 */
        gfxInitDefault();

        /* Inicializa la interfaz de consola en la pantalla superior */
        consoleInit(GFX_TOP, NULL);

        printf("\x1b[2;2HHola mundo, soy Carlos Chacon desde una New 3DS \x1b[4;2H(https://github.com/ChaconMoon/Hello-3Ds-World)\x1b[6;2H\x1b[4mPulsa el boton Start para salir");

        // Main Loop

        /* Ejecuta el loop del programa hasta que el programa se cierre*/
        while (aptMainLoop())
        {
                /* Pausa la ejecución del programa brevemente hasta que se termine de refrescar la pantalla */
                gspWaitForVBlank();

                /*
                La 3DS utliza un sistema de doble buffer al procesar gráficos, es decir mientras mostramos un buffer estamos creando el siguiente.
                Con esta función cambiamos los buffers de modo que en el que estamos trabajando se muestra y el que se muestra pasa a ser en el que trabajamos.
                */
                gfxSwapBuffers();

                /* Escanea las pulsaciones de los botones*/
                hidScanInput();

                /* Obtiene el valor de 32 bits que obtiene el estado de todos los botones de la 3DS*/
                u32 buttonPresed = hidKeysDown();

                /* Comprobamos si el bit correspondoente al botón start esta activado gracias a una operación AND,
                si es cierto devolvera un valor distinto de cero y la condición será verdadera*/
                if (buttonPresed & KEY_START)
                        break; // Terminar la ejecicón del programa
        }
        /* Libera el buffer de memoria del video, de no hacerlo la consola podría presentar problemas gráficos al volver al menú principal*/
        gfxExit();
        return 0;
}
