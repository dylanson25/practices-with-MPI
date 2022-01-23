/**
 * @file SumaMatrizes.c
 * Este es un ejemplo para practicar con la libreria de mpi
 */
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv)
{

    const int N = 4;// Filas
    const int M = 3;// Columnas

    //Quien es el proceso raiz
    const int ProcRaiz = 0;

    /*MiID  = Indica el proceso actual 
      TotProcesos = procesos totales*/
    int MiID, TotProcesos;
    
    //Matrises a operar
    int MatrizA[N][M];
    int MatrizB[N][M];

    //Resultado de la operacion entre matrices
    int MatrizC[N][M];

    //Matriz con los valores locales
    int Vector_localA[N][M];
    int Vector_localB[N][M];

    //Filas que operara cada proceso
    int NumFilas;

    //Tamaño de bloque que se le proporcionara a cada proceso
    int Block_size;
    
    //Matriz con el resultado de la operación
    int Vector_localC[M][M];
    

    //variables para los ciclos
    int i;
    int j;
    
   
    /** Ejemplo;
     * Matriz 4 x 3 con 2 procesos
     * NumFilas = 4 / 2 = 2
     * Block_size = 2 * 3 = 6
     * Tamaño de bloque = 6 
     */

    double Tiempo_inicial, Tiempo_final, Tiempo_total;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &MiID);

    MPI_Comm_size(MPI_COMM_WORLD, &TotProcesos);

     //filas entre el total de procesos
    NumFilas = N/TotProcesos;
    
    //Tamaño de bloque es igual numero de filas por cantidad de columnas
    Block_size = NumFilas * M;

    //Llenado de las matrizes
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

    MPI_Scatter(MatrizA, Block_size, MPI_INT, Vector_localA, Block_size, MPI_INT, ProcRaiz, MPI_COMM_WORLD);
    MPI_Scatter(MatrizB, Block_size, MPI_INT, Vector_localB, Block_size, MPI_INT, ProcRaiz, MPI_COMM_WORLD);

    for ( i = 0; i < NumFilas; i++)
    {   
        for ( j = 0; j < M; j++)
        {
            Vector_localC [i][j] = Vector_localA[i][j] + Vector_localB[i][j]; 
            printf("Vector local [%d][%d] = %d del proceso %d\n", i, j, Vector_localC[i][j], MiID);
        }
        
    }
    
    MPI_Gather(Vector_localC, Block_size, MPI_INT, MatrizC, Block_size, MPI_INT, ProcRaiz, MPI_COMM_WORLD);
    /** MPI_Gather
     * Recolecta bloques de datos de todos los procesos de un comunicador hacia el modo raiz
     * MPI_Gather(void *sendbuf, int sendcount, MPI_Datatype sendtype, void*recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
     * sendbuf - Direccion de inicio donde estan los datos a enviar
     * sendcount - Numero de elementos enviados a cada proceso
     * sendtype - Tipo de dato de los elementos enviados
     * recvbuf direccion de inicio donde se guardan los datos recibidos
     * recvcount - numero de elementos recibidos
     * recevtype -Tipo de dato de los elementos recividos 
     * root - Proceso raiz
     * comm - Comunicador
     */

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
        printf("Tiempo total %f", Tiempo_total);
    }

    MPI_Finalize();
}