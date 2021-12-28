//Librerias necesarias
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


int main(int argc, char **argv){

    const int N = 1000;
    const int ProcRaiz = 0;

    int MiID, TotProcesos;

    int Datos[N];
    int Datos_local[N];

    int i;
    int Block_size;
    int Suma_local;
    int Suma_Total;
    double Tiempo_inicial, Tiempo_final, Tiempo_total;

    //Initializes the MPI execution environment. The variables argc and argv are pointers to command line arguments.
   MPI_Init(  &argc , &argv);
   
   /*Determines the rank of the calling process in a communicator. The rank is an integer value of 0 to n-1, with n being the size of the communicator. 
   This way each process has a unique ID that we can use to communicate messages between processes.*/
   MPI_Comm_rank( MPI_COMM_WORLD , &MiID);
    
    /*Gets the number of processes that are associated with a specific communicator. If MPI_COMM_WORLD is used as the communicator, 
    all the processes on the cluster would be used and stored in the variable of size.*/
   MPI_Comm_size( MPI_COMM_WORLD , &TotProcesos);

   if (MiID == ProcRaiz){
       for (i = 0; i < N; i++){
           Datos[i] = rand()%11;
       }
      printf("\n")
      Tiempo_inicial = MPI_Wtime();
       
   }
    Block_size = N / TotProcesos;
    MPI_Scatter( Datos , Block_size , MPI_INT , Datos_local , Block_size , MPI_INT , ProcRaiz , MPI_COMM_WORLD);

    Suma_local = 0;
    for (i = 0 ; i < Block_size ; i++)
        Suma_local += Datos_local[i];

    printf("Suma local del proceso %d : %d\n", MiID, Suma_local);

    MPI_Reduce(&Suma_local, &Suma_Total, 1, MPI_INT, MPI_SUM, ProcRaiz, MPI_COMM_WORLD);

    if (MiID == ProcRaiz){
        Tiempo_final = MPI_Wtime();
        Tiempo_total = Tiempo_inicial - Tiempo_final;
        printf("Suma total : %d con %d procesos en un tiempo de %f\n", Suma_Total, TotProcesos, Tiempo_total);

    }

    //Terminates the MPI execution environment. The final MPI call that should be made, after it no MPI routines can be called.
    MPI_Finalize();


}