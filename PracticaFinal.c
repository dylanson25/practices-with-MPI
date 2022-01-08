/**
 * Elegir e implementar la solución con MPI, de uno de los dos problemas 6.1 
 * (Producto de dos vectores) y 6.3 (Multiplicación de matrices) que se explican 
 * en el capítulo 6 (Ejemplo de Programas Paralelos) del libro de "Introducción a
 *  la Computación Paralela" utilizado en clase.
 * 
 * En este caso este sea la solucion al primer problema Producto de vectores 6.1
 */

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv){
    int Mi_ID, Proc_tot;
    int Origen, Etiqueta=100;
    

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &Mi_ID);
    MPI_Comm_size(MPI_COMM_WORLD, &Proc_tot);

    MPI_Finalize();
}