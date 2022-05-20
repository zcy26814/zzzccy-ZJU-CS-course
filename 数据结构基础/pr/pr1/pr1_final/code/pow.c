#include <time.h>
#include <stdio.h>
#include <stdlib.h>

//construct correlation function
double powNormal(double x, int n);
double powHardInterative(double x, int n);
double powHardRecursive(double x, int  n);

int main() {
    clock_t start, end;
    double tick[8];
    double total[8];
    double duration[8];

    double x = 1.0001;
    int n[] = {1000, 5000, 10000, 20000, 40000, 60000, 80000, 100000};
    int k[] = {100000, 60000, 30000, 10000, 6000, 3000, 1000, 600}; //k[i] is Iteration(K)
    int i, j;
    
    printf("N      ");
    for(i = 0; i < 8; i++) printf("%d      ", n[i]);
    printf("\n");

    for(i = 0; i < 8; i++) {
        start = clock();
        for(j = 0; j < k[i]; j++) {
            powNormal(x, n[i]);
        }
        end = clock();
        tick[i] = end - start; //Calculate the ticks, the same as below
        total[i] = tick[i]/CLK_TCK; //Calculate the total time, the same as below
        duration[i] = total[i]/k[i]; //Calculate the duration time, the same as below
    }
    printf("Algorithm 1: ");
    printf("\n");
    for(i = 0; i < 8; i++){
        printf("%d     ", k[i]);
    }
    printf("\n");
    for(i = 0; i < 8; i++){
        printf("%f  ", tick[i]);
    }
    printf("\n");
    for(i = 0; i < 8; i++){
        printf("%f  ", total[i]);
    }
    printf("\n");
    for(i = 0; i < 8; i++){
        printf("%e  ", duration[i]);
    }
    printf("\n"); //Output the required four columns of data respectively, the same as below

    for(i = 0; i < 8; i++) k[i] *= 1000; //Adjust the k[i] according to the algotithm and the project
    for(i = 0; i < 8; i++) {
        start = clock();
        for(j = 0; j < k[i]; j++) {
            powHardRecursive(x, n[i]);
        }
        end = clock();
        tick[i] = end - start;
        total[i] = tick[i]/CLK_TCK;
        duration[i] = total[i]/k[i];
    }
    printf("Algorithm 2(Recursive): ");
    printf("\n");
    for(i = 0; i < 8; i++){
        printf("%d     ", k[i]);
    }
    printf("\n");
    for(i = 0; i < 8; i++){
        printf("%f  ", tick[i]);
    }
    printf("\n");
    for(i = 0; i < 8; i++){
        printf("%f  ", total[i]);
    }
    printf("\n");
    for(i = 0; i < 8; i++){
        printf("%e  ", duration[i]);
    }
    printf("\n");

    for(i = 0; i < 8; i++) {
        start = clock();
        for(j = 0; j < k[i]; j++) {
            powHardInterative(x, n[i]);
        }
        end = clock();
        tick[i] = end - start;
        total[i] = tick[i]/CLK_TCK;
        duration[i] = total[i]/k[i];
    }
    printf("Algorithm 2(Iterative): ");
    printf("\n");
    for(i = 0; i < 8; i++){
        printf("%d     ", k[i]);
    }
    printf("\n");
    for(i = 0; i < 8; i++){
        printf("%f  ", tick[i]);
    }
    printf("\n");
    for(i = 0; i < 8; i++){
        printf("%f  ", total[i]);
    }
    printf("\n");
    for(i = 0; i < 8; i++){
        printf("%e  ", duration[i]);
    }
    printf("\n");

    system("pause");

}

double powNormal(double x, int n) {
    double y = x;
    int i;
    for(i=1; i<n; i++) {
        y *= x;
    }
    return y;
}

//If N is even, X^N = X^(N/2) × X^(N/2); and if N is odd, X^N = X^((N−1)/2) × X^((N−1)/2) × X
double powHardInterative(double x, int n) {
    double y = 1;
    while(n > 0) {
        if(n & 1) {
            y = y * x;
        }
        n /= 2;
        x *= x;
    }
}

double powHardRecursive(double x, int  n) {
    if(n == 0) {
        return 1; //When n = 0
    } else if(n == 1) {
        return x;
    } else {
        if(n & 2) { 
            return powHardRecursive(x * x, n/2) * x;
        } else {
            return powHardRecursive(x * x, n/2);
        } //Use the recursive way to realize the algorithm 2
    }
}