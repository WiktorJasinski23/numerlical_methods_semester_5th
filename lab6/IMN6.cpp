#include <iostream>
#include <math.h>
#include "mgmres.h"

#define N ((nx+1)*(ny+1))
#define sig  xmax / 10.0
#define delta 0.1



int j(int nx, int l) {
	return (l / (nx + 1));
}

int i(int nx, int l) {
	return l - j(nx, l)*(nx + 1);
}

int epsl(int x, int l, int eps1, int eps2) {
	if (i(x, l) <= x / 2)
		return eps1;
	else
		return eps2;
}


double ro1(double x, double y, double xmax, double ymax) {
	return exp(-1 * pow(x - 0.25*xmax, 2) / pow(sig, 2) - pow(y - 0.5*ymax, 2) / pow(sig, 2));
}

double ro2(double x, double y, double xmax, double ymax) {
	return -1 * exp(-1 * pow(x - 0.75*xmax, 2) / pow(sig, 2) - pow(y - 0.5*ymax, 2) / pow(sig, 2));
}

double ro(double x, double y, double xmax, double ymax) {
	return 0.0;
}



int nzNum( double(*fun1)(double arg, double arg2, double arg3, double arg4), double(*fun2)(double arg, double arg2, double arg3, double arg4),int nx, int ny, double xmax, double ymax, int eps1, int eps2, double V1, double V2, double V3, double V4,
	int *ja, int *ia, double *a, double *b, FILE * vector, FILE * matrix) {
	int k = -1;
	for (int l = 0; l < N; ++l) {
		int brzeg = 0;
		double vb = 0;

		if (i(nx, l) == 0) {
			brzeg = 1;
			vb = V1;
		}
		else if (j(nx, l) == ny) {
			brzeg = 1;
			vb = V2;
		}
		else if (i(nx, l) == nx) {
			brzeg = 1;
			vb = V3;
		}
		else if (j(nx, l) == 0) {
			brzeg = 1;
			vb = V4;
		}

		b[l] = -(fun1(delta*i(nx, l), delta*j(nx, l), xmax, ymax) + fun2(delta*i(nx, l), delta*j(nx, l), xmax, ymax));

		if (brzeg == 1) {
			b[l] = vb;
		}

		ia[l] = -1;

		// lewa skrajna przekatna
		if (l - nx - 1 > 0 && brzeg == 0) {
			++k;
			if (ia[l] < 0)
				ia[l] = k;
			a[k] = epsl(nx, l, eps1, eps2) / pow(delta, 2);
			ja[k] = l - nx - 1;
		}

		// poddiagonala
		if (l - 1 >= 0 && brzeg == 0) {
			++k;
			if (ia[l] < 0)
				ia[l] = k;
			a[k] = epsl(nx, l, eps1, eps2) / pow(delta, 2);
			ja[k] = l - 1;
		}

		// diagonala
		++k;
		if (ia[l] < 0)
			ia[l] = k;
		if (brzeg == 0)
			a[k] = -(2 * epsl(nx, l, eps1, eps2) + epsl(nx, l + 1, eps1, eps2) + epsl(nx, l + nx + 1, eps1, eps2)) / pow(delta, 2);
		else
			a[k] = 1;
		ja[k] = l;

		// naddiagonala
		if (l < N && brzeg == 0) {
			++k;
			a[k] = epsl(nx, l + 1, eps1, eps2) / pow(delta, 2);
			ja[k] = l + 1;
		}

		// prawa skrajna przekątna
		if (l < (N - nx - 1) && brzeg == 0) {
			++k;
			a[k] = epsl(nx, l + nx + 1, eps1, eps2) / pow(delta, 2);
			ja[k] = l + nx + 1;
		}
	    
        fprintf(vector,"%d %d %d %f \n", l, i(nx,l), j(nx,l), b[l]);

		
	}
	int nz_num = k + 1;
	ia[N] = nz_num;
	    
	for(int i = 0; i < 5*N; ++i)
        fprintf(matrix,"%d %f \n", i, a[i]);

	return nz_num;
}

void algebPoisson(double(*fun1)(double arg, double arg2, double arg3, double arg4),double(*fun2)(double arg, double arg2, double arg3, double arg4),int nx, int ny, double xmax, double ymax, int eps1, int eps2, int V1, int V2, int V3, int V4, FILE * vector, FILE * matrix, FILE * map = NULL) {

	double *a = new double[5 * N];
	int *ja = new int[5 * N];
	int *ia = new int[N + 1];
	double *b = new double[N];
	double *V = new double[N];

	for(int i =0; i <N; ++i){
		V[i] = 0;
	}

	for(int i =0; i <N; ++i){
		ia[i] = -1;
	}

	int nz_num = nzNum(fun1, fun2, nx, ny, xmax, ymax, eps1, eps2, V1, V2, V3, V4, ja, ia, a, b, vector, matrix);

	pmgmres_ilu_cr(N, nz_num, ia, ja, a, V, b, 500, 500, pow(10, -8), pow(10, -8));

	if (map) {
		double tmp = 0.;
		for (int z = 0; z < N; ++z) {
			if (delta*j(nx, z) > tmp)
				fprintf(map, "\n");
			fprintf(map, "%f %f %f \n", delta*j(nx, z), delta*i(nx, z), V[z]);
			tmp = delta * j(nx, z);
		}
	}

	delete[] a;
	delete[] ia;
	delete[] ja;
	delete[] b;
	delete[] V;

}



int main() {
	int nx = 4, ny = 4;
	int eps1 = 1, eps2 = 1;
	int V1 = 10, V3 = 10, V2 = -10, V4 = -10;
	double xmax = 0, ymax = 0;

	FILE * matrix = fopen("tmp_matrix.dat", "w");
	FILE * vector = fopen("tmp_vector.dat", "w");
	algebPoisson(ro,ro,nx, ny, xmax, ymax, eps1, eps2, V1, V2, V3, V4, vector, matrix);
	fclose(matrix);
	fclose(vector);


	nx = 50;
	ny = 50;
	matrix = fopen("vector.dat", "w");
	vector = fopen("matrix.dat", "w");
	FILE * map = fopen("map1a.dat", "w");
	algebPoisson(ro, ro, nx, ny, xmax, ymax, eps1, eps2, V1, V2, V3, V4, vector, matrix, map);
	fclose(map);

	nx = 100;
	ny = 100;

	map = fopen("map1b.dat", "w");
	algebPoisson(ro, ro, nx, ny, xmax, ymax, eps1, eps2, V1, V2, V3, V4, vector, matrix, map);
	fclose(map);

	nx = 200;
	ny = 200;

	map = fopen("map1c.dat", "w");
	algebPoisson(ro, ro, nx, ny, xmax, ymax, eps1, eps2, V1, V2, V3, V4, vector, matrix, map);
	fclose(map);

	nx = 100;
	ny = 100;
	V1 = V2 = V3 = V4 = 0;
	xmax = delta * nx;
	ymax = delta * ny;


	map = fopen("map2a.dat", "w");
	algebPoisson(ro1, ro2, nx, ny, xmax, ymax, eps1, eps2, V1, V2, V3, V4, vector, matrix, map);
	fclose(map);


	eps1 = 1;
	eps2 = 2;

	map = fopen("map2b.dat", "w");
	algebPoisson(ro1, ro2, nx, ny, xmax, ymax, eps1, eps2, V1, V2, V3, V4, vector, matrix, map);
	fclose(map);


	eps1 = 1;
	eps2 = 10;
	map = fopen("map2c.dat", "w");
	algebPoisson(ro1, ro2, nx, ny, xmax, ymax, eps1, eps2, V1, V2, V3, V4, vector, matrix, map);
	fclose(map);

	fclose(matrix);
	fclose(vector);
}