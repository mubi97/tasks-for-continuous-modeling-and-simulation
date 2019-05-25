#include <stdio.h>
#include <stdlib.h>



void plot(int steps, double dt, double *x){
    FILE *gplot = popen("gnuplot -persistent", "w");
    fprintf(gplot, "plot '-' u 1:2 title 'x' with lines\n");
    int i;
    for(i = 0; i <= steps; i++){
        fprintf(gplot, "%lf %lf\n", i*dt, x[i] * 100 / 3000);
    }
    fprintf(gplot, "e");
}   


double growth(double t, double h, double a, double tEnv){
    return h * a * (t - tEnv); 
}


void initArray(double *array, int n){
    array[0] = 298.15;
    for (int i = 1; i < n; i++){
        array[i] = 0;
    }
}

void runSimulations(double dt, int n, double * temperature, double h, double a, double tEnv){
    for( int i = 0; i < n - 1; i++){
        temperature[i + 1] = temperature[i] + (dt * growth( temperature[i], h, a, tEnv )); 

       
    }
    
}

void display(double *array, int n){
    for (int i = 0; i < n; i++){
        printf("Temperature at the time %d is : %.2f\n", i + 1, array[i]);
    }
}

int main(int argc, char * argv[]){
    double dt = 1;
    int n = 100;
    double *temperature = (double *) malloc( n * sizeof(double));
    double h = 10;
    double a = 30;
    double tEnv = 100;
    initArray(temperature, n);
    runSimulations(dt, n , temperature, h, a, tEnv);
    plot(n ,dt, temperature);
    display(temperature, n);
    free(temperature);
    return 0;
}