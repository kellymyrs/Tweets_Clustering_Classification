#ifndef ASS
#define ASS
#include "Item.h"
#include "Cluster.h"
#include "Cosine_Lsh_Hashtable.h"
#include "Lsh_Hashtable.h"
#include "Search.h"
#include "G.h"
#include "Cosine_G.h"


void lloyds(vector<struct Item <double>*> items,int& n_clusters,int& N,vector<Cluster* > &clusters,int &m);
void lsh_search(int &k,int &d,int &L,int &N,int &m,vector<struct Item <double>*> &items,int &n_clusters,vector<Cluster* > &clusters);
void cube_search(int &k,int &d,int &L,int &N,int &m,vector<struct Item <double>*> &items,int &n_clusters,vector<Cluster* > &clusters);

#endif