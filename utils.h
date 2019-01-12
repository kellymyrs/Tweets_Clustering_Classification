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
#include "Tweet.h"
#include "User.h"
#include "Cluster.h"
#define F_LEX "./vader_lexicon.csv"
#define F_BIT "./coins_queries.csv"
using namespace std;

void com_line_parser(int argc,char* argv[],ifstream& input_file,ofstream& output_file,int& validation);
void read_input(ifstream &input_file,vector <struct User*> &users,int &N,int &d);

int read_lex(map<string, double> &);
int read_bitcoins(vector<vector<string>> &);
#endif