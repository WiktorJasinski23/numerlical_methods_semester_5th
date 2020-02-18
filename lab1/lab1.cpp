#include <iostream>
#include <math.h>
#include <vector>

double volts( double t, double omegav){
    return 10* sin(omegav*t);
}

int main(){
    ///////EULER//////////
    FILE *fp = fopen("anal.dat","w");
    FILE *fp1 = fopen("euler1.dat","w");
    FILE *fp2 = fopen("euler2.dat","w");
    FILE *fp3 = fopen("euler3.dat","w");

    double y0 = 1.0;
    double lambda = -1.0;
    double t0 = 0.0;
    double tk = 5.0;

    double deltat = 0.01;
    double y = y0;

    double anal = 1.0;


    for(double i = t0; i <= tk; i = i+deltat){
        anal = pow(M_E, lambda*i);
        fprintf(fp1, "%g %g %g\n", i, y, y-anal );
        fprintf(fp, "%g %g\n", i, anal);
        y = y + deltat*lambda*y;
    }

    deltat = 0.1;
    y=y0;
    anal = 1.0;

    for(double i = t0; i <= tk; i = i+deltat){
        anal = pow(M_E, lambda*i);
        fprintf(fp2, "%g %g %g\n", i, y, y-anal );
        y = y + deltat*lambda*y;
        
    }

    deltat = 1;
    y = y0;
    anal = 1.0;

    for(double i = t0; i <= tk; i = i+deltat){
        anal = pow(M_E, lambda*i);
        fprintf(fp3, "%g %g %g\n", i, y, y-anal );
        y = y + deltat*lambda*y;

    }

    fclose(fp);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);

    ////////////////////////////////////////////////////

    ////////////////////RK2/////////////////////////////////
    FILE *fp4 = fopen("anal2.dat","w");
    FILE *fp5 = fopen("trap1.dat","w");
    FILE *fp6 = fopen("trap2.dat","w");
    FILE *fp7 = fopen("trap3.dat","w");

    
    double k1,k2, k3, k4;
    deltat = 0.01;
    y=y0;

    for(double i = t0; i <= tk; i = i+deltat){
        anal = pow(M_E, lambda*i);
        fprintf(fp5, "%g %g %g\n", i, y, y-anal );
        fprintf(fp4, "%g %g\n", i, anal);
        k1 = lambda * y;
        k2 = lambda*(y+deltat*k1);
        y = y + (deltat/2.0) * (k1+k2);

    }

    deltat = 0.1;
    y=y0;

    for(double i = t0; i <= tk; i = i+deltat){
        anal = pow(M_E, lambda*i);
        fprintf(fp6, "%g %g %g\n", i, y, y-anal );
        k1 = lambda * y;
        k2 = lambda*(y+deltat*k1);
        y = y + (deltat/2.0) * (k1+k2);

    }

    deltat = 1;
    y=y0;

    for(double i = t0; i <= tk; i = i+deltat){
        anal = pow(M_E, lambda*i);
        fprintf(fp7, "%g %g %g\n", i, y, y-anal );
        k1 = lambda * y;
        k2 = lambda*(y+deltat*k1);
        y = y + (deltat/2.0) * (k1+k2);

    }


    fclose(fp4);
    fclose(fp5);
    fclose(fp6);
    fclose(fp7);

    ////////////////////////////////////////////////////

    ////////////////////RK4/////////////////////////////////
    FILE *fp8 = fopen("trap4.dat","w");
    FILE *fp9 = fopen("trap5.dat","w");
    FILE *fp10 = fopen("trap6.dat","w");

    deltat = 0.01;
    y=y0;

    for(double i = t0; i <= tk; i = i+deltat){
        anal = pow(M_E, lambda*i);
        fprintf(fp8, "%g %g %g\n", i, y, y-anal );
        k1 = lambda * y;
        k2 = lambda * (y+((deltat/2.0))*k1);
        k3 = lambda * (y+((deltat/2.0))*k2);
        k4 = lambda * (y + deltat*k3);
        y = y + deltat/6.0 *(k1 + 2*k2 + 2*k3 + k4);
    }

    deltat = 0.1;
    y=y0;

    for(double i = t0; i <= tk; i = i+deltat){
        anal = pow(M_E, lambda*i);
        fprintf(fp9, "%g %g %g\n", i, y, y-anal );
        k1 = lambda * y;
        k2 = lambda * (y+((deltat/2.0))*k1);
        k3 = lambda * (y+((deltat/2.0))*k2);
        k4 = lambda * (y + deltat*k3);
        y = y + deltat/6.0 *(k1 + 2*k2 + 2*k3 + k4);
    }


    deltat = 1;
    y=y0;

    for(double i = t0; i <= tk; i = i+deltat){
        anal = pow(M_E, lambda*i);
        fprintf(fp10, "%g %g %g\n", i, y, y-anal );
        k1 = lambda * y;
        k2 = lambda * (y+((deltat/2.0))*k1);
        k3 = lambda * (y+((deltat/2.0))*k2);
        k4 = lambda * (y + deltat*k3);
        y = y + deltat/6.0 *(k1 + 2*k2 + 2*k3 + k4);
    }

    fclose(fp8);
    fclose(fp9);
    fclose(fp10);

///////////////////////////////////////////////////////////////

    FILE *fp11 = fopen("omega0.5.dat","w");
    FILE *fp12 = fopen("omega0.8.dat","w");
    FILE *fp13 = fopen("omega1.0.dat","w");
    FILE *fp14 = fopen("omega1.2.dat","w");

    double R = 100.0;
    double L = 0.1;
    double C = 0.001;
    double omega0 = 1.0/sqrt(L*C);
    double T0 = 2*M_PI/omega0;
    double tkon = 4*T0;


    double Q = 0;
    double I = 0;

    double k1q, k2q, k3q, k4q, k1i, k2i, k3i, k4i;
    deltat = 0.0001;


    double omegav = 0.5 * omega0;
    for(double i = 0; i<=tkon; i= i+deltat){
        fprintf(fp11, "%g %g %g\n", i, Q, I );
        k1q = I;
        k1i = volts(i, omegav)/L - (1/(L*C))*Q-(R/L) * I;
        k2q = I + (deltat/2.0)*k1i;
        k2i = volts(i +(deltat/2.0), omegav)/L - (1/(L*C))*(Q+((deltat/2.0))*k1q)-(R/L)*(I+((deltat/2.0))*k1i);
        k3q = I + (deltat/2.0)*k2i;
        k3i = volts(i +(deltat/2.0), omegav)/L - (1/(L*C))*(Q+(deltat/2.0)*k2q)-(R/L)*(I+((deltat/2.0))*k2i);
        k4q = I + deltat*k3i;
        k4i = volts(i + deltat, omegav)/L - (1/(L*C))*(Q+deltat*k3q)-(R/L)*(I+deltat*k3i);
        Q = Q +(deltat/6.0)*(k1q + 2*k2q + 2*k3q + k4q);
        I = I +(deltat/6.0)*(k1i + 2*k2i + 2*k3i + k4i);
    }

     Q = 0;
     I = 0;
     omegav = 0.8 * omega0;
    for(double i = 0; i<=tkon; i= i+deltat){
        fprintf(fp12, "%g %g %g\n", i, Q, I );
        k1q = I;
        k1i = volts(i, omegav)/L - 1/(L*C)*Q-R/L *I;
        k2q = I + (deltat/2.0)*k1i;
        k2i = volts(i +(deltat/2.0), omegav)/L - 1/(L*C)*(Q+(deltat/2.0)*k1q)-R/L*(I+(deltat/2.0)*k1i);
        k3q = I + (deltat/2.0)*k2i;
        k3i = volts(i +(deltat/2.0), omegav)/L - 1/(L*C)*(Q+(deltat/2.0)*k2q)-R/L*(I+(deltat/2.0)*k2i);
        k4q = I + deltat*k3i;
        k4i = volts(i +deltat, omegav)/L - 1/(L*C)*(Q+deltat*k3q)-R/L*(I+deltat*k3i);
        Q = Q +deltat/6.0*(k1q + 2*k2q + 2*k3q + k4q);
        I = I +deltat/6.0*(k1i + 2*k2i + 2*k3i + k4i);
    }


        Q = 0;
       I = 0;
     omegav = 1.0 * omega0;
    for(double i = 0; i<=tkon; i= i+deltat){
        fprintf(fp13, "%g %g %g\n", i, Q, I );
        k1q = I;
        k1i = volts(i, omegav)/L - 1/(L*C)*Q-R/L *I;
        k2q = I + ((deltat/2.0))*k1i;
        k2i = volts(i +((deltat/2.0)), omegav)/L - 1/(L*C)*(Q+((deltat/2.0))*k1q)-R/L*(I+(deltat/2.0)*k1i);
        k3q = I + (deltat/2.0)*k2i;
        k3i = volts(i +((deltat/2.0)), omegav)/L - 1/(L*C)*(Q+((deltat/2.0))*k2q)-R/L*(I+(deltat/2.0)*k2i);
        k4q = I + deltat*k3i;
        k4i = volts(i +deltat, omegav)/L - 1/(L*C)*(Q+deltat*k3q)-R/L*(I+deltat*k3i);
        Q = Q +deltat/6.0*(k1q + 2*k2q + 2*k3q + k4q);
        I = I +deltat/6.0*(k1i + 2*k2i + 2*k3i + k4i);
    }


    Q = 0;
     I = 0;
     omegav = 1.2 * omega0;
    for(double i = 0; i<=tkon; i = i+deltat){
        fprintf(fp14, "%g %g %g\n", i, Q, I );
        k1q = I;
        k1i = volts(i, omegav)/L - (1/(L*C))*Q-(R/L) * I;
        k2q = I + (deltat/2.0)*k1i;
        k2i = volts(i +(deltat/2.0), omegav)/L - (1/(L*C))*(Q+((deltat/2.0))*k1q)-(R/L)*(I+((deltat/2.0))*k1i);
        k3q = I + (deltat/2.0)*k2i;
        k3i = volts(i +(deltat/2.0), omegav)/L - (1/(L*C))*(Q+(deltat/2.0)*k2q)-(R/L)*(I+((deltat/2.0))*k2i);
        k4q = I + deltat*k3i;
        k4i = volts(i + deltat, omegav)/L - (1/(L*C))*(Q+deltat*k3q)-(R/L)*(I+deltat*k3i);
        Q = Q +(deltat/6.0)*(k1q + 2*k2q + 2*k3q + k4q);
        I = I +(deltat/6.0)*(k1i + 2*k2i + 2*k3i + k4i);
    }




    fclose(fp11);
    fclose(fp12);
    fclose(fp13);
    fclose(fp14);
    return 0;
}