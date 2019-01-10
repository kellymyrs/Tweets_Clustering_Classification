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

using namespace std;

struct Tweet{
	int id;
	vector <string> words;

	Tweet(int i,vector<string> w){
		id = i;
		words = w;
	}
};

#endif