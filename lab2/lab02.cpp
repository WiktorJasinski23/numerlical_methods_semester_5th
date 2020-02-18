#include <iostream>
#include<math.h>

using namespace std;

int main(){

//////////////////////////////////METODA TRAPEZÓW///////////////////
	double u0 = 1.0;
	double beta = 0.001;
	double N = 500;
	double gamma = 0.1;
	double tmax = 100;
	double deltat = 0.1;
	double TOL = 0.00001;
	int mimax = 20;
	double alfa = beta * N - gamma;
//////////////////////////////////METODA PICKARDA///////////////////
	double un, un_1;
	un = u0;
	
	FILE *fp = fopen("pickard.dat", "w");
	for (double n = 0; n <= tmax; n = n + deltat) {
		un_1 = un;
		fprintf(fp, "%g %g %g\n", n, un_1, N-un_1);
		for (int mi = 1; mi <= mimax; ++mi) {
			double temp = un_1;
			un_1 = un + (deltat / 2.0)*((alfa*un - beta * un*un) + (alfa*un_1 - beta * un_1*un_1));
			if ((un_1 - temp) < TOL) {
				break;
			}
		}
		un = un_1;
	}
	fclose(fp);

//////////////////////////////////METODA NEWTONA///////////////////

	un = u0;

	FILE *fp2 = fopen("newton.dat", "w");
	for (double n = 1; n <= tmax; n = n + deltat) {
		un_1 = un;
		fprintf(fp2, "%g %g %g\n", n, un_1, N - un_1);
		for (int mi = 0; mi <= mimax; ++mi) {
			double temp = un_1;
			un_1 = un_1 - (un_1 - un - (deltat / 2.0)*((alfa*un - beta * un*un) + (alfa*un_1 - beta * un_1*un_1))) / (1 - (deltat / 2.0)*(alfa - 2 * beta*un_1));
			if ((un_1 - temp) < TOL) {
				break;
			}
		}
		un = un_1;
	}
	fclose(fp2);
    //////////////////////////////////NIEJAWNA METODA RK2///////////////////

    un = u0;
    FILE *fp3 = fopen("rk2.dat", "w");
    double a11 = 0.25;
    double a12 = 0.25 - sqrt(3.0)/6.0;
    double a21 = 0.25 + sqrt(3.0)/6.0;
    double a22 = 0.25;
    double b1 = 0.5;
    double b2 = 0.5;
    //double c1 = 0.5 - sqrt(3.0)/6.0;
    //double c2 = 0.5 + sqrt(3.0)/6.0;
    double U1 = un;
    double U2 = un;

	for (double n = 1; n <= tmax; n = n + deltat) {
		un_1 = un;
        //int iter = 0;
		fprintf(fp3, "%g %g %g\n", n, un_1, N - un_1);
		for (int mi = 0; mi <= mimax; ++mi) {
            //iter++;
            double F1 = U1 - un - deltat*(a11*(alfa*U1-beta*U1*U1)+a12*(alfa*U2-beta*U2*U2));
            double F2 = U2 - un - deltat*(a21*(alfa*U1-beta*U1*U1)+a22*(alfa*U2-beta*U2*U2));            
            double m11 = 1 - deltat*a11*(alfa-2*beta*U1);
            double m12 = -(deltat*a12*(alfa-2*beta*U2));
            double m21 = -(deltat*a21*(alfa-2*beta*U1));
            double m22 = 1 - deltat*a22*(alfa-2*beta*U2);
            double deltau1 = (F2*m12 - F1*m22)/(m11*m22-m12*m21);
            double deltau2 = (F1*m21 - F2*m11)/(m11*m22 - m12*m21);  
            U1 = U1 + deltau1;
            U2 = U2 + deltau2;
			if (deltau1 < TOL && deltau2 < TOL) {
				break;
			}
		}
		//std::cout<<"liczba iteracji to: "<<iter<<std::endl;
        un_1 = un + deltat*(b1*((beta*N-gamma)*U1 - beta * U1*U1)+b2*((beta*N-gamma)*U2- beta*U2*U2));
		un = un_1;
	}
	fclose(fp3);
}