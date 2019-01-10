#include "Cosine_Hashtable.h"

Cosine_Hashtable::Cosine_Hashtable(int& k,int& d){
	cout << "Creating a Cosine hashtable !!!"<< endl;
	g_h = new Cosine_G(k,d);
}

Cosine_Hash_Member::Cosine_Hash_Member(Item<double>* it){
	//cout << "Creating a hashmember !!!"<< endl;
	item = it;
	//g_f.clear();
}

Cosine_Hashtable::~Cosine_Hashtable(){
	cout << "Destroying hashtable"<< endl;

	//delete unordered multimap hashtable
	if(!hashtable.empty()){
		for ( auto it = hashtable.begin(); it != hashtable.end(); ++it ){
			for(auto itv = it->second.begin(); itv != it->second.end(); ++itv){
				delete *itv;
			}
		}
	}

	//delete g hash function
	delete g_h;
}

Cosine_Hash_Member::~Cosine_Hash_Member(){
	//cout << "Destroying hashmember"<< endl;
}


void Cosine_Hashtable::Insert_Hashtable(struct Item<double>* it,uint32_t& t_size){

	uint32_t cg = g_h->Calculate_G(it->coordinates);

	//cout << "Inserting an item !" << endl;
	Cosine_Hash_Member* h_member = new Cosine_Hash_Member(it);

	hashtable[cg].push_back(h_member);

}

struct Item<double>* Cosine_Hashtable::NN_Hashtable(vector<double>& c,uint32_t& t_size,double& dist){
	double temp_dist;

	//cout << endl << endl << "Searching Hashtable" << endl;
	uint32_t cg = g_h->Calculate_G(c) % t_size;

	struct Item <double>* temp_item = NULL ,* min_item = NULL;

	//search bucket
	auto search = hashtable.find(cg);
	if(search != hashtable.end()){

		//cout << "Searching bucket" << endl;
		for (int i = 0; i < search->second.size(); i++){

			//cout << "Combining" << endl;
			temp_item = search->second[i]->Combine(c,temp_dist);

			//cout << "Temp Item coordinates : ";
			//for (int j = 0; j < temp_item->coordinates.size() ; j++){
			//	cout << temp_item->coordinates[j] << " " ;
			//}
			//cout << endl;

			//cout <<"Found distance : "<< temp_dist << endl;
			//cout <<"Min distance : "<< dist << endl;
			if (temp_dist < dist){
				//cout << "Change minimum" << endl;
				dist = temp_dist;
				min_item = temp_item;

				//cout << "Min Item coordinates : ";
				//for (int j = 0; j < min_item->coordinates.size() ; j++){
				//	cout << min_item->coordinates[j] << " " ;
				//}
				//cout << endl;
			}
		}
		return min_item;
	}
	else{
		cout << "Empty bucket" << endl;
		return NULL;
	}
}

struct Item<double>* Cosine_Hash_Member::Combine(vector<double>& c,double& temp_dist){

	item->Cosine_Distance(c,temp_dist);
	return item;

}

void Cosine_Hashtable::Range_Hashtable(vector<double>& c,uint32_t& t_size,double& R,vector<struct Item <double>*>& range){
	struct Item <double>* temp_item = NULL;
	double temp_dist;

	//cout << endl << endl << "Searching Hashtable" << endl;

	uint32_t cg = g_h->Calculate_G(c);


	//search bucket
	auto search = hashtable.find(cg);
	if(search != hashtable.end()){

		//cout << "Searching bucket" << endl;
		for (int i = 0; i < search->second.size(); i++){

			//cout << "Combining" << endl;
			temp_item = search->second[i]->Combine(c,temp_dist);

			//cout << "Temp Item coordinates : ";
			//for (int j = 0; j < temp_item->coordinates.size() ; j++){
			//	cout << temp_item->coordinates[j] << " " ;
			 //}
			//cout << endl;

			//cout <<"Found distance : "<< temp_dist << endl;

			if (temp_dist < R){
				int flag = 1;
				//cout << "Adding an item to the range list" << endl;
				if(!range.empty()){
					for( int j = 0 ; j < range.size() ; j++){
						if( range[j]->id == temp_item->id ){
							flag = 0;
						}
					}
				}
				if(flag){
					range.push_back(temp_item);
				}
			}
		}
	}
	else{
		//cout << "Empty bucket" << endl;
		return;
	}
}
