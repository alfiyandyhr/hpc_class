#include <mpi.h> /* MPI functions */
#include <stdio.h> /* fprintf */
#include <unistd.h> /* usleep */

int check_circuit(int id, int i){/* time-consuming comp.*/
	usleep(1000); /* dummy: sleep 1 msec */
	return i%2; /* 0 for even, 1 for odd (dummy: the output value of the circuit) */
}
int main(int argc, char* argv[])
{
	int i, id, p, s=0;
	double etime;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	MPI_Barrier(MPI_COMM_WORLD);
	etime = -MPI_Wtime();

	for(i=id;i<65536;i+=p)
		s+=check_circuit(id, i);
	fprintf(stderr, "Process %d is done. Subtotal=%d\n", id, s);
	
	MPI_Barrier(MPI_COMM_WORLD);
	etime += MPI_Wtime();
	MPI_Finalize();

	printf("Elapsed time = %lf [sec] \n", etime);
	return 0;
}
