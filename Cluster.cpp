#include "Cluster.h"

Cluster::Cluster(Item<double>* c){

	cout << "Creating a new Cluster" << endl;
	cent = c;

}

Cluster::~Cluster(){
	cout << "Destroying a Cluster" << endl;
}

void Cluster::Insert(struct Item<double>* it){

	//cout << "Inserting an item to the Cluster " << it->cluster_id << endl;
	cl.push_back(it);

}
