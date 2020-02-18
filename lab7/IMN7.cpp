#include <iostream>
#include <math.h>

#define delta 0.01
#define ro 1
#define mi 1
#define nx 200
#define ny 90
#define i1 50
#define j1 55
#define itmax 20000

double y(int j){
	return delta * j;
}


void wbPsi(double Qwe, double Qwy, double psi[nx + 1][ny + 1]) {
	//A
	for (int j = j1; j <= ny; ++j) {
        psi[0][j] = Qwe/(2*mi) *(pow(y(j),3)/3 - pow(y(j),2)/2*(y(j1)+y(ny))+y(j)*y(j1)*y(ny));
	}
	//C
	for (int j = 0; j <= ny; ++j) {
        psi[nx][j] = Qwy/(2*mi) * (pow(y(j),3)/3 - pow(y(j),2)/2*y(ny)) + Qwe*pow(y(j1),2)*(-y(j1)+3*y(ny))/(12*mi);
	}

	//B
	for (int i = 1; i < nx; ++i) {
		psi[i][ny] = psi[0][ny];
	}
	//D
	for (int i = i1; i < nx; ++i) {
		psi[i][0] = psi[0][j1];
	}
	//E
	for (int j = 1; j <= j1; ++j) {
		psi[i1][j] = psi[0][j1];
	}
	//F
	for (int i = 1; i <= i1; ++i) {
		psi[i][j1] = psi[0][j1];
	}
}

void wbDzeta(double Qwe, double Qwy, double psi[nx+1][ny+1], double dzeta[nx + 1][ny + 1]) {
	//A
	for (int j = j1; j <= ny; ++j) {
        dzeta[0][j] = Qwe/2*mi *(2*y(j)-y(j1)-y(ny));
	}
	//C
	for (int j = 0; j <= ny; ++j) {
        dzeta[nx][j] = Qwy/2*mi *(2*y(j) - y(ny));
	}
	//B
	for (int i = 1; i < nx; ++i) {
		dzeta[i][ny] = 2 / pow(delta, 2) * (psi[i][ny - 1] - psi[i][ny]);
	}
	//D
	for (int i = i1; i < nx; ++i) {
		dzeta[i][0] = 2 / pow(delta, 2) * (psi[i][1] - psi[i][0]);
	}
	//E
	for (int j = 1; j <= j1; ++j) {
		dzeta[i1][j] = 2 / pow(delta, 2) * (psi[i1 + 1][j] - psi[i1][j]);
	}
	//F
	for (int i = 1; i <= i1; ++i) {
		dzeta[i][j1] = 2 / pow(delta, 2) * (psi[i][j1 + 1] - psi[i][j1]);
	}
	//E/F
	dzeta[i1][j1] = (dzeta[i1 - 1][j1] + dzeta[i1][j1 - 1]) / 2;

}

void ns(double Q, FILE * fpsi, FILE * fdzeta, FILE * fu, FILE * fv) {
	double psi[nx + 1][ny + 1];
	double dzeta[nx + 1][ny + 1];
    double u[nx + 1][ny + 1];
	double v[nx + 1][ny + 1];

    for(int i = 0; i <= nx; i++){
            for(int j = 0; j <= ny; j++){
               psi[i][j] = 0;
               dzeta[i][j] = 0;
               u[i][j] = 0;
               v[i][j] = 0;
            }
        }


    double Qwy = Q * (pow(y(ny),3)-pow(y(j1),3)-3*y(j1)*pow(y(ny),2)+3*pow(y(j1),2)*y(ny))/pow(y(ny),3);
	wbPsi(Q, Qwy, psi);
	int omega;
	for (int it = 0; it < itmax; ++it) {
		if (it < 2000) {
			omega = 0;
		}
		else {
			omega = 1;
		}
		for (int i = 1; i < nx; ++i) {
			for (int j = 1; j < ny; ++j) {
				if (i > i1  or j > j1 ) {
					psi[i][j] = (psi[i + 1][j] + psi[i - 1][j] + psi[i][j + 1] + psi[i][j - 1] - pow(delta, 2)*dzeta[i][j]) / 4.0;
					dzeta[i][j] = (dzeta[i + 1][j] + dzeta[i - 1][j] + dzeta[i][j + 1] + dzeta[i][j - 1] - pow(delta, 2)*dzeta[i][j]) / 4.0 - (omega*ro) / (16 * mi)*((psi[i][j + 1] - psi[i][j - 1])*(dzeta[i + 1][j] - dzeta[i - 1][j]) - (psi[i + 1][j] - psi[i - 1][j])*(dzeta[i][j + 1] - dzeta[i][j - 1]));
				}
			}
		}
		wbDzeta(Q, Qwy, psi, dzeta);
		int j2 = j1 + 2;
		double gamma = 0;
		for (int i = 1; i < nx; ++i) {
			gamma += (psi[i + 1][j2] + psi[i - 1][j2] + psi[i][j2 + 1] + psi[i][j2 - 1] - 4 * psi[i][j2] - pow(delta, 2)*dzeta[i][j2]);
		}

	}

        for(int i = 0; i <= nx; i++){
            for(int j = 0; j <= ny; j++){
                fprintf(fpsi, "%f %f %f \n", delta*i, delta*j, psi[i][j]);
            }
            fprintf(fpsi, "\n");
        }
        for(int i = 0; i <= nx; i++){
            for(int j = 0; j <= ny; j++){
                fprintf(fdzeta, "%f %f %f \n", delta*i, delta*j, dzeta[i][j]);
            }
            fprintf(fdzeta, "\n");
        }
        for(int i = 0; i <= nx; i++){
            for(int j = 0; j < ny; j++){
                u[i][j] = (psi[i][j+1]-psi[i][j])/delta;
                fprintf(fu, "%f %f %f \n", delta*i, delta*j, u[i][j]);
            }
            fprintf(fu, "\n");
        }
        for(int i = 0; i < nx; i++){
            for(int j = 0; j <= ny; j++){
                v[i][j] = (-psi[i+1][j]+psi[i][j])/delta;
                fprintf(fv, "%f %f %f \n", delta*i, delta*j, v[i][j]);
            }
            fprintf(fv, "\n");
        }
}




int main() {
	FILE * psi = fopen("zad1psi.dat", "w");
	FILE * dzeta = fopen("zad1dzeta.dat", "w");
	FILE * u = fopen("zad1u.dat", "w");
	FILE * v = fopen("zad1v.dat", "w");
	ns(-1000, psi, dzeta, u, v);

	psi = fopen("zad2psi.dat", "w");
	dzeta = fopen("zad2dzeta.dat", "w");
	u = fopen("zad2u.dat", "w");
	v = fopen("zad2v.dat", "w");
	ns(-4000, psi, dzeta, u, v);

	psi = fopen("zad3psi.dat", "w");
	dzeta = fopen("zad3dzeta.dat", "w");
	u  = fopen("zad3u.dat", "w");
	v  = fopen("zad3v.dat", "w");
	ns(4000, psi, dzeta, u, v);	

	fclose(psi);
	fclose(dzeta);
	fclose(u);
	fclose(v);
	return 0;
}