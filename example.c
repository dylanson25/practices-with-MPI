#include <stdio.h>
#include <mpi.h>

int main (int argc, char** argv){

    int n, m, source, p;

    MPI_Status status;
    MPI_Init (&argc, &argv);
    MPI_Comn_rank(MPI_COMM_WORLD, &n);//id del proceso
    MPI_Comn_size(MPI_COMM_WORLD, &m);//cuntos procesos

    if(n==0) MPI_send(&m, 1, MPI_INT, 1, 100, MPI_COMM_WORLD);
    else MPI_Recv( &p , 1 , MPI_INT, 0 , 100 , MPI_COMM_WORLD , &status);

    printf("%d", p);
    MPI_Finalize();
}