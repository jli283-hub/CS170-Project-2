#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <stdlib.h>
#include <math.h>   

using namespace std;


vector<double> splitString(string s);
bool isInCurrSet(vector<int> currFeatures, int k);

vector<int> remove_Feature(vector<int> currFeatures, int feature_to_remove){
    
    
    currFeatures.erase(remove(currFeatures.begin(), currFeatures.end(), feature_to_remove), currFeatures.end());
    
    return currFeatures;
    
}

double calculateDistance_backward(vector<double> object1, vector<double> object2, vector<int> currFeatures, int feature_to_remove, int numColumns){
    double distance = 9999;
    double sum = 0;
    vector<int> features = currFeatures;
    
    //temporarily removing the feature that we are considering
       
    features.erase(remove(features.begin(), features.end(), feature_to_remove), features.end());
    
    
    for(int i = 0; i < features.size(); i++){
        double temp1 = object1.at(features.at(i));
        double temp2 = object2.at(features.at(i));
        
        sum = sum + pow(temp1 - temp2, 2);
        
    }
    
    distance = sqrt(sum);
    
    return distance;


    /*
	vector<double> instance1 = object1; //original instance
	vector<double> instance2 = object2; //nearest neighbor that we want to calculate the distance tooi have 

	double sum = 0;
	double distance = 9999;
    
    */
    
    /*
    
        for(int k = 0; k < instance1.size(); k++){
            for(int j = 0; j < currFeatures.size(); j++){
                int feature = currFeatures.at(j);
                
                double temp1 = instance1.at(feature);
                double temp2 = instance2.at(feature);
                
                double calculation = pow(temp1 - temp2, 2);
                
                sum = sum + calculation;
                
            }
        }
        
    */
    
    /*
    for(int j = 0; j < currFeatures.size(); j++){
        
        int feature = currFeatures.at(j);
        
        double temp1 = instance1.at(feature);
        double temp2 = instance2.at(feature);
                
        double calculation = pow(temp1 - temp2, 2);
                
        sum = sum + calculation;
        
    }
    
            
	double temp2 = instance1.at(feature_to_consider); 
    double temp3 = instance2.at(feature_to_consider);
            
		
	double calculation1 = pow(temp2 - temp3, 2);

	sum = sum + calculation1;

	distance = sqrt(sum);

	return distance;
    
    */
	
}

double leave_one_out_cross_validation_backward(string fileName, vector<int> currFeatures, int feature_to_remove, int numColumns){

	int number_correctly_classified = 0;
	double nearest_neighbor_label;
	double accuracy;
    int sum = 0;
	string lines;
	ifstream infs;
	double numRows;
	vector<string> data;
	vector<vector<double>> file;

	infs.open(fileName.c_str());
	
	if(infs.is_open()){
		while(getline(infs,lines)){ //counting the number of rows in the file
			numRows++; 
			data.push_back(lines);//pushing the whole line into data vector for further processing
			
		}

		for(int d = 0; d < data.size(); d++){
			string temp = data.at(d);
            
			file.push_back(splitString(temp)); //storing the tokenized vector into a vector of doubles
            
		}
       
        
        /*
        
        for(int k = 0; k < file.size(); k++){
        
            for(int l = 0; l < file[k].size(); l++){
                    cout << file[k][l] << ' ' ;
            }
            
            cout << endl;
            
        }
        
        */
        
        
		for(int i = 0; i < numRows - 1; i++){ 
			vector<double> object_to_classify = file.at(i); //instance i
			double label_object_to_classify = object_to_classify.at(0);

			double nearest_neighbor_distance = 9999;
			int nearest_neighbor_location = 9999;

			for(int k = 0; k < numRows - 1; k++){
				if(k != i){

					double distance = calculateDistance_backward(object_to_classify, file.at(k), currFeatures, feature_to_remove, numColumns);

					if(distance < nearest_neighbor_distance){
						nearest_neighbor_distance = distance;
						nearest_neighbor_location = k;
						nearest_neighbor_label = file.at(k).at(0);
					}
				}
			}
           
			if(label_object_to_classify == nearest_neighbor_label){
                
				number_correctly_classified = number_correctly_classified + 1;
			}
		}

	}else{
		cout << "Could not open file!!!" << endl;
		exit(1);
	}

	infs.close();

	accuracy = (number_correctly_classified / (numRows - 1)) * 100;
    
    return accuracy;

}

vector<double> splitString(string s){
   

	vector<double> v; //this will store the values from each line 

	istringstream ss(s);

	double line;

	while(ss >> line){ //only getting the value without space
    
		v.push_back(line);
        
	}

	return v;
    
}

double calculateDistance(vector<double> object1, vector<double> object2, vector<int> currFeatures, int feature_to_consider, int numColumns){
    double distance = 9999;
    double sum = 0;
    vector<int> features = currFeatures;
    
    features.push_back(feature_to_consider); //temporarily pushing back the feature that we are considering
    
    for(int i = 0; i < features.size(); i++){
        double temp1 = object1.at(features.at(i));
        double temp2 = object2.at(features.at(i));
        
        sum = sum + pow(temp1 - temp2, 2);
        
    }
    
    distance = sqrt(sum);
    
    return distance;


    /*
	vector<double> instance1 = object1; //original instance
	vector<double> instance2 = object2; //nearest neighbor that we want to calculate the distance tooi have 

	double sum = 0;
	double distance = 9999;
    
    */
    
    /*
    
        for(int k = 0; k < instance1.size(); k++){
            for(int j = 0; j < currFeatures.size(); j++){
                int feature = currFeatures.at(j);
                
                double temp1 = instance1.at(feature);
                double temp2 = instance2.at(feature);
                
                double calculation = pow(temp1 - temp2, 2);
                
                sum = sum + calculation;
                
            }
        }
        
    */
    
    /*
    for(int j = 0; j < currFeatures.size(); j++){
        
        int feature = currFeatures.at(j);
        
        double temp1 = instance1.at(feature);
        double temp2 = instance2.at(feature);
                
        double calculation = pow(temp1 - temp2, 2);
                
        sum = sum + calculation;
        
    }
    
            
	double temp2 = instance1.at(feature_to_consider); 
    double temp3 = instance2.at(feature_to_consider);
            
		
	double calculation1 = pow(temp2 - temp3, 2);

	sum = sum + calculation1;

	distance = sqrt(sum);

	return distance;
    
    */
	
}


double leave_one_out_cross_validation(string fileName, vector<int> currFeatures, int feature_to_consider, int numColumns){

	int number_correctly_classified = 0;
	double nearest_neighbor_label;
	double accuracy;
    int sum = 0;
	string lines;
	ifstream infs;
	double numRows;
	vector<string> data;
	vector<vector<double>> file;

	infs.open(fileName.c_str());
	
	if(infs.is_open()){
		while(getline(infs,lines)){ //counting the number of rows in the file
			numRows++; 
			data.push_back(lines);//pushing the whole line into data vector for further processing
			
		}

		for(int d = 0; d < data.size(); d++){
			string temp = data.at(d);
            
			file.push_back(splitString(temp)); //storing the tokenized vector into a vector of doubles
            
		}
       
        
        /*
        
        for(int k = 0; k < file.size(); k++){
        
            for(int l = 0; l < file[k].size(); l++){
                    cout << file[k][l] << ' ' ;
            }
            
            cout << endl;
            
        }
        
        */
        
        
		for(int i = 0; i < numRows - 1; i++){ 
			vector<double> object_to_classify = file.at(i); //instance i
			double label_object_to_classify = object_to_classify.at(0);

			double nearest_neighbor_distance = 9999;
			int nearest_neighbor_location = 9999;

			for(int k = 0; k < numRows - 1; k++){
				if(k != i){

					double distance = calculateDistance(object_to_classify, file.at(k), currFeatures, feature_to_consider, numColumns);

					if(distance < nearest_neighbor_distance){
						nearest_neighbor_distance = distance;
						nearest_neighbor_location = k;
						nearest_neighbor_label = file.at(k).at(0);
					}
				}
			}
           
			if(label_object_to_classify == nearest_neighbor_label){
                
				number_correctly_classified = number_correctly_classified + 1;
			}
		}

	}else{
		cout << "Could not open file!!!" << endl;
		exit(1);
	}

	infs.close();

	accuracy = (number_correctly_classified / (numRows - 1)) * 100;
    
    return accuracy;

}
bool isInCurrSet(vector<int> currFeatures, int k){
	bool check = false;

	for(int i = 0; i < currFeatures.size(); i++){
		if(currFeatures.at(i) == k){
			check = true; //means that is is already in the currSet
		}
	}

	return check; //false means that it is not in the currSet and thus needs to be considered
}

double findMaxAccuracy(vector <double> a){
    double max = 0.0;
    
    for(int i = 0; i < a.size(); i++){
        if(a.at(i) > max){
            max = a.at(i);
        }
    }
    
    return max;
}

int findIndex(double max, vector<double> a){
    int index;
    
    for(int i = 0; i < a.size(); i++){
            if(a.at(i) == max){
              index = i;  
            }
    }
    
    return index;
}

void printBestFeatures(vector<int> features){
    for(int i = 0; i < features.size(); i++){
        cout << features.at(i) << " ";
    }
}

void feature_search_forward(string fileName, int numColumns){

	vector<int> currFeatures; //initializing the current set of features to be empty
    vector<double> accuracies; //storing the accuracies to print out the best one once search is over
    vector<vector<int>> bestFeatures; //storing the features that were added at each level
	double accuracy;
    double best_accuracy_so_far;
	int i;
	int k;
	for(i = 1; i < numColumns; i++){
		cout << "On the " << i << "th level of the search tree" << endl;
		int feature_to_add;
		best_accuracy_so_far = 0.0;

		for(k = 1; k < numColumns; k++){
			if(!isInCurrSet(currFeatures, k)){ //checks if the current feature number is in the curr set of features

				cout << "--Considering adding the " << k << "th feature" << endl;
				accuracy = leave_one_out_cross_validation(fileName, currFeatures, k, numColumns); 
                cout << fixed << setprecision(2);
				cout << "Accuracy of feature " << k << ": " << accuracy << "%" << endl;
                
                if(accuracy > best_accuracy_so_far){
					best_accuracy_so_far = accuracy;
					feature_to_add = k;
                }
                
			}
            
		}

		currFeatures.push_back(feature_to_add); //adding the best feature to the current set of features
        accuracies.push_back(best_accuracy_so_far);
        bestFeatures.push_back(currFeatures);
		cout << "On level " << i << " I added feature " << feature_to_add << " to the current set." << endl;
        
        cout << "Current set of Features: { ";
        
        copy(currFeatures.begin(),
         currFeatures.end(),
         ostream_iterator<int>(cout, " "));
         
        cout << "}" << endl;
        
	}
    
    cout << endl << endl;
    
    cout << "---------------FINISHED SEARCH!!--------------" << endl;
    
   double maxAccuracy = findMaxAccuracy(accuracies);
    
   int max_accuracy_position = findIndex(maxAccuracy, accuracies);
   
   vector<int> f = bestFeatures.at(max_accuracy_position);
    
   cout << "The best subset of features are: { ";
   
   for(int k = 0; k < f.size(); k++){
       cout << f.at(k) << " ";
       
       if(k == f.size() - 1){
            cout << "}";
       }
   }
   
   cout << " which has an accuracy of " << maxAccuracy << "%" << endl;

}

void feature_search_backward(string fileName, int numColumns){
    vector<int> currFeatures;
    vector<double> accuracies; //storing the accuracies to print out the best one once search is over
    vector<vector<int>> bestFeatures; //storing the features that were added at each level
    
    for(int i = 1; i < numColumns; i++){ //pushing all the possible features into the current set 
        currFeatures.push_back(i);
    }
    
    double accuracy;
    double best_accuracy_so_far;
	int i;
	int k;
	for(i = 1; i < numColumns; i++){
		cout << "On the " << i << "th level of the search tree" << endl;
		int feature_to_remove;
		best_accuracy_so_far = 0.0;

		for(k = 1; k < numColumns; k++){
			if(isInCurrSet(currFeatures, k)){ //checks if the current feature number is in the curr set of features

				cout << "--Considering removing the " << k << "th feature" << endl;
				accuracy = leave_one_out_cross_validation_backward(fileName, currFeatures, k, numColumns); 
                cout << fixed << setprecision(2);
				cout << "Accuracy of feature " << k << ": " << accuracy << "%" << endl;
                
                if(accuracy > best_accuracy_so_far){
					best_accuracy_so_far = accuracy;
					feature_to_remove = k;
                }
                
			}
            
		}

		currFeatures = remove_Feature(currFeatures, feature_to_remove); //removing the feature
        accuracies.push_back(best_accuracy_so_far);
        bestFeatures.push_back(currFeatures);
		cout << "On level " << i << " I removed feature " << feature_to_remove << " to the current set." << endl;
        
        cout << "Current set of Features: { ";
        
        copy(currFeatures.begin(),
         currFeatures.end(),
         ostream_iterator<int>(cout, " "));
         
        cout << "}" << endl;
        
	}
    
    cout << endl << endl;
    
    cout << "---------------FINISHED SEARCH!!--------------" << endl;
    
   double maxAccuracy = findMaxAccuracy(accuracies);
    
   int max_accuracy_position = findIndex(maxAccuracy, accuracies);
   
   vector<int> f = bestFeatures.at(max_accuracy_position);
    
   cout << "The best subset of features are: { ";
   
   for(int k = 0; k < f.size(); k++){
       cout << f.at(k) << " ";
       
       if(k == f.size() - 1){
            cout << "}";
       }
   }
   
   cout << " which has an accuracy of " << maxAccuracy << "%" << endl;
    
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
		}
        
        if(option == 2){
            feature_search_backward(fileName,numColumns);
        }
		
	}else{
		cout << "FAIL!!" << endl;
	}

}
