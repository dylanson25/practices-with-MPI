#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv){

    //Nos indica cuantos numeros vamos a cpnsiderar
    const int N = 1000; 
    //Quien es el proceso raiz
    const int ProcRaiz = 0;

    //Variables de mi id y el total de procesos
    int MiID, TotProcesos;

    //Vectores contine los N elementos la utiliza solo elemento raiz
    int VectorA[N];
    int VectorB[N];
    //Datos_local va a contener los elementos locales
    int Vector_localA[N];
    int Vector_localB[N];

    int i;

    //Tamaño de bloque 
    int Block_size;
    //Resusltado del producto escalar local de cada vector
    int Result_producto[N];
    //Suma de los resultados locales
    int Suma_local;
    //suma total del resultado de cada proceso
    int Suma_Total;

    //Variables para tomar el tiempo de procesamiento
    double Tiempo_inicial, Tiempo_final, Tiempo_total;

    //Initializes the MPI execution environment. The variables argc and argv are pointers to command line arguments.
   MPI_Init(  &argc , &argv);
   
   /*Determines the rank of the calling process in a communicator. The rank is an integer value of 0 to n-1, with n being the size of the communicator. 
   This way each process has a unique ID that we can use to communicate messages between processes.*/
   MPI_Comm_rank( MPI_COMM_WORLD , &MiID);
    
    /*Gets the number of processes that are associated with a specific communicator. If MPI_COMM_WORLD is used as the communicator, 
    all the processes on the cluster would be used and stored in the variable of size.*/
   MPI_Comm_size( MPI_COMM_WORLD , &TotProcesos);

    //ver si el proceso actual es el proceso raiz
   if (MiID == ProcRaiz){
      //genera una nueva semilla para que me de numeros aleatorios diferentes cada que se ejecute
      srand(MPI_Wtime());
       //Ciclo que genera numeros aleatorios
       for (i = 0; i < N; i++){
           //numero aleatorio entre 0 y 50
           VectorA[i] = rand()%51;
       }
      srand(MPI_Wtime());
       for (i = 0; i < N; i++){
           //numero aleatorio entre 0 y 50
           VectorB[i] = rand()%51;
       }

      printf("\n");
      //inidica cuando inicio la ejecucion 
      Tiempo_inicial = MPI_Wtime();
       
   }
   //tamaño de los vloques en que se va a dividir la informacion
    Block_size = N / TotProcesos;
    /*si es el proceso raiz envia informacion y recive si no es el proceso raiz 
    envia la informacion a los demas procesos que se guarda en la variable de datos local*/
    MPI_Scatter( VectorA , Block_size , MPI_INT , Vector_localA , Block_size , MPI_INT , ProcRaiz , MPI_COMM_WORLD);
    MPI_Scatter( VectorB , Block_size , MPI_INT , Vector_localB , Block_size , MPI_INT , ProcRaiz , MPI_COMM_WORLD);
    
   //Multiplicacion escalar local
   for ( i = 0; i < Block_size; i++)
   {
       Result_producto[i] = VectorA[i] * VectorB[i]; 
   }
   
   
    //suma los datos locales
    Suma_local = 0;
    for (i = 0 ; i < Block_size ; i++)
        Suma_local += Result_producto[i];
    
    // prueba de suma de cada proceso, su id y su resultado
    printf("Suma local del proceso %d : %d\n", MiID, Suma_local);

    //recolecta la suma local de cada proceso y en este caso la suma y recibe el proceso raiz
    MPI_Reduce(&Suma_local, &Suma_Total, 1, MPI_INT, MPI_SUM, ProcRaiz, MPI_COMM_WORLD);
    

    if (MiID == ProcRaiz){
        //indica el tiempo en el que termino
        Tiempo_final = MPI_Wtime();
        //obtenemos el tiempo que tardo en ejecutarse
        Tiempo_total = Tiempo_inicial - Tiempo_final;
        printf("Suma total : %d con %d procesos en un tiempo de %f\n", Suma_Total, TotProcesos, Tiempo_total);

    }

    //Terminates the MPI execution environment. The final MPI call that should be made, after it no MPI routines can be called.
    MPI_Finalize();


}