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


double growthForQ(double q, double ka, double ke, double d){
    return ka * d - ke * q; 
}


double growthForQc(double dq, double v){
    return dq / v; 
}

void initArray(double *array, int n, int initial){
    array[0] = initial;
    for (int i = 1; i < n; i++){
        array[i] = 0;
    }
}

void runSimulations(double dt, int n, double * q , double * qc, double ka, double ke, double d, double v, int iterations){
    for( int i = 0; i < n - 1; i++){
        if(i % 8 == 0){
            double dq = growthForQ(q[iterations], ka, ke, d);
            q[iterations + 1] = q[iterations] + (dt * dq);
            qc[iterations + 1] = qc[iterations + 1] + (dt * growthForQc(dq, v));
            iterations++;
        }
        

       
    }
    
}

void display(double *array, double *array1, int n){
    for (int i = 0; i < n; i++){
        printf("Amount of Drug at the time %d is : %.2f\n", i + 1, array[i]);
        printf("Amount of Drug Concentration in blood at the time %d is : %.2f\n", i + 1, array1[i]);
    }
}

int main(int argc, char * argv[]){
    double dt = 1;
    int n = 100;
    int iterations = n / 8;
    double *q = (double *) malloc( n * sizeof(double));
    double *qc = (double *) malloc(n * sizeof(double));
    double v = 5;
    double ka = 0.12;
    double hl = 10;
    double d = 300;
    double ke = -log(0.5) / hl;
    initArray(q, iterations, 0);
    initArray(qc, iterations, q[0] / v);
    runSimulations(dt, n , q, qc, ka, ke, d, v, 0);
    plot(iterations ,dt, q);
    display(q, qc, iterations);
    free(q);
    free(qc);
    return 0;
}