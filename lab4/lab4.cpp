#include <iostream>
#include <math.h>

#define epsilon 1.0
#define delta 0.1
#define nx 150
#define ny 100
#define Vn1 10.0
#define Vn2 0.0
#define xmax (delta*nx)
#define ymax (delta*ny)
#define sigmax (0.1*xmax)
#define sigmay (0.1*ymax)
#define TOL  pow(10, -6)

using namespace std;

double x(int i) {
	return delta * i;
}

double y(int j) {
	return delta * j;
}

double** setTable(double **tab) {
	for (int i = 0; i <= nx; i++) {
		for (int j = 0; j <= ny; j++) {
			tab[i][j] = 0.0;
		}
	}

	for (int i = 0; i <= nx; i++) {
		tab[i][0] = Vn1;
		tab[i][ny] = Vn2;
	}

	return tab;
}

double **newTable() {
	double **tab;
	tab = new double*[nx+1];
	for (int i = 0; i <= nx; i++) {
		tab[i] = new double[ny+1];
	}

	//tab = setTable(tab);

	return tab;
}

double **cpTable(double **tab) {
	double **temp = newTable();

	for (int i = 0; i <= nx; i++) {
		for (int j = 0; j <= ny; j++) {
			temp[i][j] = tab[i][j];
		}
	}

	return temp;
}

void rmTable(double **tab) {
	for (int i = 0; i <= nx; i++) {
		delete tab[i];
	}

	delete tab;
}

double p1(double x, double y) {
	return exp(-pow(x*delta - 0.35*xmax, 2) / pow(sigmax, 2) - pow(y*delta - 0.5*ymax, 2) / pow(sigmay, 2));
}

double p2(double x, double y) {
	return -1 * exp(-pow(x*delta - 0.65*xmax, 2) / pow(sigmax, 2) - pow(y*delta - 0.5*ymax, 2) / pow(sigmay, 2));
}

double p(double x, double y) {
	return p1(x, y) + p2(x, y);
}

void relaksacjaGlobalna(double wg, FILE * file) {

	double **Vnn = newTable();
	double **Vns = newTable();
    int it = 0;

    for (int i = 0; i <= nx; i++) {
		for (int j = 0; j <= ny; j++) {
			Vnn[i][j] = 0.0;
            Vns[i][j] = 0.0;
		}
	}

    for (int i = 0; i <= nx; i++) {
		Vnn[i][0] = Vn1;
		Vns[i][ny] = Vn2;
	}


	double Sit, Sit_1;
	do {

		for (int i = 1; i < nx; i++) {
			for (int j = 1; j < ny; j++) {
				Vnn[i][j] = (Vns[i + 1][j] + Vns[i - 1][j] + Vns[i][j + 1] + Vns[i][j - 1] +
					(pow(delta, 2)*p(i, j) / epsilon)) / 4.0;
			}
		}

		for (int j = 1; j <= ny; j++) {
			Vnn[0][j] = Vnn[1][j];
			Vnn[nx][j] = Vnn[nx - 1][j];
		}

		for (int i = 0; i <= nx; i++) {
			for (int j = 0; j < ny; j++) {
				Vns[i][j] = (1 - wg)*Vns[i][j] + wg * Vnn[i][j];
			}
		}

		Sit_1 = Sit;
		Sit = 0;
		for (int i = 0; i < nx; i++) {
			for (int j = 0; j < ny; j++) {
				Sit += pow(delta, 2)*(pow((Vnn[i + 1][j] - Vnn[i][j]) / delta, 2) / 2
					+ pow((Vnn[i][j + 1] - Vnn[i][j]) / delta, 2) / 2 - p(i, j)*Vnn[i][j]);


			}
		}
        //cout<<it<<endl;
    ++it;
    fprintf(file, "%d %f\n", it, Sit);
	} while (fabs((Sit - Sit_1) / Sit_1) > TOL);


	rmTable(Vnn);
	rmTable(Vns);
}

void relaksacjaLokalna(double wl, FILE * file) {

    

	double **Vn = newTable();


    for (int i = 0; i <= nx; i++) {
		for (int j = 0; j <= ny; j++) {
			Vn[i][j] = 0.0;
           
		}
	}

    for (int i = 0; i <= nx; i++) {
		Vn[i][0] = Vn1;
		
	}
	double Sit = 1, Sit_1;
    int it =0;
	do {

		for (int i = 1; i <= nx - 1; i++) {
			for (int j = 1; j <= ny - 1; j++) {
				Vn[i][j] = (1 - wl)*Vn[i][j] + wl * (Vn[i + 1][j] +
					Vn[i - 1][j] + Vn[i][j + 1] + Vn[i][j - 1] + (pow(delta, 2)*p(i, j)) / epsilon) / 4;
			}
		}

		for (int j = 1; j < ny; j++) {
			Vn[0][j] = Vn[1][j];
			Vn[nx][j] = Vn[nx - 1][j];
		}

		Sit_1 = Sit;
		Sit = 0;
		for (int i = 0; i < nx - 1; i++) {
			for (int j = 0; j < ny - 1; j++) {
				Sit += pow(delta, 2)*(pow((Vn[i + 1][j] - Vn[i][j]) / delta, 2) / 2 +
					pow((Vn[i][j + 1] - Vn[i][j]) / delta, 2) / 2 - p(i, j)*Vn[i][j]);
			}
		}
    ++it;
    fprintf(file, "%d %f\n", it, Sit);
	} while (fabs((Sit - Sit_1) / Sit_1) > TOL);

	rmTable(Vn);
}

int main() {
    FILE * file;
    //file = fopen("relaksacjaglobalna1", "w");
    //relaksacjaGlobalna(0.6, file);
    //fclose(file);
    file = fopen("relaksacjalokalna1", "w");
    relaksacjaLokalna(1.0, file);
    fclose(file);
	return 0;
}