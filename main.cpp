#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <vector>

using namespace std;

int leave_one_out_cross_validation(string fileName, vector<int> currFeatures, int k, int numColumns){
	string lines;
	ifstream infs;
	int numRows;
	string line;
	
	infs.open(fileName.c_str());
	
	if(infs.is_open()){
		while(getline(infs,lines)){ //counting the number of rows in the file
			numRows++; 
		}
		
		for(int i = 0; i < numRows; i++){
			
			for(int k = 0; i < numRows; k++){
			}
		}
	}else{
		cout << "Could not open file!!!" << endl;
		exit(1);
	}

	return 0;	
}

bool isInCurrSet(vector<int> currFeatures){
	return false; //false means that it is not in the currSet and thus needs to be considered
}

void feature_search_forward(string fileName, int numColumns){

	vector<int> currFeatures; //initializing the current set of features to be empty
	int accuracy;
	for(int i = 1; i < numColumns - 1; i++){
		cout << "On the " << i << "th level of the search tree" << endl;
		int feature_to_add;
		int best_accuracy_so_far = 0;

		for(int k = 1; k < numColumns - 1; k++){
			if(!isInCurrSet(currFeatures)){ //checks if the current feature number is in the curr set of features
				cout << "--Considering adding the " << k << "th feature" << endl;
				accuracy = leave_one_out_cross_validation(fileName, currFeatures, k + 1, numColumns); 
			}

			if(accuracy > best_accuracy_so_far){
				best_accuracy_so_far = accuracy;
				feature_to_add = k;
			}
		}

		cout << "On level " << i << " I added feature " << feature_to_add << " to the current set." << endl;
	}

}

void feature_search_backward(string fileName, int numColumns){

}


int main(){

	string fileName;
	string line;
	ifstream myFile;

	cout << "Welcome to my Feature Selection Program." << endl;
	cout << "Please type in the name of the tile to test: " << endl;

	cin >> fileName;//here i'm just going to assume that the user inputs the correct small or large text file

	myFile.open(fileName.c_str());

	if(myFile.is_open()){
		cout << "FILE WAS OPENED" << endl;

		cout << endl;

		cout << endl;

		getline(myFile,line);//grabbing the first line to count the number of columns

		stringstream str; 

		str << line; //sending the first line to the stringstream

		int numColumns;

		double currVal;

		while(str >> currVal){
			numColumns++;
		}

		myFile.close();

		int option;

		cout << "Please select which search algorithm you want to use." << endl;
		cout << "1) Forward Selection" << endl;
		cout << "2) Backward Elimination" << endl;

		cout << endl;

		cout << endl;

		cin >> option;

		cout << endl;

		if(option == 1){
			feature_search_forward(fileName,numColumns);
		}else{
			feature_search_backward(fileName,numColumns);
		}
		
	}else{
		cout << "FAIL!!" << endl;
	}

}


