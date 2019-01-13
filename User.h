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
#include "Item.h"

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
		int flag = 0; //means that user talks about the coin within at least one tweet
		int sum;

		//cout << "Creating vector U !!" << endl << endl;
		
		//calculate tweets' scores
		for(int k = 0 ; k < tweets.size() ; k++){
			tweets[k]->Calculate_Score(lex);
		}

		//search each coin
		for(int i = 0 ; i < coins.size() ; i++){

			sum = 0;
			flag = 0;

			//search tweets
			for(int k = 0 ; k < tweets.size() ; k++){	

				//search different types of the coin
				for(int j = 0 ; j < coins[i].size() ; j++){

					if(tweets[k]->Search_Tweet(coins[i][j])){
						flag = 1; //tweet talks about the coin
						sum += tweets[k]->score;
						break;
					}
				}

			}

			//if coin does't exist to any of the tweets
			if(!flag){
				u.push_back(-10000);
				uex.push_back(false);
			}
			else{
				u.push_back(sum);
				uex.push_back(true);
			}
		}

		Normalise();


#ifdef DEBUG
		cout << "<--------Printing User-------->" << endl;
		Print_User();
#endif
	}

	bool Ignore_User(){
		//check for zero vector
		
		int talk = 0; //user doesn't talk about bitcoins
		double zero; //user has only 0 coins 
		for(int i = 0 ; i < uex.size() ; i++){

			if(uex[i]){
				talk = 1;

				zero = u[i];
				if( zero != 0.0){
					break;
				}
			}
		
		}

		if(!talk || zero == 0.0){
			cout << "I am going to ignore user : " << endl;
			Print_User();
			return true;
		}

		return false;
	}

	void Print_User(){
		cout << "<<----------USER------------>>" << endl;
		cout << "User : " << id << endl;
		
		cout << "Tweets : " << endl;
		for (int i = 0 ; i < tweets.size() ; i++){
			tweets[i]->Print_Tweet();
		}


		cout << " U : ";
		for(int i = 0 ; i < u.size() ; i++){
			cout << u[i] <<" ";
		}
		cout << endl << endl;
	}

	double Average(vector <double> v){
		double ex = 0.0,sum = 0.0,av;

		for(int i = 0 ; i < v.size() ; i++){
			if( v[i] != -10000){
				sum += v[i];
				ex++;
			}
			else{
				v[i] = 0;
			}
		}
		if (ex != 0) {
			av = sum / ex;
			av = av / sqrt(av*av + 15);
		}
		else 
			av = 0;

		return av;
	}


	void Normalise(){
		double av = Average(u);
//#ifdef DEBUG 
		//cout << "Average Sentiment : " << av << endl;
//#endif
		for(int i = 0 ; i < u.size() ; i++){
			if(uex[i]){
				u[i] -= av;
			}
		}		
	}

	void calculate_R(vector<struct Item <double>*>& pnearest,int &j){
		double sum = 0.0 ,av = 0.0 ,total = 0.0, z;

		for(int i = 0 ; i < pnearest.size() ; i++){
			sum += pnearest[i]->Simularity(u);
			av += Average(pnearest[i]->coordinates);
			total += sum*av;
		}

		cout << "Sumary Simularity : " << sum << endl;
		cout << "Sumary  Average : "<< av << endl;

		if(!sum){
			z = 1 / abs(sum);
		}

		u[j] = z * total;

	}
};

#endif