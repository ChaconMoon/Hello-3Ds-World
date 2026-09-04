# Hello 3DS World

Un pequeño **Hello World para Nintendo 3DS**, creado para aprender los fundamentos del desarrollo homebrew con C, devkitARM y libctru.

<p align="center">
        <img src=".github/program_screenshot.png" width="700px" />
</p>

## ¿Qué incluye?

- Inicialización de los servicios gráficos de la consola.
- Texto en la pantalla superior mediante la consola de libctru.
- Bucle principal sincronizado con el refresco vertical.
- Lectura de botones y salida al pulsar `START`.
- Generación de un paquete `.3dsx` para una Nintendo 3DS o un emulador compatible.

## Requisitos

La forma recomendada de compilar el proyecto es utilizar **Visual Studio Code** con el contenedor de desarrollo incluido. El contenedor proporciona las herramientas de devkitPro necesarias para compilar aplicaciones de Nintendo 3DS.

También es posible instalar las herramientas manualmente:

- [Contenedores de desarrollo de devkitPro](https://hub.docker.com/u/devkitpro)
- [Extensión Dev Containers para Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)
- [Instalación de devkitPro para Linux](https://github.com/devkitPro/pacman/releases/tag/v6.0.2)
- [Guía de inicio para Windows](https://devkitpro.org/wiki/Getting_Started)

## Empezar

### 1. Clonar el repositorio

```bash
git clone https://github.com/ChaconMoon/Hello-3Ds-World.git
cd Hello-3Ds-World
```

### 2. Abrir el contenedor de desarrollo

Instala la extensión si todavía no la tienes:

```bash
code --install-extension ms-vscode-remote.remote-containers
```

Abre el proyecto en Visual Studio Code y ejecuta el comando `Dev Containers: Reopen in Container` desde la paleta de comandos (`Ctrl+Shift+P`). Visual Studio Code utilizará la configuración de `.devcontainer/devcontainer.json` y preparará el entorno de compilación.

### 3. Compilar

Desde la terminal del contenedor, ejecuta:

```bash
make
```

El resultado se genera dentro de `dist/Hello3DsWorldChaconMoon/` e incluye el ejecutable `.3dsx`, listo para copiarlo a una Nintendo 3DS o abrirlo en un emulador como [Azahar](https://github.com/azahar-emu/azahar).

Para eliminar los archivos generados:

```bash
make clean
```

## Cómo funciona

El programa utiliza la biblioteca estándar de C y la biblioteca [libctru](https://github.com/devkitPro/libctru) para acceder a los servicios de la Nintendo 3DS:

1. `gfxInitDefault()` inicializa los gráficos.
2. `consoleInit()` prepara la consola de texto en la pantalla superior.
3. `aptMainLoop()` mantiene la aplicación activa.
4. `gspWaitForVBlank()` y `gfxSwapBuffers()` sincronizan y muestran cada fotograma.
5. `hidScanInput()` y `hidKeysDown()` detectan la pulsación de `START`.
6. `gfxExit()` libera los recursos gráficos antes de cerrar la aplicación.

El código principal se encuentra en [`source/main.c`](source/main.c):

```c
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
```

## Estructura del proyecto

```text
.
├── .devcontainer/       # Configuración del contenedor de desarrollo.
├── .vscode/             # Configuración del editor.
├── source/main.c        # Código principal de la aplicación.
├── icon.png             # Icono incluido en el paquete de la aplicación.
├── Makefile             # Reglas de compilación y empaquetado.
└── README.md            # Documentación del proyecto.
```
