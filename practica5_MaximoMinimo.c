/**
 * @file practica5_MaximoMinimo.c
 * Hacer un programa paralelo con MPI en C que calcule el número máximo y el número mínimo de un vector de enteros.
 * Solamente uno de los procesos (proceso raíz) deberá crear el vector de enteros. Dicho proceso deberá generar N 
 * números enteros de manera aleatoria que estén en un rango entre 0 y 100. El valor de N se debe inicializar en la sección de variables (ej. int N=10000;)
 * 
 * Posteriormente el proceso raíz distribuirá por bloques, los N enteros entre todos los procesos creados (incluyendo él mismo).
 * Cada proceso encuentra el número máximo y el número mínimo de los elementos que le tocaron.
 * 
 * El proceso raíz recolecta el mínimo que calculó cada proceso utilizando la función MPI_Reduce, y al mismo tiempo calcula el mínimo de los elementos que va recibiendo.
 * 
 * El proceso raíz recolecta el máximo de cada proceso mediante la función MPI_Reduce, y al mismo tiempo calcula el máximo de los elementos que va recibiendo.
 * 
 * El proceso raíz imprime el máximo y el mínimo calculado
 * 
 * Para facilitar la compresión del programa, se debe crear un número de procesos que divida exactamente a N, de esta manera a cada proceso le tocará el mismo número de elementos del vector. (ej.  si N=10000,  y número de procesos = 5,  10000/5 = 2000, sí es divisible)
 */
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv){

}