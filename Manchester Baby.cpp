#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>

#include "manbaby.h"

using namespace std;

int fetch();
int decode();
int execute();
int load();
void clearmem();
void printmem();


int counter;
char fetched[17];
char memory[32][32];
char loadmem[32];
char poke[32];
//sets the array to 0s


int main(){
	printarr(poke);
	cleararr(poke);
	printarr(poke);
	clearmem(memory);
	printmem();
	
	load();

}

//for loading binary into the memory
int load(){
	int line;

	cout << "Enter the line which you would like to poke data into, from 1 to 32: ";
	cin >> line;
	cout << endl << "Enter a 32 bit string: ";
	cin >> poke[32];

	for(int i = 0; i<32; i++){

		memory[line-1][i] = poke[i];

	}
	/*for(int i = 0; i<32; i++){

		if(memory[line][i] == void)
		memory[line][i] = '0';

	}*/
	printmem();
	printarr(poke);
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



void printmem(){

	for(int x = 0; x<32; x++){
	for(int i = 0; i<32; i++){

		cout << memory[x][i];

	}
	cout << endl;
}

}



