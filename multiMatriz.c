#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    const FilaM1 = 4;
    const ColumM1 = 6;

    const FilaM2 = 6;
    const ColumM2 = 4;
    if (FilaM1 == ColumM2)
    {
        const int ProcRaiz;
        int MiID, TotProcesos;

        int MatrizA[FilaM1][ColumM1];
        int MatrizB[FilaM2][ColumM2];

        int NM = FilaM1 * ColumM2;
        int MatrizC[NM][NM];

        int NumFilas;
        int Block_size;

        int i, j;

        NumFilas = FilaM1 / TotProcesos;
        Block_size = NumFilas * ColumM1;
        
        int MatrizLocal[NumFilas][ColumM2];

        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &MiID);
        MPI_Comm_size(MPI_COMM_WORLD, &TotProcesos);
        if (MiID == ProcRaiz)
        {
            srand(MPI_Wtime());
            for (i = 0; i < FilaM1; i++)
            {
                for (j = 0; j < ColumM1; j++)
                {
                    MatrizA[i][j] = rand() % 11;
                }
            }

            for (i = 0; i < FilaM2; i++)
            {
                for (j = 0; j < ColumM2; j++)
                {
                    MatrizB[i][j] = rand() % 11;
                }
            }
        }

        MPI_Scatter(MatrizA, Block_size, MPI_INT, Vector_localA, Block_size, MPI_INT, ProcRaiz, MPI_COMM_WORLD);
        MPI_Bcast( MatrizB , (FilaM2 * ColumM2) , MPI_INT , 0 , MPI_COMM_WORLD);
        for ( i = 0; i < NumFilas; i++)
        {
            for ( j = 0; j < count; j++)
            {
                
            }
            
        }
        

        MPI_Finalize();
    }
    else
    {
        MPI_Finalize();
    }
}

/**
 * bcast para enviar toda la matriz dos
 *              [1] [1]   [e11][e12]
 * [1] [2] [3]  [2] [2] = [e21][e22]
 * [1] [2] [3]  [3] [3]   
 * 
 * [1] [2] [3]  [1] [1]   [e11][e12]
 * [1] [2] [3]  [2] [2] = [e21][e22]
 * [1] [2] [3]  [3] [3]   [e31][e32]
 * 
 */