#include <iostream>
#include <ctime>
#include <stdlib.h>
using namespace std;
#define MAX 250
int main(){
    unsigned t0, t1;
    double A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];



    for (int i = 0; i < MAX; i++){
        for (int j = 0; j < MAX; j++){
            //A[i][j]= rand() % 100;
            A[i][j]= 2;
            //B[i][j]= rand() % 100;
            B[i][j]= 2;
        }
    }

    t0=clock();  
    for (int i = 0; i < MAX; i++){
        for (int j = 0; j < MAX; j++){
            C[i][j] = 0;
            for (int k = 0; k < MAX; k++){
                C[i][j] += A[i][k]*B[k][j];
            }
        }
    }
    t1 = clock();
    long double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Usando "<<MAX<<" Valores el tiempo que tardo fue: " << time << endl;
    return 0;
}

