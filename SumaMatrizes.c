/**
 * @file SumaMatrizes.c
 * Este es un ejemplo para practicar con la libreria de mpi
 */
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv)
{

    const int N = 4;
    const int M = 3;

    const int ProcRaiz = 0;

    int MiID, TotProcesos;

    int MatrizA[N][M];
    int MatrizB[N][M];
    int MatrizC[N][M];

    int Vector_localA[N][M];
    int Vector_localB[N][M];

    int i;
    int j;

    int NumFilas;
    int Block_size;
  

    double Tiempo_inicial, Tiempo_final, Tiempo_total;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &MiID);

    MPI_Comm_size(MPI_COMM_WORLD, &TotProcesos);


    if (MiID == ProcRaiz)
    {
        srand(MPI_Wtime());
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < M; j++)
            {
                MatrizA[i][j] = rand() % 11;
                MatrizB[i][j] = rand() % 11;
                printf("Matriz A[%d][%d] = [%d] \n", i, j, MatrizA[i][j]);
                printf("Matriz B[%d][%d] = [%d] \n", i, j, MatrizB[i][j]);
            }
        }

        Tiempo_inicial = MPI_Wtime();
    }
    NumFilas = N/TotProcesos;
    Block_size = NumFilas * M;
    
    MPI_Scatter(MatrizA, Block_size, MPI_INT, Vector_localA, Block_size, MPI_INT, ProcRaiz, MPI_COMM_WORLD);
    MPI_Scatter(MatrizB, Block_size, MPI_INT, Vector_localB, Block_size, MPI_INT, ProcRaiz, MPI_COMM_WORLD);
    
    int Vector_localC[M][M];
    for (i = 0; i < Block_size; i++)
    {
        Vector_localC[i] = Vector_localA[i] + Vector_localB[i];

    }

    MPI_Gather(Vector_localC, Block_size, MPI_INT, MatrizC, Block_size, MPI_INT, ProcRaiz, MPI_COMM_WORLD);

    if (MiID == ProcRaiz)
    {
        Tiempo_final = MPI_Wtime();
        Tiempo_total = Tiempo_final - Tiempo_inicial;

        for (i = 0; i < N; i++)
        {
            for (j = 0; j < M; j++)
            {
                printf("Matriz C[%d][%d] = [%d] \n", i, j, MatrizC[i][j]);
            }
        }
    }

    MPI_Finalize();
}