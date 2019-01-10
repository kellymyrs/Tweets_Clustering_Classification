#ifndef EV
#define EV
#include "Item.h"
#include "Cluster.h"

void silhouette(vector<struct Item <double>*> items,int& n_clusters,int& N,vector<Cluster* > &clusters,int &m,int &d);
void av_dist(Item<double>* it,Cluster* cluster,double &sum,int &m);
void second_cluster(Item<double>* it,vector<Cluster* > &clusters,Cluster* second,int &m);

#endif