#include <iostream>
#include <ctime>
#include <stdlib.h>
using namespace std;
#define MAX 200
#define SUB 100
int main(){
    unsigned t0, t1;
    double A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];



    for (int i = 0; i < MAX; i++){
        for (int j = 0; j < MAX; j++){
            //A[i][j]= rand() % 100;
            A[i][j]= 2;
            //B[i][j]= rand() % 100;
            B[i][j]= 2;
            C[i][j]= 0;
        }
    }

    t0=clock();  
    for (int i = 0; i < MAX; i+=SUB){
    	
        for (int j = 0; j < MAX; j+=SUB){
        	
            for (int k = 0; k < MAX; k+=SUB){
            	
				for (int si = 0; si < SUB; si++){
					
					for (int sj = 0; sj < SUB; sj++){
						
						for (int sk = 0; sk < SUB; sk++){
							//cout<<"entre ";
							C[i+si][j+sj] += A[i+si][k+sk]*B[k+sk][j+sj];
						}
					}
				}
            }
        }
    }
    t1 = clock();
    long double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Usando "<<MAX<<" y subsectores de "<<SUB<<" Valores el tiempo que tardo fue: " << time << endl;
    return 0;
}


