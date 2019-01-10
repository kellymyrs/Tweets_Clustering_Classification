#include "Update.h"

void pam(vector<struct Item <double>*> items,int& n_clusters,int& N,vector<Cluster* > &clusters,int &m){
	double sum,min;
	struct Item<double>* temp; 	

	cout << "PAM" << endl;
	for(int i = 0 ; i < n_clusters ; i++){


		objective_funct(clusters[i]->get_centroid(),clusters[i],min,m);
		
		for(int j = 0 ; j < clusters[i]->cl.size() ; j++){

			//calculate the distances from all the the other points of the cluster and the centroid
			objective_funct(clusters[i]->cl[j],clusters[i],sum,m);
			
			//update center
			if( sum < min ){
				min = sum;
				temp = clusters[i]->get_centroid();
				clusters[i]->Update_Cent(clusters[i]->cl[j]);
				clusters[i]->cl[j] = temp;

			}

		}

	}
}

void objective_funct(Item<double>* it,Cluster* cluster,double &sum,int &m){
	sum = 0;
	double dist;

	for(int j = 0 ; j < cluster->cl.size() ; j++){

		if( it->id != cluster->cl[j]->id){

			if( m == 0 ){
				it->Distance(cluster->cl[j]->coordinates,dist);
			}
			else{
				it->Cosine_Distance(cluster->cl[j]->coordinates,dist);
			}

			sum += dist;

		}
		
	}

	if( it->id != cluster->get_centroid()->id){

		if( m == 0 ){
			it->Distance(cluster->get_centroid()->coordinates,dist);
		}
		else{
			it->Cosine_Distance(cluster->get_centroid()->coordinates,dist);
		}

		sum += dist;

	}


}

void kmeans(vector<struct Item <double>*> items,int& n_clusters,int& N,vector<Cluster* > &clusters,int &m,int &d){
	Item<double>* centroid;
	double mean;
	vector<double> coordinates; //coordinates

	cout << "Kmeans" << endl;
	for(int i = 0 ; i < n_clusters ; i++){

		centroid = new Item<double>(0,coordinates,0);

		for(int c = 0 ; c < d ; c++ ){

			mean = 0;
			//cout << clusters[i]->cl.size() << endl;
			for(int j = 0 ; j < clusters[i]->cl.size() ; j++){

				mean += clusters[i]->cl[j]->coordinates[c];

			}
			mean += clusters[i]->cent->coordinates[c];
			mean = mean/(double)(clusters[i]->cl.size() + 1.0);
			//cout << mean << endl;
			centroid->coordinates.push_back(mean);
		}

		clusters[i]->cent = centroid;
		centroid->Print_Item();
		//delete centroid;
	}

}
