#include <iostream>

using namespace std;

char printarr(char l[]){
	cout << endl;

	for(int i = 0; i<32; i++){

		cout << l[i];

	}
	cout << endl << endl;
	
}

void clearmem(char l[][32]){

for(int x = 0; x<32; x++){
	for(int i = 0; i<32; i++){

		l[x][i] = '0';

	}
}

}

char cleararr(char l[]){

	for(int i = 0; i<32; i++){

		l[i] = '0';

	}

}



