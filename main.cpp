#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>

using namespace std;

int main(){

	string fileName;
	string line;
	ifstream myFile;

	cout << "Welcome to my Feature Selection Program." << endl;
	cout << "Please type in the name of the tile to test: " << endl;

	cin >> fileName;//here i'm just going to assume that the user inputs the correct small or large text file

	myFile.open(fileName);

	

		
}
