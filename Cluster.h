#ifndef CLUSTER
#define CLUSTER
#include "Item.h"

struct Cluster
{
	struct Item<double>* cent; 
	vector <Item<double>* > cl;


	Cluster(Item<double>* c);
	~Cluster();
	struct Item<double>* get_centroid() { return cent; }
	vector <Item<double>* > get_cluster() {return cl; }
	void Update_Cent(struct Item<double>* c){ c = cent; }
	void Insert(struct Item<double>* it);	
};

#endif
