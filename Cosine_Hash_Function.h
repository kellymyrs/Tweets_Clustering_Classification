#ifndef C_H_F
#define C_H_F
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

using namespace std;

class Cosine_Hash_Function{
    private:
        vector<double> r;
    public:
        Cosine_Hash_Function(int& d);
        ~Cosine_Hash_Function();
        int cosine_h_function(vector <double>& p);
};

#endif
