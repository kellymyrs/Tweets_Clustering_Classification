#include "G.h"

G::G(int& k,int& d){
	g.reserve(k);
	Hash_Function* h;

	//cout << "Creating a G Hash function : " << endl;
	r = rand() % 10 + 1;

	for (int i = 0; i < k; ++i){
		h = new Hash_Function(d);
		g.push_back(h);
	}
}

G::~G(){
	cout << "Destroying G Hash function : " << endl;
	for (vector<Hash_Function*>::iterator it = g.begin(); it != g.end(); ++it)
		delete *it;
	//g.clear();
}

int64_t G::f_function(vector <double>& p,uint32_t& t_size){
	//cout << "Calculating f!" << endl;

	int64_t f = 0, h;
	vector<Hash_Function*>::iterator it;
	for (it = g.begin(); it != g.end(); ++it){
		//cout << "In the for loop for every h" << endl;
		h = (*it)->g_h_function(p);
		//cout << "OK with the h(p) = " << h << endl;
		//cout << "OK with the r = " << r << endl;
		f +=  h * r;

	}
	//cout << "OK with the sum (h(p) * r)  !" << endl;
	//cout << "*********************F---->" << f << endl;
	f = f%t_size;

	if (f < 0) f += t_size;
	//cout << "*********************F---->" << f << endl;
	return f;
}

void G::Calculate_G(vector<double>& c,vector<int64_t>& g_m){
	int64_t h;

	vector<Hash_Function*>::iterator it;
	//cout << "Calculating G" << endl;
	for ( it = g.begin() ; it != g.end() ; ++it ){

		h = (*it)->g_h_function(c);

		g_m.push_back(h);

	}
}
