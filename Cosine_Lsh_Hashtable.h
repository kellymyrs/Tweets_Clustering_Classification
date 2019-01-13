#ifndef C_L_H
#define C_L_H
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <string>
#include <random>
#include <unordered_map>
#include <cstdint>
#include <time.h>
#include "Cosine_Hashtable.h"


using namespace std;

class Cosine_Lsh_Hashtable {
	private :
		vector<Cosine_Hashtable*> lsh_hashtable;
	public :
		Cosine_Lsh_Hashtable(int& k,int& d,int& L);
		~Cosine_Lsh_Hashtable();
		void Insert_Lsh_Hashtable(struct Item<double>* item,uint32_t& t_size,int& L);
		struct Item<double>* NN_Lsh(vector<double>& c,int& L,uint32_t& t_size,double& min_dist);
		void Range_Lsh(vector<double>& c,int& L,uint32_t& t_size,double& R,vector<struct Item <double>*>& range);
		void Get_Buckets(vector<double>& c,int& L,uint32_t& t_size,vector<struct Item <double>*>& range);
};

#endif
