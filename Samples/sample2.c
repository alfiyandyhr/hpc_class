#include <mpi.h> /* MPI functions */
#include <stdio.h> /* fprintf */
#include <unistd.h> /* usleep */

int check_circuit(int id, int i){/* time-consuming comp.*/
	usleep(1000); /* dummy: sleep 1 msec */
	return i%2; /* 0 for even, 1 for odd (dummy: the output value of the circuit) */
}
int main(int argc, char* argv[])
{
	int i, id, p, s, g;
	double etime;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	printf("Hello from node %d\n", id);
	s = g = 0;
	MPI_Barrier(MPI_COMM_WORLD);
	etime = -MPI_Wtime();

	for(i=id;i<65536;i+=p)
		s+=check_circuit(id, i);
	MPI_Reduce(&s,&g,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	if(id==0)
		fprintf(stderr, "Process %d is done. Total=%d \n", id, g);
	
	MPI_Barrier(MPI_COMM_WORLD);
	etime += MPI_Wtime();
	printf("Elapsed time = %lf [sec]\n", etime);

	MPI_Finalize();
	return 0;
}
