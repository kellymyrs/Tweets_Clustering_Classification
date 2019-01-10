#include "utils.h"

using namespace std;

int main(int argc,char* argv[]){	
	ifstream input_file, conf_file;
	ofstream output_file;
	int i,j,k = 4 ,L = 5,P,N,d,n_clusters,in,as,up,km = 0,validation = 0; // N = number of items(lines) in the file, d = number of coordinates (dimension)
	char* com;
	string line,temp_str;
	vector <struct User*> users;
	vector<struct Item <double>*> items,range;
	struct Item <double>* item,* nn = NULL;
	string metric;
	vector<Cluster* > clusters;
	vector<Cluster* > old_clusters;
	int t;
	vector<double> s;
	double 	ov = 0.0;
	double exec_time;

	srand (time(NULL));

	//command line parsing
	com_line_parser(argc,argv,input_file,output_file,validation);

	read_input(input_file,users,N,d,P);
	
	
	map<string, double> lex_map; // <- map (word) -> value
	vector<vector<string>> bc_vect;
	read_lex(lex_map);
	read_bitcoins(bc_vect);

	for(i = 0 ; i <= users.size() ; i++){
		users[i]->Create_U(bc_vect,lex_map);
	}
	return 1;
}