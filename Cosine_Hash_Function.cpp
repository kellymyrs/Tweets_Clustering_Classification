#include "Cosine_Hash_Function.h"

Cosine_Hash_Function::Cosine_Hash_Function(int& d){
	cout << "Creating a Cosine Hash function : "<< endl;

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
	std::normal_distribution<double> distribution(0.0, 1.0);

	r.reserve(d);
	for ( int i = 0 ; i < d ; i++){
		double number = distribution(generator);
		r.push_back(number);
		//cout << "r" << i << " = " << number << endl;
	}
}

Cosine_Hash_Function::~Cosine_Hash_Function(){
	cout << "Destroying Cosine Hash Function" << endl;
	r.clear();
}

//calculates h(p)
int Cosine_Hash_Function::cosine_h_function(vector <double>& p){
    double c = 0;

    //cout << "Calculating h(p) !" << endl;
	vector<double>::iterator itv = r.begin();
	for (vector<double>::iterator it = p.begin(); it != p.end(); it++){
		//cout << "ri = " << *itv << endl;
		//cout << "p = " << *it << endl;
		c += (*itv) * (*it);
		itv++;
	}
	//cout << "H(P) = " << c << endl;
    if( c >= 0)
        return 1;
    else
        return 0;

}
