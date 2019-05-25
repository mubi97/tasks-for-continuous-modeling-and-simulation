#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void plot3d(int steps, double dt, double *x, double *y, double *z) 
{ 
    FILE *gplot = popen("gnuplot -persistent", "w"); 
    fprintf(gplot, "splot '-' u 1:2:3 title 'm' with lines\n"); 
    fprintf(gplot,"%lf %lf %lf\n", x[0], y[0], z[0]); 
    int i; 
    for (i = 0; i <= steps; i++) 
    { 
        fprintf(gplot,"%lf %lf %lf\n", x[i], y[i], z[i]); 
    } 
    fprintf(gplot,"e"); 
}


double growthForX(double y, double x, double sigma){
    return sigma * (y - x); 
}


double growthForY(double x, double y, double z, double rho){
    return x * (rho - z) - y; 
}


double growthForZ(double x, double y, double z, double beta){
    return x * y - beta * z; 
}

void initArray(double *array, int n, int initial){
    array[0] = initial;
    for (int i = 1; i < n; i++){
        array[i] = 0;
    }
}

void runSimulations(double dt, int n, double * x , double * y, double * z, double sigma, double rho, double beta){
    for( int i = 0; i < n - 1; i++){
        

        x[i + 1] = x[i] + dt * growthForX(y[i], x[i], sigma); 
        y[i + 1] = x[i] + dt * growthForY(x[i], y[i], z[i], rho);
        z[i + 1] = x[i] + dt * growthForZ(y[i], x[i], z[i], beta);
       
    }
    
}

void display(double *array, double *array1, double *array2, int n){
    for (int i = 0; i < n; i++){
        printf("Values At time %d\n x : %.2f\ty : %.2f\tz : %.2f\n", i + 1, array[i], array1[i], array2[i]);
    }
}

int main(int argc, char * argv[]){
    double dt = 1;
    int n = 100;
    double *x = (double *) malloc( n * sizeof(double));
    double *y = (double *) malloc(n * sizeof(double));
    double *z = (double *) malloc(n * sizeof(double));
    double sigma = 10;
    double rho = 28;
    double beta = 8 / 3;
    initArray(x, n, 1);
    initArray(y, n, 1);
    initArray(z, n, 1);
    runSimulations(dt, n , x, y, z, sigma, rho, beta);
    plot3d(n ,dt, x, y, z);
    display(x, y, z, n);
    free(x);
    free(y);
    free(z);
    return 0;
}