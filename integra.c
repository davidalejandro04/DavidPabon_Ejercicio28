#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

double fun(double x);
double integral_montecarlo(double *x, int _n);
int main(int argc, char **argv)
{
	int n,rank,size,len;
	int N, i, n_puntos;
	double x, integral,integralsub;
	double *f;
	double INTEGRAL_VALOR=0.5;
	char name[80];

	double start_time, end_time,computation_time;
	N = atoi(argv[1]);
	n_puntos=N;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	MPI_Get_processor_name(name,&len);



		if (rank==0)
		{
			start_time=MPI_Wtime();
		}

		f = malloc(n_puntos*sizeof(double));
	  
		for(i=0; i<n_puntos; i++)
		{
			f[i] = fun(drand48());
		}

		integralsub = integral_montecarlo(f, n_puntos);

		fprintf(stdout, "La integral es : %f del rank: %d en %s\n", integralsub,rank, name);

		MPI_Reduce(&integralsub, &integral, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		if (rank == 0)
		{
			printf("La integral es %.16f con error de %.16f\n", integral,(INTEGRAL_VALOR-integral));
			end_time = MPI_Wtime();
			computation_time = end_time - start_time;		
			printf("El tiempo para calcular la integral es: %f\n", computation_time);
		}



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
	a = a/_n;
	return a;
}

double fun(double x)
{
	return (x);
}
