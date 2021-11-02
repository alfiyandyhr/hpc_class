#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc,char* argv[])
{
	int N = 1E9;
	int i, id, p, s, g;
	double x,y,etime;
	srand(time(NULL)); /* initialization */
	//clock_t t;

	//t = clock();

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	MPI_Barrier(MPI_COMM_WORLD);
	etime = -MPI_Wtime();

	s = g = 0;
	for(i=id;i<N;i+=p) {
		/* two random numbers 0<x,y<1 */
		x = (double)rand()/RAND_MAX;
		y = (double)rand()/RAND_MAX;
		if( x*x + y*y < 1 ) {
			s = s+1;
		}
	}
	MPI_Reduce(&s,&g,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	if(id==0)
		printf("Process %d is done. pi = %lf\n", id, 4.0*g/N);
	
	MPI_Barrier(MPI_COMM_WORLD);
	etime += MPI_Wtime();
	//t = clock() - t;
	//etime = ((double)t)/CLOCKS_PER_SEC;
	printf("Core %d, Elapsed time = %lf [sec]\n", id, etime);
	MPI_Finalize();
	return 0;
}
