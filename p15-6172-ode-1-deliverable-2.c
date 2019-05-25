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


double growth(double p, double r, double m){
    return (r * p) - (r * p / m) * p; 
}


void initArray(double *array, int n){
    array[0] = 100;
    for (int i = 1; i < n; i++){
        array[i] = 0;
    }
}

void runSimulations(double dt, int n, double * population, double m, double r){
    for( int i = 0; i < n - 1; i++){
        population[i + 1] = population[i] + (int)(dt * growth( population[i], r, m )); 

       
    }
    
}

void display(double *array, int n){
    for (int i = 0; i < n; i++){
        printf("Population at the time %d is : %.2f\n", i + 1, array[i]);
    }
}

int main(int argc, char * argv[]){
    double dt = 1;
    int n = 100;
    double *population = (double *) malloc( n * sizeof(double));
    double m = 1000;
    double r = 0.1;
    initArray(population, n);
    runSimulations(dt, n , population, m, r);
    plot(n ,dt, population);
    display(population, n);
    free(population);
    return 0;
}