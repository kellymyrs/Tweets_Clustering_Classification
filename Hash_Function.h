#ifndef H_F
#define H_F
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
#include <chrono>

#define W 300

using namespace std;

class Hash_Function{
	private :
		double t;
		vector<double> v;
	public :
		Hash_Function(int d);
		~Hash_Function();
		void hash_function_v(int d);
		int64_t g_h_function(vector <double>& p);
};

#endif
