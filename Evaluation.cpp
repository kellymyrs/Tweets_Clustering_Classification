#include "Evaluation.h"

void silhouette(vector<struct Item <double>*> items,int& n_clusters,int& N,vector<Cluster* > &clusters,int &m,int &d){
	Cluster* second;
	double a,b,ov = 0.0;
	vector<double> s;

	//loop for every cluster
	for(int i = 0 ; i < n_clusters ; i++){

		s.push_back(0.0);
		
		//loop for every point of the cluster
		for(int j = 0 ; j < clusters[i]->cl.size() ; j++){

			//average distance of j to other objects in same cluster			
			av_dist(clusters[i]->cl[j],clusters[i],a,m);
			//cout << "a(s) = " << a << endl;

			//cluster of 2nd closest centroid
			second_cluster(clusters[i]->cl[j],clusters,second,m);
			
			//average distance of j to objects in next best (neighbor) cluster
			av_dist(clusters[i]->cl[j],second,b,m);
			//cout << "b(s) = " << b << endl;

			if( a > b ){
				s[i] += ( b - a ) / a;
			}
			else{
				s[i] += ( b - a ) / b;
			}
			//cout << "s(i) = " << s[i] << endl;

		}

		s[i] = s[i] / (double)(clusters[i]->cl.size());

		cout << "Average s(i) over all j in some cluster " << s[i]<< endl;
		ov += s[i];
	}
	ov = ov / (double)(n_clusters);
	cout << "Overall Silhouette " << ov << endl;
}

void av_dist(Item<double>* it,Cluster* cluster,double &sum,int &m){
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

	sum = sum / (cluster->cl.size() + 1);


}

void second_cluster(Item<double>* it,vector<Cluster* > &clusters,Cluster* second,int &m){
	double dist,min = 1000000;

	for (int i = 0; i < clusters.size(); ++i){
		
		if(it->cluster_id != i){

			if( m == 0 ){
				it->Distance(clusters[i]->get_centroid()->coordinates,dist);
			}
			else{
				it->Cosine_Distance(clusters[i]->get_centroid()->coordinates,dist);
			}
		
		}

		if( dist < min ){
			min = dist;
			second = clusters[i];
		}
	
	}
}