/**
 * @file Practica4SendRev.c
 *  Programa MPI - Comunicación entre pares de procesos.
 * Si son 6 procesos:   0   1    2   3   4   5
 * El proceso 0 se comunicaría solamente con el proceso 3 y el 3 con el 1 el proceso 1 con el proceso 4 (y el 4 con el 1) y el
 * proceso 2 con el proceso 5 (y el 5 con el 1).
 * El mensaje a enviar será su propio número de proceso.
 * Cada proceso imprimirá el mensaje siguiente:
 * “Soy el proceso <No. proceso> y mi paraja es el proceso <No. proceso Origen>”
 */
#include <stdio.h>
#include <mpi.h>

int main(int argc, char**argv){
    int Mi_ID, Proc_tot;
    int Origen, Etiqueta=100;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &Mi_ID);
    MPI_Comm_size(MPI_COMM_WORLD, &Proc_tot);

    if((Proc_tot % 2) == 0 ){
        MPI_Send(&Mi_ID, 1, MPI_INT, (Mi_ID + 3)%Proc_tot, Etiqueta, MPI_COMM_WORLD);
        MPI_Recv(&Origen, 1, MPI_INT, MPI_ANY_SOURCE, Etiqueta, MPI_COMM_WORLD, &status);

        printf("soy el proceso %d, Mi pareja es %d \n", Mi_ID, Origen);

        MPI_Finalize();
    }else{
        MPI_Finalize();
    }

}
