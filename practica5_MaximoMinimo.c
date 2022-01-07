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
    int N = 1000;
    int ProcRaiz = 0;
    int i;

    int MaximoLocal;

    double Tiempo_inicial, Tiempo_final, Tiempo_total;

    int MiID, TotProcesos;

    MPI_Init( &argc , &argv);
    MPI_Comm_rank( MPI_COMM_WORLD , &MiID);
    MPI_Comm_size(MPI_COMM_WORLD, &TotProcesos);

    int Block_size = N / TotProcesos;
    int Vector_local[Block_size];
    
    if((N % TotProcesos) == 0){
        int VectorA[N];

        srand(MPI_Wtime());
        for ( i = 0; i < N; i++)
            VectorB[i] = rand()%101;
        
        Tiempo_inicial = MPI_Wtime();
        MPI_Scatter( VectorA , Block_size , MPI_INT , Vector_local , Block_size , MPI_INT , ProcRaiz , MPI_COMM_WORLD);
    }
    
    MaximoLocal = 0;
    for ( i = 0; i < Block_size; i++){
       MaximoLocal = MaximoLocal < Vector_local[i] ? Vector_local[i] : MaximoLocal; 
    }

    printf("Maximo local del proceso %d : %d\n", MiID, MaximoLocal);

    MPI_Reduce(&MaximoLocal, &MaximoLocal, 1, MPI_INT, MPI_MAX, ProcRaiz, MPI_COMM_WORLD);

    if(MiID == ProcRaiz){
        Tiempo_final = MPI_Wtime();
        Tiempo_total = Tiempo_final - Tiempo_inicial;
        printf("Maximo total : %d con %d procesos en un tiempo de %f\n", Suma_Total, TotProcesos, Tiempo_total);
    }

    
}