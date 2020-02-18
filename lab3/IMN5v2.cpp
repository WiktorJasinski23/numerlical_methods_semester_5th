#include <iostream>
#include <math.h>

const int ny = 128;
const int nx = 128;
const double delta = 0.2;
const double xmax = delta * nx;
const double ymax = delta * ny;
const double TOL = pow(10, - 8);


double** poisson(double tab[][ny+1], int k, FILE *  integral, FILE * map){

    double V[nx+1][ny+1];

    for(int i = 0; i <= nx; ++i){
        for(int j = 0; j <= ny; ++j){
            V[i][j] = tab[i][j];
        }
    }

    static int it = 0;
    double Sit = 0.0;
    double prevSit = 0.0;
    
   
        
        for(int i = 0; i <= nx-k; i=i+k){
            for(int j = 0; j <= ny-k; j=j+k){
                Sit += pow(k * delta, 2) / 2.0  *  (pow((V[i+k][j] - V[i][j])/(2.0 * k * delta) + (V[i+k][j+k] - V[i][j+k])/(2.0 * k * delta), 2) + 
                pow((V[i][j+k] - V[i][j])/(2.0 * k * delta) + (V[i+k][j+k] - V[i+k][j])/(2.0 * k * delta), 2));
            }
        }

        do{
            for(int i = k; i <= nx-k; i=i+k){
                for(int j = k; j <= ny-k; j=j+k){
                    V[i][j] = (V[i+k][j] + V[i-k][j] + V[i][j+k] + V[i][j-k]) / 4.0;
                }
            }
            
            prevSit = Sit;
            Sit = 0.0;

            for(int i = 0; i <= nx-k; i=i+k){
                for(int j = 0; j <= ny-k; j=j+k){
                    Sit += pow(k * delta, 2) / 2.0  *  (pow((V[i+k][j] - V[i][j])/(2.0 * k * delta) + (V[i+k][j+k] - V[i][j+k])/(2.0 * k * delta), 2) + 
                    pow((V[i][j+k] - V[i][j])/(2.0 * k * delta) + (V[i+k][j+k] - V[i+k][j])/(2.0 * k * delta), 2));
                
                }
            }
            ++it;
            //std::cout<<k<<" "<<it<<" "<<Sit<<std::endl;
            fprintf(integral,"%d %f\n", it, Sit);
        }while(fabs((Sit - prevSit)/Sit) > TOL);

        for(int i = 0; i <= nx; i += k){
            for(int j = 0; j <= ny; j += k){
                fprintf(map, "%f %f %f \n", delta*i, delta*j, V[i][j]);
            }
            fprintf(map, "\n");
        }

        for(int i = 0; i <= nx-k; i=i+k){
            for(int j = 0; j <= ny-k; j=j+k){
                V[i+k/2][j+k/2] = (V[i][j] + V[i+k][j] + V[i][j+k] + V[i+k][j+k]) / 4.0;
                if(i!=nx-k)
                    V[i+k][j+k/2] = (V[i+k][j] + V[i+k][j+k]) / 2.0;
                if(j!=ny-k)
                    V[i+k/2][j+k] = (V[i][j+k] + V[i+k][j+k]) / 2.0;
                if(j!=0)
                    V[i+k/2][j] = (V[i][j] + V[i+k][j]) / 2.0;
                if(i!=0)
                    V[i][j+k/2] = (V[i][j] + V[i][j+k]) / 2.0;
            }
        }
        return V;
    }  





int main(){
    FILE * integral;
    FILE * map;

    double** V;

    for(int i = 0; i <= nx; ++i){
        for(int j = 0; j <= ny; ++j){
            V[i][j] = 0.0;
        }
    }

    for(int j = 0; j <= ny; ++j){
        V[0][j] = sin(M_PI*(delta*j/ymax));
    }

    for(int i = 0; i <= nx; ++i){
        V[i][ny] = (-1)*sin(2*M_PI*delta*i/xmax);
    }

    for(int j = 0; j <= ny; ++j){
        V[nx][j] = sin(M_PI*(delta*j/ymax));
    }

    for(int i = 0; i <= nx; ++i){
        V[i][0] = sin(2*M_PI*delta*i/xmax);
    }

    integral = fopen("integral1.dat","w");
    map = fopen("map1.dat","w");
    V = poisson(V, 16, integral, map);
    fclose(map);
    fclose(integral);


    integral = fopen("integral2.dat","w");
    map = fopen("map2.dat","w");
    V = poisson(V, 8, integral, map);
    fclose(map);
    fclose(integral);


    integral = fopen("integral3.dat","w");
    map = fopen("map3.dat","w");
    V = poisson(V,4, integral, map);
    fclose(map);
    fclose(integral);


    integral = fopen("integral4.dat","w");
    map = fopen("map4.dat","w");
    V = poisson(V,2, integral, map);
    fclose(map);
    fclose(integral);


    integral = fopen("integral5.dat","w");
    map = fopen("map5.dat","w");
    V = poisson(V, 1, integral, map);
    fclose(map);
    fclose(integral);

    return 0;
}