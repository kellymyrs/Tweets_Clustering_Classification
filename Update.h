#ifndef UP
#define UP
#include "Item.h"
#include "Cluster.h"

void pam(vector<struct Item <double>*> items,int& n_clusters,int& N,vector<Cluster* > &clusters,int &m);
void objective_funct(Item<double>* it,Cluster* cluster,double &sum,int &m);
void kmeans(vector<struct Item <double>*> items,int& n_clusters,int& N,vector<Cluster* > &clusters,int &m,int &d);

#endif