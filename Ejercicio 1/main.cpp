#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <cstdlib>
#include <unistd.h>
using namespace std;


#define MAX 500
int main()
{

    unsigned t0, t1, t2, t3;
    double A[MAX][MAX], x[MAX], y[MAX];
    int nmro=1;
    char ext='1';

    for (int i = 0; i < MAX; i++){
        for (int j = 0; j < MAX; j++){
            A[i][j]= rand() % 100;
            x[j]= rand() % 100;
        }
    }

    do{
        if(ext!='1'){
            break;
        }
        cout<<"Prueba numero: "<<nmro<<endl;
        nmro++;

        t0=clock();
        for (int i = 0; i < MAX; i++){
            for (int j = 0; j < MAX; j++){
                y[i] += A[i][j]*x[j];
            }
        }
        t1 = clock();
        long double time = (double(t1-t0)/CLOCKS_PER_SEC);
        cout << "Tiempo que tardo 1: " << time << endl;

        t2 = clock();
        for (int j = 0; j < MAX; j++){
            for (int i = 0; i < MAX; i++){
                y[i] += A[i][j]*x[j];
            }
        }
        t3 = clock();
        cout << t2<< endl;
        long double time2 = (double(t3-t2)/CLOCKS_PER_SEC);
        cout << "Tiempo que tardo 2: " << time2 << endl;
        cout << "ingrese 1 para continuar" << endl;
        //sleep(3);
    }while(cin>>ext);

    return 0;
}

