#include "utils.h"
#include "Recommendation.h"

using namespace std;

int main(int argc,char* argv[]){	
	ifstream input_file, conf_file;
	ofstream output_file;
	int i,j,k = 4 ,L = 5,N,d,n_clusters,in,as,up,km = 0,validation = 0; // N = number of items(lines) in the file, d = number of coordinates (dimension)
	char* com;
	string line,temp_str;
	vector <struct User*> users;
	vector<struct Item <double>*> items;
	vector < vector<struct Item <double>*> > pnearest,cnearest; //pnearest neoghbors of every user
	vector<Cluster* > clusters;
	vector<Cluster* > old_clusters;
	vector < vector<struct Item <double>*> > totalclusters;
	vector < vector< pair<double,int> > > dist;
	map<int, struct Tweet*> totaltweets;
	vector< struct User*> cusers;
	int t;
	vector<double> s;
	double 	ov = 0.0;

	// to claculate time 
	double exec_time;


	srand (time(NULL));

	//command line parsing
	com_line_parser(argc,argv,input_file,output_file,validation);

	read_input(input_file,users,N,d,totaltweets);
	
	
	map<string, double> lex_map; // <- map (word) -> value
	read_lex(lex_map);	

	vector<vector<string>> bc_vect;
	read_bitcoins(bc_vect);

    output_file << "Cosine LSH" << endl;

	for(i = 0 ; i < users.size() ; i++){
	 	
	 	users[i]->Create_U(bc_vect,lex_map);
	
	}

	// for(i = 0 ; i < users.size() ; i++){
	// 	users[i]->Print_User();
	// }


    output_file << "Cosine Lsh" << endl;
	//---1st calc time
	clock_t tStart = clock();
	find_P_NN(users,pnearest,bc_vect.size());
	unrated_items(users,pnearest);
	u_problem(users,bc_vect,output_file);
	exec_time =  (double)(clock() - tStart)/CLOCKS_PER_SEC;
	output_file << "Execution time : " << fixed << setprecision(6) << exec_time <<endl;

	cout << "Cosine LSH Recommendation MAE: ";
	Validation(users);

	//read the input form project 2 and create table items
	read_oldinput(items);

	//read configuration file
	read_conf(k,L,n_clusters);

	//create iconic users
	Create_C(items,n_clusters,cusers,totaltweets,lex_map,bc_vect);

	//---2nd Calc time
	tStart = clock();
	find_P_NN(users,cusers,pnearest,bc_vect.size());
	unrated_items(users,pnearest);	
	c_problem(users,bc_vect,output_file);
	exec_time =  (double)(clock() - tStart)/CLOCKS_PER_SEC;
	output_file << "Execution time : " << fixed << setprecision(6) << exec_time <<endl;

	cout << "Cosine LSH Recommendation MAE: ";
	Validation(users);

    output_file << "Clustering" << endl;

	//---3rd calc time
	tStart = clock();
	clustering(users,totalclusters,d);
	unrated_items(users,totalclusters);	
	u_problem(users,bc_vect,output_file);
	exec_time =  (double)(clock() - tStart)/CLOCKS_PER_SEC;
	output_file << "Execution time : " << fixed << setprecision(6) << exec_time <<endl;
	
	cout << "Clustering Recommendation MAE: ";
	Validation(users);


	//---4th cacl time
	tStart = clock();
	clustering(users,cusers,totalclusters,d);;
	unrated_items(users,totalclusters);	
	c_problem(users,bc_vect,output_file);
	exec_time =  (double)(clock() - tStart)/CLOCKS_PER_SEC;
	output_file << "Execution time : " << fixed << setprecision(6) << exec_time <<endl;

	cout << "Clustering Recommendation MAE: ";
	Validation(users);
	
	return 1;
}