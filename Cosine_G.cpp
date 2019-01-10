#include "Cosine_G.h"

Cosine_G::Cosine_G(int& k,int& d){
    g.reserve(k);
	Cosine_Hash_Function* h;

	cout << "Creating a Cosine G Hash function : " << endl;

	for (int i = 0; i < k; ++i){
		h = new Cosine_Hash_Function(d);
		g.push_back(h);
	}
}

Cosine_G::~Cosine_G(){
	cout << "Destroying Cosine G Hash function : " << endl;
	for (vector<Cosine_Hash_Function*>::iterator it = g.begin(); it != g.end(); ++it)
		delete *it;
	//g.clear();
}

uint32_t Cosine_G::Calculate_G(vector<double>& c){
	int h;
    uint32_t concat = 0;

	vector<Cosine_Hash_Function*>::iterator it;
	//cout << "Calculating Cosine G" << endl;
	//cout << "H = " ;
	for ( it = g.begin() ; it != g.end() ; ++it ){

		h = (*it)->cosine_h_function(c);
	//	cout << h << " " ;

        concat = (concat << 1) | h;

	}
	//cout << endl;
	//cout << "CONCAT = "<< concat << endl;
    return concat;
}

uint32_t Cosine_G::Change_Bit(vector<double>& c,int p){
	int h;
    uint32_t concat = 0;

	for(int i = 0 ; i < g.size() ; i++){
		h = g[i]->cosine_h_function(c);
        if(i == g.size() - p){
            if(h == 0){
                h = 1;
            }
            else{
                h = 0;
            }
        }
        concat = (concat << 1) | h;
    }
	//cout << endl;
	//cout << "CONCAT = "<< concat << endl;
    return concat;
}


