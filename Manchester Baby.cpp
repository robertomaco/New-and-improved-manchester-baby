#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int fetch();
int decode();
int execute();
int load();

int counter;
char fetched[17];
char memory[32][32];

int main(){

	
	decode();


}
//for loading binary into the memory
int load(){

}

int fetch(){

for(int i = 0; i<18; i++){

	fetched[i] = memory[0][i];

}

}

int decode(){
	cout << "Fetched addresses: ";
	for(int i = 0; i<18; i++){
		cout << fetched[i];
	}

}
