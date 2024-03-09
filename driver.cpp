// Author: Nikola Tunguz
// Date: May 10, 2023
// Purpose: Homework 7 - Creating a graph data structure that can hold elements of any type.

#include <iostream>
#include <fstream>
#include <sstream>

#include "Graph.h"
using namespace std;

void print( string& value );
int factorial(int n);
void generatePermutations(string* cityArray, int numCities, int start, int end, string* permutationArray, int& permSize);

int main(){
    Graph<string> graph = Graph<string>();
    string cityArray[999];
    int numCities = 0;

    string city1 = "", city2 = "";
    int miles = 0, milesPerGallon = 40;
    
    //read cities and distances from file, add to graph and city array
    ifstream fin("cityData.txt");
    while( fin.good() ){
        fin >> city1 >> city2 >> miles; 
        graph.add(city1,city2, miles);

        bool insert1 = true, insert2 = true;
        for(int i = 0; i <= numCities; i++){
            if(cityArray[i] == city1){
                insert1 = false;
            }
            if(cityArray[i] == city2){
                insert2 = false;
            }
            
        }
        if(insert1){
                cityArray[numCities] = city1;
                numCities++;
            }
        if(insert2){
            cityArray[numCities] = city2;
            numCities++;
        }
    }
    fin.close();

    //create and store all permutations that begin and end at the first city
    string permutationArray[ factorial(numCities - 1) ];
    int permSize = 0;
    int optimalWeight = -1;
    string optimalPath = "";
    
    generatePermutations(cityArray,numCities,1,numCities,permutationArray, permSize);
  
    ofstream fout("solution.txt");
    fout << "Possible Permutations: " << permSize << endl; 

    for(int i = 0; i < permSize; i++){
        stringstream ss(permutationArray[i]);
        string city1 = "", city2 = "", next = "";
        ss >> city1 >> city2;
        int currentWeight = 0;

        try{
            while(ss >> next){
                currentWeight += graph.getEdgeWeight(city1,city2);
                city1 = city2;
                city2 = next;
            }
            currentWeight += graph.getEdgeWeight(city1,city2);

            if(currentWeight < optimalWeight || optimalWeight == -1){
                optimalWeight = currentWeight;
                optimalPath = permutationArray[i];
            }

            fout << permutationArray[i] << "     Cost (In Gallons): " << float(currentWeight) / milesPerGallon << endl;

        }
        catch(std::invalid_argument){
            fout << permutationArray[i] << "     Invalid Path " << endl;
        }

    }

    fout << endl << "Most Efficient Path" << endl << optimalPath << endl << "Cost (In Gallons): " << float(optimalWeight) / milesPerGallon << endl;

    return 0;  

}

void print( string& value ){
    cout << value << " ";
}

int factorial(int n){
    if(n == 1){
        return n;
    }
    return factorial(n-1) * n;
}
void generatePermutations(string* cityArray, int numCities, int start, int end, string* permutationArray, int& permSize){
    if( start == end){
        string input = "";
        for(int i = 0; i < numCities; i++){
            input += cityArray[i] + " ";
        }
        input += cityArray[0];
        permutationArray[permSize] = input;
        permSize++;
    }
    else{
        string temp = "";
        for(int i = start; i < end; i++){
            temp = cityArray[start];
            cityArray[start] = cityArray[i];
            cityArray[i] = temp;

            generatePermutations(cityArray,numCities, start+1, end,permutationArray,permSize);

            temp = cityArray[start];
            cityArray[start] = cityArray[i];
            cityArray[i] = temp;
        }
    }

}