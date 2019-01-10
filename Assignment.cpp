#include "Assignment.h"

void lloyds(vector<struct Item <double>*> items,int& n_clusters,int& N,vector<Cluster* > &clusters,int &m){
	double d,min;
	cout << "Lloyd's" << endl;

	//loop for every point
	for(int i = 0 ; i < N ; i++ ){

		//find the minimum distance from all the centroids
		if( m == 0 ){
			items[i]->Distance(clusters[0]->get_centroid()->coordinates,min);
		}
		else{
			items[i]->Cosine_Distance(clusters[0]->get_centroid()->coordinates,min);
		}
		items[i]->cluster_id = 0; //assign the first cluster to the point

		//loop for every cluster 
		//check if the other clusters are closer to the point
		for (int j = 1 ; j < n_clusters ; j++){
			
			//find the distance from the current centroid
			if( m == 0){
				items[i]->Distance(clusters[j]->get_centroid()->coordinates,d);
			}
			else{
				items[i]->Cosine_Distance(clusters[j]->get_centroid()->coordinates,d);
			}

			//check if the current centroid is closer to the point
			if( d < min ){
				min = d;
				items[i]->cluster_id = j;				
			}

		}

		//instert the point to the closest cluster
		clusters[items[i]->cluster_id]->Insert(items[i]);
	}
}

void lsh_search(int &k,int &d,int &L,int &N,int &m,vector<struct Item <double>*> &items,int &n_clusters,vector<Cluster* > &clusters){
    uint32_t t_size;
    Lsh_Hashtable* eu_h;
    Cosine_Lsh_Hashtable* co_h;
    double R,temp;
    vector<struct Item <double>*> range;
    int assigned = n_clusters,balls=0;

    cout << "Lsh " << endl;

    //Create Lsh_Hashtable
    if(m == 0){
        eu_h = new Lsh_Hashtable(k,d,L);
        t_size = (uint32_t) floor(N/8);
    }
    else{
        co_h = new Cosine_Lsh_Hashtable(k,d,L);
        t_size = 2<<(k-1);
    }

    for (int i = 0; i < N; ++i){
        if( m == 0){
            eu_h->Insert_Lsh_Hashtable(items[i],t_size,L);
        }
    	else{
            //cout << "Inserting" << endl;
            co_h->Insert_Lsh_Hashtable(items[i],t_size,L);
        }
    }	

    for (int i = 0 ; i < n_clusters ; i++){
    	clusters[i]->get_centroid()->Print_Item();
    	cout << clusters[i]->get_centroid()->cluster_id << endl;
    }

    //calculate the distances between the centroids
    if( m == 0 ){
    	clusters[0]->get_centroid()->Distance(clusters[1]->get_centroid()->coordinates,R);
    }
    else{
    	clusters[0]->get_centroid()->Cosine_Distance(clusters[1]->get_centroid()->coordinates,R);
    }
    cout << "Initialise R : " << R << endl;
    temp = R;
    for (int i = 0 ; i < n_clusters ; i++){
    	
    	for(int j = 0 ; j < n_clusters ; j++){
		    
		    if(i != j ){
			    if( m == 0 ){
			    	clusters[i]->get_centroid()->Distance(clusters[j]->get_centroid()->coordinates,temp);
			    }
			    else{
			    	clusters[i]->get_centroid()->Cosine_Distance(clusters[j]->get_centroid()->coordinates,temp);
			    }	
			}		    		
    	
		    if( temp < R ){
		    	R = temp;
		    }
    	}
    }
//    cout << "Radious : " << R << endl;
//   R = 0.5;
	R = R / 2.0;
  	cout << "Radious : " << R << endl;

    while( assigned != N ){

	   	for( int i = 0 ; i < n_clusters ; i++){

	   		if(m == 0){
	   			eu_h->Range_Lsh(clusters[i]->get_centroid()->coordinates,L,t_size,R,range);
	   		}
	   		else{
	   			co_h->Range_Lsh(clusters[i]->get_centroid()->coordinates,L,t_size,R,range);
	   		}

	   		if(range.size() == 0 && assigned != 0 ){
	   			balls++;
	   		}
	   	
	   		//insert the neigbors to the cluster
	   		for(int j = 0 ; j < range.size() ; j++){

	   			//case we insert to the cluster a centroid
	   			if( range[j]->cluster_id == 0 ){
	   				continue;
	   			}
	   			//case the point belongs to more than one clusters
	   			else if( range[j]->cluster_id > 0 ){
	   				double cur , ex;

				    if( m == 0 ){

				    	//calculate the distance from the existing centroid			    	
				    	range[j]->Distance(clusters[range[j]->cluster_id]->get_centroid()->coordinates,ex);
				    
				    	//calculate the distance from the current centroid
				    	range[j]->Distance(clusters[i]->get_centroid()->coordinates,cur);

				    }
				    else{

				    	//calculate the distance from the existing centroid
				    	range[j]->Cosine_Distance(clusters[range[j]->cluster_id]->get_centroid()->coordinates,ex);	

				    	//calculate the distance from the current centroid
				    	range[j]->Cosine_Distance(clusters[i]->get_centroid()->coordinates,cur);	

	   				} 

	   				if( cur < ex ){
			   			range[j]->cluster_id = i;
			   			clusters[i]->Insert(range[j]);   					
	   				} 

	   			}			
	   			else{
		   			range[j]->cluster_id = i;
		   			clusters[i]->Insert(range[j]);
		   			assigned++;
		   		}
	   		}
	   		range.clear();
   			cout << "Assigned points : " << assigned << endl;
	   	}

	   	//case most ranges/balls do not assign a new point
	   	if( balls > n_clusters/2 ){
	   		break;
	   	}

	   	R = R*2;

	}

   	cout << "Assigned points : " << assigned << endl;

    if( m == 0 ){
        delete eu_h;
    }
    else{
        delete co_h;
    }
}

void cube_search(int &k,int &d,int &L,int &N,int &m,vector<struct Item <double>*> &items,int &n_clusters,vector<Cluster* > &clusters){
    uint32_t t_size;    
    Cosine_G* cg;
    G* g;
    int M=10,probes=2;
    double R,temp;
    vector<struct Item <double>*> range;
    int assigned = n_clusters,balls=0;

    cout << "Cube " << endl;

    //Create Hashtable
    unordered_map<int,vector <Item<double>*>> hashtable;    
    
    if(m == 1){ //cosine
        cg = new Cosine_G(k,d);
        t_size = 2<<(k-1);
    }
    else{ //euclidean
        g = new G(k,d);
        t_size = (uint32_t) floor(N/2);
    }  
      
    //insert items into the hashtable
    for (int i = 0; i < N; ++i){
        if(m){
            int hash = cg->Calculate_G(items[i]->coordinates);
            hashtable[hash].push_back(items[i]);
        }
        else{
            vector<int64_t> g_m;
            g->Calculate_G(items[i]->coordinates,g_m);
            int h,concat = 0;

            //cout << "H = ";
            for(int j = 0 ; j < g_m.size() ; j++){
                h = g_m[j] % 2;
                //cout << h << " " ;

                concat = (concat << 1) | h;            
            }
            //cout << endl;

            hashtable[concat].push_back(items[i]);            
        }
    }

    // for (int i = 0 ; i < n_clusters ; i++){
    // 	clusters[i]->get_centroid()->Print_Item();
    // 	cout << clusters[i]->get_centroid()->cluster_id << endl;
    // }

    //calculate the distances between the centroids
    if( m == 0 ){
    	clusters[0]->get_centroid()->Distance(clusters[1]->get_centroid()->coordinates,R);
    }
    else{
    	clusters[0]->get_centroid()->Cosine_Distance(clusters[1]->get_centroid()->coordinates,R);
    }
    temp = R;
    for (int i = 0 ; i < n_clusters ; i++){
    	
    	for(int j = 0 ; j < n_clusters ; j++){
		    
		    if(i != j ){
			    if( m == 0 ){
			    	clusters[i]->get_centroid()->Distance(clusters[j]->get_centroid()->coordinates,temp);
			    }
			    else{
			    	clusters[i]->get_centroid()->Cosine_Distance(clusters[j]->get_centroid()->coordinates,temp);
			    }	
			}		    		
    	
		    if( temp < R ){
		    	R = temp;
		    }
    	}
    }
//    cout << "Radious : " << R << endl;
//	R = R/2;
   	R = R / 2.0;
   	cout << "Radious : " << R << endl;

    while( assigned != N ){

	   	for( int i = 0 ; i < n_clusters ; i++){

            Range(clusters[i]->get_centroid()->coordinates,hashtable,m,R,M,probes,cg,g,range);

	   		if(range.size() == 0 && assigned != 0 ){
	   			balls++;
	   		}
	   	
	   		//insert the neigbors to the cluster
	   		for(int j = 0 ; j < range.size() ; j++){

	   			//case we insert to the cluster a centroid
	   			if( range[j]->cluster_id == 0 ){
	   				continue;
	   			}
	   			//case the point belongs to more than one clusters
	   			else if( range[j]->cluster_id > 0 ){
	   				double cur , ex;

				    if( m == 0 ){

				    	//calculate the distance from the existing centroid			    	
				    	range[j]->Distance(clusters[range[j]->cluster_id]->get_centroid()->coordinates,ex);
				    
				    	//calculate the distance from the current centroid
				    	range[j]->Distance(clusters[i]->get_centroid()->coordinates,cur);

				    }
				    else{

				    	//calculate the distance from the existing centroid
				    	range[j]->Cosine_Distance(clusters[range[j]->cluster_id]->get_centroid()->coordinates,ex);	

				    	//calculate the distance from the current centroid
				    	range[j]->Cosine_Distance(clusters[i]->get_centroid()->coordinates,cur);	

	   				} 

	   				if( cur < ex ){
			   			range[j]->cluster_id = i;
			   			clusters[i]->Insert(range[j]);   					
	   				} 

	   			}			
	   			else{
		   			range[j]->cluster_id = i;
		   			clusters[i]->Insert(range[j]);
		   			assigned++;
		   		}
	   		}
	   		range.clear();
   			cout << "Assigned points : " << assigned << endl;
	   	}

	   	//case most ranges/balls do not assign a new point
	   	if( balls > n_clusters/2 ){
	   		break;
	   	}

	   	R = R*2;

	}

   	cout << "Assigned points : " << assigned << endl;
    if(m == 1){ //cosine
        delete cg; 
    }
    else{ //euclidean
        delete g;
    }
}