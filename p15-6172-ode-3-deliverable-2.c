#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void plot(int steps, double dt, double *x){
    FILE *gplot = popen("gnuplot -persistent", "w");
    fprintf(gplot, "plot '-' u 1:2 title 'x' with lines\n");
    int i;
    for(i = 0; i <= steps; i++){
        fprintf(gplot, "%lf %lf\n", i*dt, x[i] * 100 / 3000);
    }
    fprintf(gplot, "e");
}   


double growth(double n, double k, double m){
    return k * n * log(m / n); 
}


void initArray(double *array, int n){
    array[0] = 1000;
    for (int i = 1; i < n; i++){
        array[i] = 0;
    }
}

void runSimulations(double dt, int n, double * cells, double k, double m){
    for( int i = 0; i < n - 1; i++){
        cells[i + 1] = cells[i] + (dt * growth( cells[i], k, m )); 

       
    }
    
}

void display(double *array, int n){
    for (int i = 0; i < n; i++){
        printf("Number of Cancer Cells at the time %d is : %.2f\n", i + 1, array[i]);
    }
}

int main(int argc, char * argv[]){
    double dt = 1;
    int n = 100;
    double *cells = (double *) malloc( n * sizeof(double));
    double k = 0.10;
    double m = 1000000;
    initArray(cells, n);
    runSimulations(dt, n , cells, k, m);
    plot(n ,dt, cells);
    display(cells, n);
    free(cells);
    return 0;
}