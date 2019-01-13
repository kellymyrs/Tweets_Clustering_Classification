#ifndef TWEET
#define TWEET
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
#include <algorithm>
#include "utils.h"

using namespace std;

struct Tweet{
	int id;
	double score;
	vector <string> words;

	Tweet(int i,vector<string> v){
		id = i;
		score = 0;
		words = v;
	}

	void Calculate_Score(map <string,double> dict){
		//cout << "Calculate score" << endl;
		
		for(int i = 0 ; i < words.size() ; i++){
			score += dict[words[i]];
		}
	}

	int Search_Tweet(string word){
		return find(words.begin(), words.end(), word) != words.end();
	}

	void Print_Tweet(){
		cout << "Tweet id : " << id << endl;
		cout << "Tweet's score : " << score << endl;
		cout << "Number of words : " << words.size() << endl;
		cout << "Words : ";
		for (int i = 0; i < words.size(); i++)
		{
			cout << words[i] << " ";
		}
		cout << endl;
	}

};

#endif