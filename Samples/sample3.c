#include <mpi.h> /* MPI functions */
#include <stdio.h> /* printf */

int main(int argc, char* argv[])
{
	int i, j, id, p;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	printf("Hi from node %d \n", id);
	if(id==0) { /* MPI process 0 */
		for(i=1;i<p;i++) { /* receiving values from the others */
			MPI_Recv( &j, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
			id += j;
		}
		printf("The sum is %d.\n", id);
	}
	else { /* The other processes */
		/* sending data to MPI process 0 */
		MPI_Send( &id, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}
