#include <stdio.h>
#include <mpi.h>

int main (int argc, char** argv){

    int n, m, source, p;

    MPI_Status status;
    MPI_Init (&argc, &argv);
    MPI_Comn_rank(MPI_COMM_WORLD, &n);//id del proceso
    MPI_Comn_size(MPI_COMM_WORLD, &m);//cuntos procesos
    /** 
     * MPI_Send( const void* buf , int count , MPI_Datatype datatype , int dest , int tag , MPI_Comm comm);
     *  buf => Dirección inicial del buffer de envío. Esto significa que requiere un puntero. Si
        solo se pretende enviar un elemento, se puede enviar el puntero a este
        (&elemento).
     *  count => Numero de elementos a enviar
     *  datatype => tipo de dato de cada elemento a enviar
     *  dest => Numero de procesos destino
     *  tag => entero que representa la etiqueta del mensaje
     *  comm => comunicador utilizado para la comunicación
     * ----------------------------------------------------
     * MPI_send(&m, 1, MPI_INT, 1, 100, MPI_COMM_WORLD);
     * m => la direcion de envio en este caso seria a los demas procesadores
     * 1 => un elemento sera enviado
     * MPI_INT => el elemento enviado es un entero
     * 1 => el proceso destino es el 1
     * 100 => 100 es la representacion de la etiqueta de este mensaje
     * MPI_COMM_WORLD => comunicador utilizado para la comunicación
    */
   /** 
    * MPI_Recv( void* buf , int count , MPI_Datatype datatype , int source , int tag , MPI_Comm comm , MPI_Status* status);
    * Count => Entero que indica el numero máximo de elementos que se espera recibir en el buffer de entrada
    * Datatype => tipo de dato de cada elemento de origen que se va a recibir
    * Source => Numero del proceso origen esperado, solo acepta mensajes cuyo origen sea el especificado
    * tag => entero que representa la etiqueta del mensaje
    * comm => comunicador utilizado para la comunicación
    * Status => Objeto de tipo MPI_Status contiene datos relevantes sobre el mensaje
    * ---------------------------------------------------------------------------------
    *  MPI_Recv( &p , 1 , MPI_INT, 0 , 100 , MPI_COMM_WORLD , &status);
    * p => indica el numero maximo de elementos que se espera recibir en el buffer de entrada en este caso seria 4
    * 1 => no se
    * MPI_INT => el dato enviado es un entero
    * 0 => el proceso o es el proceso origen
    * MPI_COMM_WORLD => comunicador que se usara 
    * status => objeto con los datos relevantes sobre el mensaje
   */
    if(n==0) MPI_send(&m, 1, MPI_INT, 1, 100, MPI_COMM_WORLD);
    else MPI_Recv( &p , 1 , MPI_INT, 0 , 100 , MPI_COMM_WORLD , &status);

    printf("%d", p);
    MPI_Finalize();
/*teoricamente y por lo que entiendo al analizar el codigo es que p es el numero maximo que van a recibir 
el mensaje por lo tanto en este caso seria 4 que son los procesadores a usar
*/
}