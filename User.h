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
#include "utils.h"

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


	void Create_U(vector <vector<string>>& coins,map<string, double>& lex){
		int flag = 0;
		int sum;

		//calculate tweets' scores
		for(int k = 0 ; k <= tweets.size() ; k++){
			tweets[k]->Calculate_Score(lex);
		}

		for(int i = 0 ; i <= coins.size() ; i++){

			sum = 0;
			flag = 0;			
			//search tweets
			for(int k = 0 ; k <= tweets.size() ; k++){	

				for(int j = 0 ; j <= coins[i].size() ; j++){

					if(tweets[k]->Search_Tweet(coins[i][j])){
						flag = 1; ////means that tweet talks about the coin
						sum += tweets[k]->score;
						break;
					}
				}

			}

			//if coin does't exist to any of the tweets
			if(!flag){
				u.push_back(-10000);
			}
			else{
				u.push_back(sum);
			}
		}
	}
};

#endif