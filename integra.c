#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

double fun(double x1,double x2,double x3,double x4,double x5,double x6,double x7,double x8,double x9,double x10);
double integral_montecarlo(double *x, int _n);
int main(int argc, char **argv)
{
	int n,rank,size,len;
	int N, i, n_puntos,b,a;
	double x1,x2,x3,x4,x5,x6,x7,x8,x9,x10, integral,integralsub;
	double *f;
	char name[80];
	

	double start_time, end_time,computation_time;
	N = atoi(argv[1]);
	n_puntos=N;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	MPI_Get_processor_name(name,&len);
	

	b=1;
	a=0;

		if (rank==0)
		{
			start_time=MPI_Wtime();
		}

		f = malloc(n_puntos*sizeof(double));
	  
		for(i=0; i<n_puntos; i++)
		{
			x1=drand48()*(b-a)+a;
			x2=drand48()*(b-a)+a;
			x3=drand48()*(b-a)+a;
			x4=drand48()*(b-a)+a;
			x5=drand48()*(b-a)+a;
			x6=drand48()*(b-a)+a;
			x7=drand48()*(b-a)+a;
			x8=drand48()*(b-a)+a;
			x9=drand48()*(b-a)+a;
			x10=drand48()*(b-a)+a;
			
			f[i] = fun(x1,x2,x3,x4,x5,x6,x7,x8,x9,x10);
		}

		if(size!=0)
		{
			integralsub = integral_montecarlo(f, n_puntos)/size;

		}
		if(size==0)
		{
			integralsub = integral_montecarlo(f, n_puntos);
		}

		fprintf(stdout, "La integral es : %f del rank: %d en %s\n", integralsub,rank, name);

		MPI_Reduce(&integralsub, &integral, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		if (rank == 0)
		{
			printf("La integral es %.16f con error de %.16f\n", integral,fabs(integral-(155.0/6.0)));
			end_time = MPI_Wtime();
			computation_time = end_time - start_time;		
			printf("El tiempo para calcular la integral es: %f\n", computation_time);
		}


	char buffer[80];
	sprintf(buffer, "integralN%d.txt",N);
	FILE *file = fopen(buffer, "wb");
	fprintf(file, "%f", integral);
	fclose(file);


	MPI_Finalize();


	return 0;
}

double integral_montecarlo(double *x, int _n)
{
	int i;
	double a;
	a = 0.0;
	for(i=0;i<_n;i++)
	{
		a += x[i];
	}
	a = a/(_n-1);
	return a;
}

double fun(double x1,double x2,double x3,double x4,double x5,double x6,double x7,double x8,double x9,double x10)
{
	return (x1+x2+x3+x4+x5+x6+x7+x8+x9+x10)*(x1+x2+x3+x4+x5+x6+x7+x8+x9+x10);
}
