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
		for(int i = 0 ; i <= words.size() ; i++){
			score += dict[words[i]];
		}
	}

	int Search_Tweet(string word){
		return find(words.begin(), words.end(), word) != word.end();
	}


};

#endif