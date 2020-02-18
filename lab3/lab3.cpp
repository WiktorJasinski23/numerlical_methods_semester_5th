#include <iostream>
#include <math.h>
#include <algorithm>

#define x0 0.01
#define v0 0.0
#define dt0 1.0
#define S 0.75
#define p 2.0

using namespace std;

struct para {
	double x;
	double v;
};

double f(double vn) {
	return vn;
}

double g(double xn, double vn, double alfa) {
	return (alfa*(1.0 - xn * xn)*vn - xn);
}


para rk2(double xn, double vn, double dt, double alfa) {
	double k1x = f(vn);
	double k1v = g(xn, vn, alfa);

	double k2x = f(vn + dt*k1v);
	double k2v = g(xn + dt * k1x, vn + dt * k1v, alfa);

	para par;

	par.x = xn + (dt / 2.0) * (k1x + k2x);
	par.v = vn + (dt / 2.0) * (k1v + k2v);

	return par;
}

double F_F(double xn1, double xn, double vn1, double vn, double dt) {
	return xn1 - xn - (dt / 2.0)*(f(vn) + f(vn1));
}

double G_G(double xn1, double xn, double vn1, double vn, double dt, double alfa) {
	return vn1 - vn - (dt / 2.0)*(g(xn, vn, alfa) + g(xn1, vn1, alfa));
}

para trapez(double xn, double vn, double dt, double alfa) {
	double dx = 0.0;
	double dv = 0.0;
	double xn1 = xn;
	double vn1 = vn;

	double delta = pow(10, -10);
	do { 
        dx = 0.0;
        dv = 0.0;

		double a11 = 1.0;
		double a12 = -dt / 2.0;
		double a21 = -(dt / 2.0) * (-2.0 * alfa*xn1*vn1 - 1.0);
		double a22 = 1 - (dt / 2.0)*alfa*(1 - pow(xn1, 2.0));

		dx = (((-1)*F_F(xn1, xn, vn1, vn, dt))*a22 - ((-1)*G_G(xn1,xn,vn1,vn,dt, alfa))*a12) / (a11 * a22 - a12 * a21);

		dv = (a11*((-1)*G_G(xn1, xn, vn1, vn, dt, alfa)) - a21 * ((-1)*F_F(xn1, xn, vn1, vn, dt))) / (a11*a22 - a12 * a21);

		xn1 = xn1 + dx;
		vn1 = vn1 + dv;
        //cout<<dx<<" "<<dv<<endl;
	} while (fabs(dx) > delta and fabs(dv) > delta);

	para par;

	par.x = xn + (dt / 2.0)*(f(vn) + f(vn1));
	par.v = vn + (dt / 2.0)*(g(xn, vn, alfa) + g(xn1, vn1, alfa));

	return par;

}
void krokCzasowy(FILE * file, para(*schemat_numeryczny)(double xn, double vn, double dt, double alfa), double TOL) {
	double alfa = 5.0;

	double t = 0.0;
	double  dt = dt0;
	double xn = x0;
	double vn = v0;
	double tmax = 40.0;

	double Ex = 0.0;
	double Ev = 0.0;
	para tmp1;
	para tmp2;

	fprintf(file, "%f %f %f %f \n", t, dt, xn, vn);
	do {
		
		tmp2 = schemat_numeryczny(xn, vn, dt, alfa);
		tmp2 = schemat_numeryczny(tmp2.x, tmp2.v, dt, alfa);

		tmp1 = schemat_numeryczny(xn, vn, 2.0 * dt, alfa);

		Ex = (tmp2.x - tmp1.x) / (pow(2.0, p) - 1.0);
		Ev = (tmp2.v - tmp1.v) / (pow(2.0, p) - 1.0);

		if (std::max(fabs(Ex), fabs(Ev)) < TOL) {
			t = t + 2.0 * dt;
			xn = tmp2.x;
			vn = tmp2.v;
			fprintf(file, "%f %f %f %f \n", t, dt, xn, vn);

		}
		dt = (pow(S*TOL / (std::max(fabs(Ex), fabs(Ev))), (1.0 / (p + 1.0)))*dt);
        //cout<<dt<<endl;

	} while (t < tmax);

}




int main() {

	FILE * file;

	////////////////rk2/////////////////////

	file = fopen("RK2.dat", "w");

	double TOL = pow(10.0, -2.0);
	krokCzasowy(file, rk2, TOL);

	fclose(file);

	file = fopen("RK22.dat", "w");

	TOL = pow(10, -5);
	krokCzasowy(file, rk2 ,TOL);

	fclose(file);


	/////////////metoda trapezow////////////

	file = fopen("trapezy.dat", "w");

	TOL = pow(10, -2);
	krokCzasowy(file, trapez, TOL);

	fclose(file);
	

	file = fopen("trapezy2.dat", "w");

	TOL = pow(10, -5);
	krokCzasowy(file, trapez, TOL);

	fclose(file);
}
