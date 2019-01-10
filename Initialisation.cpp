#include "Initialisation.h"

void random_selection(vector<struct Item <double>*> items,int& n_clusters,int& N,vector<Cluster* > &clusters){

	int i,c;
	Cluster* cluster;

	cout << "Random Selection of "<< n_clusters << " points !" << endl;

	for( i = 0 ; i < n_clusters ; i++){

		c = rand() % N + 1;
		while( items[c-1]->cluster_id == 0 ){ //case the point is already a centroid
			c = rand() % N + 1;
		}
		
			
		items[c-1]->cluster_id = 0; //turn this point to a centroid

		cluster = new Cluster(items[c-1]);
		clusters.push_back(cluster);

	}

}

void kmeansplus(vector<struct Item <double>*> items,int& n_clusters,int& N,vector<Cluster* > &clusters,int &m){

	int i,flag = 0;
	double d,center;
	vector<double> dist;
	vector<double> v;
    double temp;

	cout << "K-means++ "<< endl;

	items[0]->cluster_id = 0; //turn this point to a centroid

	cout << "The new centroid is the item : " << items[0]->id << endl;
	//items[0]->Print_Item();	

	clusters.push_back(new Cluster(items[0]));

	//calculate distances from the centroid
	dist.push_back(0);
	v.push_back(0);
	//cout << v[0] << endl;

	for (i = 1 ; i < N ; i++){

		//items[i]->Print_Item();
		if( m == 0){
			items[0]->Distance(items[i]->coordinates,d);
		}
		else{
			items[0]->Cosine_Distance(items[i]->coordinates,d);
		}

		//cout << "Distance : " << d << endl;
		dist.push_back(d);
		v.push_back( v[i-1] + (d * d));
		//cout << v[i] << endl;
	
	}
	//cout << "DISTANCES OK!!" << endl;

	center = v[N-1] * ( (double)rand() / (double)RAND_MAX )  ;
	//cout << "TEMP " << temp << endl;
	//cout << "V "<<v[N-1] << endl;
    //center =  temp * v[N-1];
    //cout << "CENTROID : " << center << endl;

    //cout << "RAND OK !!" << endl;

	//find the right range
	i = 1;
	//cout << "V : " << v[i] << endl;
	while( center > v[i] ){
	//	cout << i << endl;
		i++;
	}

	//cout << "RANGE OK!!" << endl;
	//cout << "NEW CENTROID" << endl;
	//cout << i << endl;
	items[i]->cluster_id = 0; //turn this point to a centroid

	cout << "The new centroid is the item : " << items[i]->id << endl;	

	clusters.push_back(new Cluster(items[i]));		

	//loop for the rest centroids
	while( clusters.size() != n_clusters ){


		//calculate the distances from the new center
		if(!flag){ //case we haven't found a new centroid yet
			for( int j = 1 ; j < N ; j++ ){

				if( m == 0 ){
					items[j]->Distance(clusters[0]->get_centroid()->coordinates,dist[j]);
				}
				else{
					items[j]->Cosine_Distance(clusters[0]->get_centroid()->coordinates,dist[j]);
				}
				
				for (i = 1 ; i < clusters.size() ; i++){

					if( m == 0 ){
						items[j]->Distance(clusters[i]->get_centroid()->coordinates,d);
					}
					else{
						items[j]->Cosine_Distance(clusters[i]->get_centroid()->coordinates,d);
					}

					if( d < dist[j]){ //combine the distance from the last centroid with the previous minimum 

						dist[j] = d;

					}
				}

				v[j] = v[j-1] + (dist[j] * dist[j]);
			}
		}

		center = v[N-1] * ( (double)rand() / (double)RAND_MAX )  ;
		//cout << "TEMP " << temp << endl;
		//cout << "V "<<v[N-1] << endl;
	    //center =  temp * v[N-1];
	    //cout << "CENTROID : " << center << endl;

	    //cout << "RAND OK !!" << endl;

		//find the right range
		i = 1;
		//cout << "V : " << v[i] << endl;
		while( center > v[i] ){
		//	cout << i << endl;
			i++;
		}

		//cout << "RANGE OK!!" << endl;
		//cout << "NEW CENTROID" << endl;
		//cout << i << endl;
		items[i]->cluster_id = 0; //turn this point to a centroid

		cout << "The new centroid is the item : " << items[i]->id << endl;	

		clusters.push_back(new Cluster(items[i]));
		flag = 0;

	}

}