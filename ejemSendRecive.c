#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv){
    int Mi_ID, Proc_tot;
    int Origen, Etiqueta=100;
    MPI_Status status;

    //Inicializar el entorno de MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &Mi_ID);
    MPI_Comm_size(MPI_COMM_WORLD, &Proc_tot);

    //Codigo
    MPI_Send(&Mi_ID, 1, MPI_INT, (Mi_ID+1)%Proc_tot, Etiqueta, MPI_COMM_WORLD);
    //Si Mi_ID = 0 y Proc_tot = 5, (Mi_ID+1)%Proc_tot=(0+1)%5=1
    /*
     * Mi_ID => direccion de memoria de Mi_ID, variable a enviar
     * 1 => Se enviara un elemento
     * MPI_Int => elemento entero
     * (Mi_ID+1)%Proc_tot => a quien se lo vamos a enviar
     * Etiqueta => identificador del mensaje
     * MPI_COMM_WORLD => comunicador que se va a usar
    */
    MPI_Send(&Origen, 1, MPI_INT, MPI_ABY_SOURCE, Etiqueta, MPI_COMM_WORLD, &status);
    /** 
     * Origen => direccion de memoria donde va a almacenar las cosas
     * 1 => un elemento 
     * MPI_Int => Entero
     * MPI_INT, MPI_ABY_SOURCE => cualquiera
     * Etiqueta => en este caso es 100
     * MPI_COMM_WORLD => comunicador que se va a usar
     * 
    */

    printf('Soy el proceso %d, recibi mensaje de %d\n', Mi_ID, Origen);

    MPI_Finalize();
}