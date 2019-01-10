#include "Cosine_Lsh_Hashtable.h"

#include "Lsh_Hashtable.h"

Cosine_Lsh_Hashtable::Cosine_Lsh_Hashtable(int& k,int& d,int& L){
	Cosine_Hashtable* h;
	cout << "Creating Cosine_Lsh_Hashtable !!!" << endl;
	cout << "Dimension" << d << endl;
	for ( int i = 0; i < L; ++i ){
		h = new Cosine_Hashtable(k,d);
		lsh_hashtable.push_back(h);
	}
}

Cosine_Lsh_Hashtable::~Cosine_Lsh_Hashtable(){
	cout << "Destroying Cosine_Lsh_Hashtable"<< endl;

	//delete lsh_hashtable
	if(!lsh_hashtable.empty()){
		for ( auto it = lsh_hashtable.begin(); it != lsh_hashtable.end(); ++it ){
			delete *it;
		}
	}

}

void Cosine_Lsh_Hashtable::Insert_Lsh_Hashtable(struct Item<double>* item,uint32_t& t_size,int& L){
	// for loop for every hashtable
	for ( int i = 0; i < L; ++i ){
		lsh_hashtable[i]->Insert_Hashtable(item,t_size);
	}
}

void Cosine_Lsh_Hashtable::Range_Lsh(vector<double>& c,int& L,uint32_t& t_size,double& R,vector<struct Item <double>*>& range){

	//loop for every hashtable
	//cout << endl << endl << "Range Search : Searching Cosine_Lsh_Hashtable !" << endl;
	for (int i = 0 ; i < L ; i++){

		lsh_hashtable[i]->Range_Hashtable(c,t_size,R,range);

	}
}

struct Item<double>* Cosine_Lsh_Hashtable::NN_Lsh(vector<double>& c,int& L,uint32_t& t_size,double& min_dist){
	//loop for every hashtable
	double dist = min_dist = 10000000;
	struct Item<double>* min_item; //item with minimum distance for every hashtable
	struct Item<double>* result;


	//cout << endl << endl << " NN : Searching Lsh_Hashtable !" << endl;
	for (int i = 0 ; i < L ; i++){
		min_item = lsh_hashtable[i]->NN_Hashtable(c,t_size,dist);


		//if( min_item != NULL){
		//	cout << "Min Item distance Lsh : " << dist << endl ;
		//	cout << "Min Item coordinates Lsh : ";
		//	for (int j = 0; j < min_item->coordinates.size() ; j++){
		//		cout << min_item->coordinates[j] << " " ;
		//	}
		//	cout << endl;

		//}

		if (dist < min_dist){
		//	cout << "Change Result !!" << endl;
			min_dist = dist;
			result = min_item;
			//for (int j = 0; j < result->coordinates.size() ; j++){
			//	cout << result->coordinates[j] << " " ;
			//}
			//cout << endl;
		}

	}
	return result;

}
