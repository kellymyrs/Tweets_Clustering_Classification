#ifndef UT
#define UT
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
#include <fstream>
#include <complex> 
#include <chrono>
#include <ctime>
#include <limits>
#include <iomanip>
#include <map>
#include <bits/stdc++.h>

#include "Tweet.h"
#include "User.h"
#include "Cluster.h"
#include "Item.h"
#include "G.h"
#include "Cosine_Lsh_Hashtable.h"
#include "Initialisation.h"
#include "Assignment.h"
#include "Update.h"
#include "Evaluation.h"

#define F_LEX "./vader_lexicon.csv"
#define F_BIT "./coins_queries.csv"
#define P 20
using namespace std;

void com_line_parser(int ,char** ,ifstream &,ofstream &,int &);
void read_input(ifstream &input_file,vector <struct User*> &users,int &N,int &d,map<int, struct Tweet*> &totaltweets);

int read_lex(map<string, double> &);
int read_bitcoins(vector<vector<string>> &);

void read_oldinput(vector<struct Item <double>*> &items);
void read_conf(int& k, int & L, int& n_clusters );

#endif