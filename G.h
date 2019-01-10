#ifndef G_F
#define G_F
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
#include "Hash_Function.h"

#define W 300

using namespace std;

class G{
	private :
		vector<Hash_Function*> g;
		int64_t r;
	public :
		G(int& k,int& d);
		~G();
		int64_t f_function(vector <double>& p,uint32_t& t_size);
		void Calculate_G(vector<double>& c,vector<int64_t>& g_numbers);
};

#endif
