#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;

void increment_CI();
int fetch();
int decode();
int execute();
int load();
void clearmem();
void printmem();
void boot();
//global variables for setting sizes
int counter=0;
char memory[32][32];
int accumulator[32];
int controlinstruction[32];
char presentinstruction[32];

int execute(){

}

//decode function
int decode(){
//create two local arrays storing different parts of the current store location
char operand[13];
char opcode[3];
//presentinstruction is simply the row in the store that we are executing
for(int i = 0; i < 13; i++){
  operand[i] = presentinstruction[i];
}
for(int x = 0; x < 3; x++){
  opcode[x] = presentinstruction[x+13];
}

//for testing purposes
cout << operand << endl;
cout << opcode << endl;

//Takes the operand array and reverses the order
int length = strlen(operand);
char revOper[length];
for(int i = 1; i <= length; i++){
    revOper[i-1] = operand[length-i];
}
cout << revOper << endl;

//Takes the opcode array and reverses the order
int codelength = strlen(opcode);
char revOpcode[codelength];
for(int i = 1; i <= codelength; i++){
    revOpcode[i-1] = opcode[codelength-i];
}
cout << revOpcode << endl;

//You can now pass these two arrays into another function to be executed upon
}

void increment_CI(){
  counter++;
}

int fetch(){
increment_CI();
for (int i = 0; i < 32; i++){
  presentinstruction[i] = memory[counter][i];
}
cout << presentinstruction << endl;
}

int load(){
  ifstream inputfile("test.txt");
  for(int i = 0; i < 32; i++){
    for(int j = 0; j < 32; j++){
      inputfile >> memory[i][j];
    }
  }
  inputfile.close();
  cout << "File Loaded" << endl;
  return 1;
}
void printmem(){
  cout << "Printing Storage" << endl;
  for (int i = 0; i < 32; i++){
    for (int j =0; j<32; j++){
      cout << memory[i][j];
    }
    cout << endl;
  }
}

void boot(){
  cout << "Booting System" << endl;
  for(int i = 0; i < 32; i++){
    for(int j = 0; j < 32; j++){
      memory[i][j] = 0;
    }
    accumulator[i] = 0;
    controlinstruction[i] = 0;
    presentinstruction[i] = 0;
  }
  cout << endl;
  cout << endl;
  cout << endl;
  cout << endl;
  cout << endl;
  cout << "--------------" << endl;
  cout << "System Booted" << endl;
  cout << "--------------" << endl;
  cout << endl;
  cout << endl;
  cout << endl;
  cout << endl;
  cout << endl;
}
int main(){
boot();
load();
fetch();
decode();
}
