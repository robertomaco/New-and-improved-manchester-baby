//AC21009
//Team 9
//Scott Carnegie - 160020666
//Ryan McAleaney - 150012137
//Saral Mulasastra -
//Derrick Li -

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>
using namespace std;

//forward declarations of needed functions;
void printstatus();
void increment_CI();
int fetch();
int decode();
int execute(int operand, int opcode);
int load();
void clearmem();
void printmem();
void boot();
int decimalToBinary(int a);

//setting up memory locations
char memory[32][32];
int accumulator[32];
int controlinstruction[32];
char presentinstruction[32];
char operand[13];
char opcode[3];

//The DecodeCI function, returns the decimal representation of the controlinstruction register.
int decodeCI(){
  int revCI[32];
  for(int i = 0; i < 32; i++){
      revCI[i] = controlinstruction[31-i];
  }
  int CIsum = 0;
  int CImultiplyer = 0;
  for (int i = 31; i >= 0; i--){
      int temp = revCI[i];
      CIsum = CIsum + (temp * pow(2,CImultiplyer));
      CImultiplyer++;
  }
  return CIsum;
}

//the decodeAcc() function, returns the decimal represtation of the accumulator register.

int decodeAcc(){
  int revAcc[32];
  for(int i = 0; i < 32; i++){
      revAcc[i] = accumulator[31-i];
  }
  if(revAcc[0] == 1){
    int Accsum = 0;
    int Accmultiplyer = 0;
    for (int i = 31; i >= 1; i--){
        int temp = revAcc[i];
        Accsum = Accsum + (temp * pow(2,Accmultiplyer));
        Accmultiplyer++;
    }
    return -Accsum;
  }else{
  int Accsum = 0;
  int Accmultiplyer = 0;
  for (int i = 31; i >= 0; i--){
      int temp = revAcc[i];
      Accsum = Accsum + (temp * pow(2,Accmultiplyer));
      Accmultiplyer++;
  }
  return Accsum;
}
}


//The Execute function, takes the operand and opcode as decimal input parameters, and runs the appropriate commands.
int execute(int operand, int opcode){
//Gets the decimal representation of the controlinstruction and the accumulator
int CI = decodeCI();
int ACC = decodeAcc();
//sets up a status variable, only used to tell the program not to loop the fetch-execute cycle again
int exestatus = 0;
//The 8, really 7 cause 4 and 5 are the same, different operations the baby can perform.
if(opcode == 0){
  //If the opcode is zero, set the controlinstruction to the operand value and jump to it on the next f-e cycle
  CI = operand;
}else if(opcode == 1){
  //if the opcode is one, perform a relative jump, adding the operand to the controlinstruction
  CI = CI + operand;
}else if(opcode == 2){
  //if the opcode is two, set the accumulator to the negative value of the operand
  ACC = -(operand);
}else if(opcode == 3){
  //if the opcode is three, set the line in the store corresponding to the operand value to the accumulator
  char accChar[32];
  for (int i = 0; i < 32; i++){
    if(accumulator[i] == 0){
      accChar[i] = '0';
    }else if(accumulator[i] == 1){
      accChar[i] = '1';
    }else{

    }
    for(int i = 0; i<32;i++){
      memory[operand-1][i] = accChar[i];
    }
  }
}else if(opcode == 4 || opcode == 5){
  // if the opcode is either four or five, take the operand from the accumulator
  ACC = ACC - operand;
}else if(opcode == 6){
  //if the opcode is 6 and the accumlator is negative, skip a increment of the controlinstruction
  if(ACC < 0){
    increment_CI();
  }
}else if(opcode == 7){
  //if the opcode is 7, set exestatus to 2, and use that to check if we should perform another fetch-execute cycle.
  exestatus = 2;
}
//Check if the decimal value of the new accumlator is positive, if so, just place it into the accumlator register
if(ACC >= 0){
int toReturn[32];
for(int l = 0;l<32;l++){
  toReturn[l]=0;
}
int returned = decimalToBinary(ACC);
while(returned){
 for(int m = 0;m<sizeof(returned);m++){
   toReturn[m] = returned%10;
   returned /= 10;
 }
}
for(int i = 0; i<32;i++){
 accumulator[i] = toReturn[i];
}
//if not, represent the number in the same way, just having a 1 at the 32nd bit, letting my program know the number is supposed to be negative
//NOT TWO's COMPLIMENT
//Purely a solution for my program
}else{
int toReturn[32];
for(int l = 0;l<32;l++){
  toReturn[l]=0;
}
int returned = decimalToBinary(-ACC);
while(returned){
 for(int m = 0;m<sizeof(returned);m++){
   toReturn[m] = returned%10;
   returned /= 10;
 }
}
for(int i = 0; i<32;i++){
 accumulator[i] = toReturn[i];
}
accumulator[31] = 1;
}
//Also, if need be, re-put the CI variable into the controlinstruction register.
int CIReturn[32];
  for(int l = 0;l<32;l++){
    CIReturn[l]=0;
  }
  int CIreturned = decimalToBinary(CI);
  while(CIreturned){
   for(int m = 0;m<sizeof(CIreturned);m++){
     CIReturn[m] = CIreturned%10;
     CIreturned /= 10;
   }
  }
  for(int i = 0; i<32;i++){
   controlinstruction[i] = CIReturn[i];
  }
//if conditional allowing my program to know if it needs to start the fetch-execute cycle again, or just print out the final, halted, details
if(exestatus == 2){
  printstatus();
  cout << "STATUS: HALTED- Baby reached end of program!" << endl;
}else{
  printstatus();
  fetch();
}
}


//The Decode Function, gets the Operand and Opcode from the presentinstruction array, reverses their order, converts them to decimal, and passes them into the execute function
int decode(){

//create two local arrays storing different parts of the current store location
//presentinstruction is simply the row in the store that we are executing

for(int i = 0; i < 13; i++){
  operand[i] = presentinstruction[i];
}
for(int x = 13; x < 16; x++){
  opcode[x-13] = presentinstruction[x];
}

//Takes the operand array and reverses the order

char revOper[13];
for(int i = 0; i < 13; i++){
    revOper[i] = operand[12-i];
}

//Takes the opcode array and reverses the order

char revOpcode[3];
for(int i = 0; i < 3; i++){
    revOpcode[i] = opcode[2-i];
}

//takes the now reveresed Operand array and converts it into an Equivalent integer array

int revOperInt[13];
for (int i = 0; i < 13; i++){
  if(revOper[i] == '0'){
    revOperInt[i] = 0;
  }else if(revOper[i] == '1'){
    revOperInt[i] = 1;
  }else{

  }
}

//Same as above, but for the opcode array

int revOpcodeInt[3];
for (int i = 0; i < 3; i++){
  if(revOpcode[i] == '0'){
    revOpcodeInt[i] = 0;
  }else if(revOpcode[i] == '1'){
    revOpcodeInt[i] = 1;
  }else{

  }
}

//converts the now integer array of the operand (still binary) into a decimal number

int operandsum = 0;
int multiplyer = 0;
for (int i = 12; i >= 0; i--){
    int temp = revOperInt[i];
    operandsum = operandsum + (temp * pow(2,multiplyer));
    multiplyer++;
}

//Same as above but for the opcode

int opcodesum = 0;
int opmultiplyer = 0;
for (int i = 2; i >= 0; i--){
    int temp = revOpcodeInt[i];
    opcodesum = opcodesum + (temp * pow(2,opmultiplyer));
    opmultiplyer++;
}

//Runs the execute function, passing through the decimal values of the operand and opcode for the current line
execute(operandsum, opcodesum);
}

//function for taking an integer and returning its binary representation
int decimalToBinary(int n) {
    int remainder;
 int binary = 0, i = 1;

    while(n != 0) {
        remainder = n%2;
        n = n/2;
        binary= binary + (remainder*i);
        i = i*10;
    }
    return binary;
}


// The Increment_CI function, this function it increments the controlinstruction, so that we know what line in the store we are working with

void increment_CI(){
  //Sets a CIsum integer variable to the returned value of a function, decodeCI(), which returns the decimal value of the controlinstruction
  int CIsum = decodeCI();
  //adds one to the controlinstruction
  CIsum = CIsum + 1;
  //Returns the new CIsum as a binary number to the controlinstruction.
  int toReturn[32];
  for(int l = 0;l<32;l++){
    toReturn[l]=0;
  }
  int returned = decimalToBinary(CIsum);
  while(returned){
   for(int m = 0;m<sizeof(returned);m++){
     toReturn[m] = returned%10;
     returned /= 10;
   }
  }
  for(int i = 0; i<32;i++){
   controlinstruction[i] = toReturn[i];
  }
}

//The Fetch Function, increments the controlinstruction register, and sets the presentinstruction register to the line in the store that we need. Then runs the Decode() function automatically

int fetch(){
increment_CI();
int CIsum = decodeCI();
for (int i = 0; i < 32; i++){
  presentinstruction[i] = memory[CIsum][i];
}
decode();
}

//The Load function, loads a program from a txt file into the store to be run

int load(){
  ifstream inputfile("BabyTest1-MC.txt");
  for(int i = 0; i < 32; i++){
    for(int j = 0; j < 32; j++){
      inputfile >> memory[i][j];
    }
  }
  inputfile.close();
    cout << "---------------" << endl;
  cout << "File Loaded" << endl;
    cout << "---------------" << endl;
  return 1;
}

//The print status function, prints out the values of the store (32x32), and the other registers to the console.

void printstatus(){
  //Prints the whole store to the console
  cout << endl;
  cout << endl;
  cout << "---------------" << endl;
cout << "Printing New Cycle Info" << endl;
  cout << "---------------" << endl;
    for(int i = 0; i<32;i++){
      for(int j = 0; j<32;j++){
        cout << memory[i][j];
      }
      cout << endl;
    }
    //Prints The Value of the Accumulator to the console
    cout << "---------------" << endl;
  cout << "Printing Accumulator" << endl;
    cout << "---------------" << endl;
    cout << "Register Storage : ";
    int n1 = decodeAcc();
    for (int i=0;i<32;i++){
      cout << accumulator[i];
    }
    cout << endl << "Decimal : " << n1 << endl;
  cout << endl;
  //Prints The Value of the Control Instruction Register to the console
  cout << "---------------" << endl;
cout << "Printing CI" << endl;
  cout << "---------------" << endl;
  cout << "Register Storage : ";
  int n2 = decodeCI();
  for (int i=0;i<32;i++){
    cout << controlinstruction[i];
  }
  cout << endl << "Decimal : " << n2 << endl;
  cout << endl;
  //Prints The Value of the Accumulator to the console
  cout << "---------------" << endl;
  cout << "Printing PI" << endl;
  cout << "---------------" << endl;
  cout << "Register Storage : ";
  for (int i=0;i<32;i++){
    cout << presentinstruction[i];
  }
  cout << endl;
  cout << endl;
}

//The Boot function, Intialises all the memory locations to 0;

void boot(){

  //Prints the Boot Message to the Console
  cout << "---------------" << endl;
  cout << "Booting System" << endl;
  cout << "---------------" << endl;

  //Intialises all the required memory locations to zero.
  for(int i = 0; i < 32; i++){
    for(int j = 0; j < 32; j++){
      memory[i][j] = 0;
    }
    accumulator[i] = 0;
    presentinstruction[i] = 0;
    controlinstruction[i] = 0;
  }
}
//The Main Function, Boots the Machine, Loads the txt file into the store and starts the fetch-execute cycle
int main(){
  boot();
  load();
  printstatus();
  fetch();
}
