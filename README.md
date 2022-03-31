# CC5512: Proyecto Desarrollo de un Game RPG Engine

En el siguiente repositorio se encontrará un proyecto de creación de un game engine enfocado a desarrollo de juegos de RPG, especificamente de camara top down, con estética retro. El motor se estará desarrollando en C++

Se busca conseguir un Engine en el cual se puedan desarrollar juegos rpg de mundos extensos con la capacidad de ir capturando criaturas/monstruos y poder jugar tanto con el personaje principal, como con los animales atrapados

## tipos de juego objetivo
-Pokemon

-Chrono Trigger

## Requisitos para clonar el repositorio
-Tener Visual Studio 2019 o superior (no se ha probado con versiones anteriores), tener instalado CMake en una version igual o superior a 3.2.0

## Instalación: 

-Clonar el Repositorio en su Ordenador

-Dentro de la carpeta libs, encontrará 3 carpetas: glad, glfw y glm, dentro de cada una de ellas encontrara una carpeta source

-Junto (no dentro) de cada carpeta source, crear una carpeta llamada build, y dentro de ellas (en una cmd) ejecutar cmake ..\source

-Luego en cada carpeta build encontrará un archivo .sln que deberá abrir y compilar con Visual Studio (en modo Release)

## Para ejecutar

-Dirigirse a la carpeta retroEngine, dentro debera repetir el proceso de generar una carpeta build al lado de source y ejecutar cmake ..\source

-Entrar a la carpeta retroEngine/build y abrir el archivo RetroEngine.sln con Visual Stduio

-Compilar el trabajo en Debug o Release

-Entrar a la carpeta retroEngine/build/Debug o retroEngine/build/Release (dependiendo de la compilacion) y ejecutar RetroE.exe

