#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <windows.h>
#include <queue>
using namespace std;
#define MAX 40
#define SUB 2
int main(){
    unsigned t0, t1;
    double A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
	queue <int> CACHE;


    for (int i = 0; i < MAX; i++){
        for (int j = 0; j < MAX; j++){
            //A[i][j]= rand() % 100;
            A[i][j]= 2;
            //B[i][j]= rand() % 100;
            B[i][j]= 2;
            C[i][j]= 0;
        }
    }
	
	
	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
    t0=clock();  
    SetConsoleTextAttribute(hConsole, 204);
    for (int i = 0; i < MAX; i+=SUB){
    	
        for (int j = 0; j < MAX; j+=SUB){
        	
            for (int k = 0; k < MAX; k+=SUB){

				for (int si = 0; si < SUB; si++){
					
					for (int sj = 0; sj < SUB; sj++){
						
						for (int sk = 0; sk < SUB; sk++){
							
							C[i+si][j+sj] += A[i+si][k+sk]*B[k+sk][j+sj];
							
							queue <int> tmp=CACHE;
							for(int bs=0;bs<CACHE.size();bs++){
								if(!tmp.empty()){
									if(tmp.front()!=i){
										tmp.pop();
									}
									else{
										SetConsoleTextAttribute(hConsole, 170);
										cout<<"EEE";
										SetConsoleTextAttribute(hConsole, 0);
										cout<<"|";
										break;
									}
								}
							}
							if(tmp.empty()){
								SetConsoleTextAttribute(hConsole, 204);
								cout<<"SSS";
								SetConsoleTextAttribute(hConsole, 0);
										cout<<"|";
								CACHE.push(i);
								if(CACHE.size()>=4){
									CACHE.pop();
									CACHE.push(i);
								}
							}
							
							
							tmp=CACHE;
							for(int bs=0;bs<CACHE.size();bs++){
								if(!tmp.empty()){
									if(tmp.front()!=-k){
										tmp.pop();
									}
									else{
										SetConsoleTextAttribute(hConsole, 170);
										cout<<"SSS";
										SetConsoleTextAttribute(hConsole, 0);
										cout<<"|";
										break;
									}
								}
							}
							if(tmp.empty()){
								SetConsoleTextAttribute(hConsole, 204);
								cout<<"EEE";
								SetConsoleTextAttribute(hConsole, 0);
								cout<<"|";
								CACHE.push(-k);
								if(CACHE.size()>=4){
									CACHE.pop();
									CACHE.push(-k);
								}
							}
							
						}
					}
				}
            }
        }
    }
    t1 = clock();
    SetConsoleTextAttribute(hConsole, 15);
    long double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Usando "<<MAX<<" y subsectores de "<<SUB<<" Valores el tiempo que tardo fue: " << time << endl;
    return 0;
}


