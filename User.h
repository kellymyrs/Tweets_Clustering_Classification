#ifndef USER
#define USER
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

struct User{
	int id;
	vector <double> u;
	vector <bool> uex;
	vector <struct Tweet*> tweets;

	User(int i,struct Tweet* tweet){
		id = i;
		tweets.push_back(tweet);
	}
};

#endif