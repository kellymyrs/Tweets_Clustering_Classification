#ifndef C_G
#define C_G
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
#include "Cosine_Hash_Function.h"

using namespace std;

class Cosine_G{
    private:
        vector<Cosine_Hash_Function*> g;
    public:
        Cosine_G(int& k,int& d);
        ~Cosine_G();
        uint32_t Calculate_G(vector<double>& c);
        uint32_t Change_Bit(vector<double>& c,int p);
};

#endif
