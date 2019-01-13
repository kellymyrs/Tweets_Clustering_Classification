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

#define F_LEX "./vader_lexicon.csv"
#define F_BIT "./coins_queries.csv"
#define P 20
using namespace std;

void com_line_parser(int argc,char* argv[],ifstream& input_file,ofstream& output_file,int& validation);
void read_input(ifstream &input_file,vector <struct User*> &users,int &N,int &d);

int read_lex(map<string, double> &);
int read_bitcoins(vector<vector<string>> &);

void find_P_NN(vector <struct User*> &users,vector<struct Item <double>*>& pnearest,int d);
void unrated_items(vector <struct User*> &users,vector<struct Item <double>*>& pnearest);
#endif