#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(int argc,char* argv[])
{
	int N = 1E9;
	int i,total = 0;
	double x,y;
	srand(time(NULL)); /* initialization */
	clock_t t;

	t = clock();
	for(i=0;i<N;i++) {
		/* two random numbers 0<x,y<1 */
		x = (double)rand()/RAND_MAX;
		y = (double)rand()/RAND_MAX;
		if( x*x + y*y < 1 ) {
			total = total+1;
		}
	}
	printf("pi=%lf \n",4.0*total/N);
	t = clock() - t;
	double etime = ((double)t)/CLOCKS_PER_SEC;
	printf("Elapsed time = %lf\n", etime);
}
