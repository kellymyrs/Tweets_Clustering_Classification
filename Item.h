#ifndef ITEM
#define ITEM
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <string>
#include <random>
#include <cstdint>
#include <time.h>
#include <math.h>
#include <utility>
#include <cmath>
#include <unordered_map>
#include <complex> 

#define W 300

using namespace std;

template <typename T>
struct Item{
	int id;
	vector <T> coordinates;
	int cluster_id;


	Item(int i,vector<T>& c,int cl){
		id = i;
		coordinates = c;
		cluster_id = cl;
	}
	~Item(){
		coordinates.clear();
	}
	void Distance(vector<T>& c,double& temp_dist){
		double temp = 0;
		//cout << "Item coordinates : ";
		for (int i = 0; i < coordinates.size() ; i++){
			temp += (coordinates[i] - c[i])*(coordinates[i] - c[i]) ;
		//	cout << coordinates[i] << " " ;
		}
		//cout << "Dist : " << temp_dist<< endl;
		temp_dist = sqrt(temp);
		//cout << " ************************sqrt--->" << temp_dist;
		//cout << endl;
	}

	void Cosine_Distance(vector<T>& c,double& temp_dist){
		double dot = 0.0, denom_a = 0.0, denom_b = 0.0 ,cos = 0.0;

		for (int i = 0; i < coordinates.size() ; i++){
		    dot += c[i] * coordinates[i] ;
        	denom_a += coordinates[i] * coordinates[i] ;
        	denom_b += c[i] * c[i] ;
    	}
    	cos = dot / (sqrt(denom_a) * sqrt(denom_b)) ;

		temp_dist = 1 - cos;
	}

	void Print_Item(){
        cout << "***Start print a POINT***" << '\n';

        // Print cordinates
        cout << "{";
        for (auto &c : coordinates) {
            cout << c <<",";
        }
        std::cout << "}" << "\n";
        std::cout << "<---End print   | POINT |" << "\n\n";		
	}

};

#endif
