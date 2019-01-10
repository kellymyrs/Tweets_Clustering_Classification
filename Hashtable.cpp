#include "Hashtable.h"

Hashtable::Hashtable(int& k,int& d){
	cout << "Creating a hashtable !!!"<< endl;
	g_h = new G(k,d);
}

Hash_Member::Hash_Member(G* g_f,Item<double>* it){
	//cout << "Creating a hashmember !!!"<< endl;
	item = it;
	g_m = g_f;
	//g_f.clear();
}

Hashtable::~Hashtable(){
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

Hash_Member::~Hash_Member(){
	//cout << "Destroying hashmember"<< endl;
}


void Hashtable::Insert_Hashtable(struct Item<double>* it,uint32_t& t_size){

	//cout << "Creating f function!" << endl;
	int64_t f = g_h->f_function(it->coordinates,t_size); //calculate f
	//cout << "f number is :" << f << endl;


	//cout << "Inserting an item !" << endl;
	Hash_Member* h_member = new Hash_Member(g_h,it);
	hashtable[f].push_back(h_member);
}

struct Item<double>* Hashtable::NN_Hashtable(vector<double>& c,uint32_t& t_size,double& dist){
	double temp_dist;

	//cout << endl << endl << "Searching Hashtable" << endl;
	int64_t f = g_h->f_function(c,t_size); //calculate f
	//cout << "f = " << f << endl;
	struct Item <double>* temp_item = NULL ,* min_item = NULL;

	//search bucket
	auto search = hashtable.find(f);
	if(search != hashtable.end()){

		//cout << "Searching bucket" << endl;
		for (int i = 0; i < search->second.size(); i++){

			//cout << "Combining" << endl;
			temp_item = search->second[i]->Combine(c,g_h,temp_dist);

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
		//cout << "Empty bucket" << endl;
		return NULL;
	}
}

struct Item<double>* Hash_Member::Combine(vector<double>& c,G *g_h,double& temp_dist){
	int flag = 1; //checks if the two G functions are equal

	vector<int64_t> g_b,g_t;

	g_m->Calculate_G(c,g_b); //calculate hash member G
	g_h->Calculate_G(c,g_t); //calculate hashtable G

	//combine hash member G and hashtable G
	vector<int64_t>::iterator itv = g_b.begin();
	for (vector<int64_t>::iterator it = g_t.begin(); it != g_t.end(); ++it){

		//cout << "Hash member G = " << *itv << ' ';
		//cout << "Hashtable G = " << *it << endl;

		if(*itv != *it){ //case the two functions aren't equal
			flag = 0;
			break;
		}

		++itv;
	}

	//calculate distance
	if(flag){
		item->Distance(c,temp_dist);

		//cout << "Temp Item coordinates IN THE FOR : ";
		//int temp = 0;
		//for (int i = 0; i < item->coordinates.size() ; ++i){
		//	cout << item->coordinates[i] << " " ;
		//}
		//cout << endl;

		return item;
	}
	else{
		temp_dist = 10000000;
		return NULL;
	}

}

void Hashtable::Range_Hashtable(vector<double>& c,uint32_t& t_size,double& R,vector<struct Item <double>*>& range){
	struct Item <double>* temp_item = NULL;
	double temp_dist;

	//cout << endl << endl << "Searching Hashtable" << endl;

	int64_t f = g_h->f_function(c,t_size); //calculate f
	//cout << "f = " << f << endl;


	//search bucket
	auto search = hashtable.find(f);
	if(search != hashtable.end()){

		//cout << "Searching bucket" << endl;
		for (int i = 0; i < search->second.size(); i++){

			//cout << "Combining" << endl;
			temp_item = search->second[i]->Combine(c,g_h,temp_dist);

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
