#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv){
    int Mi_ID, Proc_tot;
    int Origen, Etiqueta=100;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &Mi_ID);
    MPI_Comm_size(MPI_COMM_WORLD, &Proc_tot);

    MPI_Send(&Mi_ID, 1, MPI_INT, (Mi_ID+1)%Proc_tot, Etiqueta, MPI_COMM_WORLD);
    MPI_Send(&Origen, 1, MPI_INT, MPI_ABY_SOURCE, Etiqueta, MPI_COMM_WORLD, &status);

    printf('Soy el proceso %d, recibi mensaje de %d\n', Mi_ID, Origen);

    MPI_Finalize();
}