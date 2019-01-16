#ifndef REC
#define REC
#include "utils.h"

void find_P_NN(vector <struct User*> &users,vector < vector<struct Item <double>*> >& totalpnearest,int d);
void find_P_NN(vector <struct User*> &users,vector< struct User*> &cusers,vector < vector<struct Item <double>*> >& totalpnearest,int d);
void clustering(vector <struct User*> &users,vector < vector<struct Item <double>*> >& totalclusters,int d);
void clustering(vector <struct User*> &users,vector< struct User*> &cusers,vector < vector<struct Item <double>*> >& totalclusters,int d);
void unrated_items(vector <struct User*> &,vector <vector<struct Item <double>*> >&);
void u_problem(vector <struct User*> &users,vector<vector<string>> &bc_vect,ofstream& output_file);
void Create_C(vector<struct Item <double>*> &items,int &n_clusters,vector< struct User*> &cusers,map<int, struct Tweet*> &totaltweets,map<string, double>& lex,vector <vector<string>>& bc_vect);
void c_problem(vector <struct User*> &users,vector<vector<string>> &bc_vect,ofstream& output_file);
void Validation(vector <struct User*> &users);

#endif