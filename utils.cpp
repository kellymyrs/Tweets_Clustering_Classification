#include "utils.h"
void com_line_parser(int argc,char* argv[],ifstream& input_file,ofstream& output_file,int& validation){
	for( int i = 1 ; i < argc - 1 ; i++) {
		if(!strcmp(argv[i],"-d")){         //input file
			input_file.open(argv[i+1]);
	    	if(!input_file.is_open()){
	    		cout << "Don't have an input file" << endl ;
	    	}
    	}
		if(!strcmp(argv[i],"-o"))        //output file
			output_file.open(argv[i+1]);

		if(!strcmp(argv[i],"-validate"))      //validation
			validation = 1;		
	}

}

void read_input(ifstream &input_file,vector <struct User*> &users,int &N,int &d,int& P){
	string line,temp_str;
	struct Tweet* tweet;
    struct User* user; 
    int i = 1,tweetid,userid=-1,id;
    vector<string> w;

    while(getline(input_file,line)) {

        istringstream curr_line(line);

        //user id
        getline(curr_line, temp_str, '\t');
        id = atoi(temp_str.c_str());
        //cout << "User id = " << userid << endl;

        //tweet id
        getline(curr_line, temp_str, '\t');
        tweetid = atoi(temp_str.c_str());
        //cout << "Tweet id = " << tweetid << endl;

        d = 1;
        while (getline(curr_line, temp_str, '\t')) {

            //cout << temp_str.c_str() << " ";
            w.push_back(temp_str.c_str()); 
            d++;
        }
        cout << endl;

        tweet = new struct Tweet(tweetid,w);
        if( userid == id){ //add new tweet to the existing user
            users[i-1]->tweets.push_back(tweet);
        }
        else{//create a new user
            user = new struct User(userid , tweet);
            users.push_back(user);    
        }
        
        
        // auto res = users.find(userid);
        // if (res != users.end()) {
        //     cout << "Found " << res->first << '\n';
        //     res->second.tweets.push_back(tweet);

        // } 
        // else {
        //     std::cout << "Not found\n";
        //     users.emplace(make_pair(userid, user));
        // }

        w.clear();
        i++; 
    }

    input_file.close();
    
    d--;
    N = i-1;

    // for( i = 0 ; i < N ; i++ ){
    //     items[i]->Print_Item();
    // }
    

    cout << "Number of tweets = " << N << endl;
    cout << "Number of words = " << d << endl;
        
}

// void read_conf(ifstream& conf_file, int& k, int & L, int& n_clusters ){
// 	string line,temp_str;	

// 	while(getline(conf_file,line)){

//         istringstream curr_line(line);

//         getline(curr_line, temp_str, ' ');

//         if(!temp_str.compare("number_of_clusters:")){
        	
//         	getline(curr_line, temp_str, ' ');
//             n_clusters = atoi(temp_str.c_str());
            
//         }
//         else if(!temp_str.compare("number_of_hash_functions:")){

//         	getline(curr_line, temp_str, ' ');
//             if(temp_str.compare("")){
//         	   k = atoi(temp_str.c_str());
//             }
//         }
//         else if(!temp_str.compare("number_of_hash_tables:")){

//         	getline(curr_line, temp_str, ' ');
//             if(temp_str.compare("")){
//         	   L = atoi(temp_str.c_str());
//             }
//         }        
// 	}

// 	conf_file.close();

// 	cout << "Number of clusters = " << n_clusters << endl;
// 	cout << "Number of hash functions = " << k << endl;
// 	cout << "Number of Hashtables = " << L << endl;
	
// }

// int read_prompt(int& in,int& as,int& up){
//     char* com = new char[100];
//     cout << "Do you want to define the algorithms you want run?" << endl;
//     cin >> com;
//     if(!strcmp(com,"yes")){
        
//         cout << "Tell me the algorithm you want to use for Initialisation!" << endl;
//         cin >> com;
        
//         if(!strcmp(com,"Random_Selection")){
//             in = 0;
//         }
//         else if(!strcmp(com,"Kmeans")){
//             in = 1;
//         }
//         else{
//             cout << "Undefined algorithm" << endl;
//             return 0;
//         }

//         cout << "Tell me the algorithm you want to use for Assignment!" << endl;
//         cin >> com;

//         if(!strcmp(com,"Lloyds")){
//             as = 0;
//         }
//         else if(!strcmp(com,"Lsh")){
//             as = 1;
//         }
//         else if(!strcmp(com,"Hypercube")){
//             as = 2;
//         }
//         else{
//             cout << "Undefined algorithm" << endl;
//             return 0;
//         }

//         cout << "Tell me the algorithm you want to use for Update!" << endl;
//         cin >> com;

//         if(!strcmp(com,"Kmeans")){
//             up = 0;
//         }
//         else if(!strcmp(com,"Pam")){
//             up = 1;
//         }
//         else{
//             cout << "Undefined algorithm" << endl;
//             return 0;
//         }

//     }
//     else{
//         in = -1;
//         as = -1;
//         up = -1;
//     }
//     delete[] com;
//     return 1;
// }

// void run(int &k,int &d,int &L,int &N,int &m,vector<struct Item <double>*> &items,int &n_clusters,vector<Cluster* > &clusters,ofstream& output_file){
//     vector<Cluster* > old_clusters;  
//     int km = 0; 

//     for(int i = 0 ; i < 2 ; i++){

//         for(int j = 0 ; j < 3 ; j++){
        
//             for(int t = 0 ; t < 2 ; t++){

//                 //INITIALISIATION
//                 if(i == 0){
//                     random_selection(items,n_clusters,N,clusters);
//                     output_file << "Random Selection x ";                
//                 }
//                 else{
//                     kmeansplus(items,n_clusters,N,clusters,m);
//                     output_file << "K means++  x ";               
//                 }

//                 int r = 0;
//                 while(1){
//                     //ASSIGNMENT
//                     if(j == 0){
//                         lloyds(items,n_clusters,N,clusters,m);
//                         if(r == 0){
//                             output_file << "Lloyd's x ";
//                         }
//                     }
//                     else if(j == 1){
//                         lsh_search(k,d,L,N,m,items,n_clusters,clusters);
//                         if(r == 0){
//                             output_file << "Lsh Search x ";
//                         }                    
//                     }
//                     else{
//                         cube_search(k,d,L,N,m,items,n_clusters,clusters);
//                         if(r == 0){
//                             output_file << "Hypercube Search x ";
//                         }
//                     }

//                     old_clusters = clusters;

//                     //UPDATE
//                     if(t == 0){
//                         km = 1;
//                         kmeans(items,n_clusters,N,clusters,m,d);                        
//                         if(r == 0){
//                             output_file << "K means";
//                         }                    
//                     }
//                     else{
//                         pam(items,n_clusters,N,clusters,m);
//                         if(r == 0){
//                             output_file << "PAM ";
//                         }                    
//                     }

//                     int b = 0;
//                     for (i = 0; i < n_clusters ; i++){
//                         if(old_clusters[i]->cent->id == clusters[i]->cent->id){
//                             b++;
//                         }
//                     }   
//                     if( b == n_clusters ){
//                         break;
//                     } 
//                     r++;
//                 }
//                 //prints
//                 output_file << endl;
//                 if( m == 0){
//                     output_file << "Metric : Euclidean" << endl;
//                 }
//                 else{
//                     output_file << "Metric : Cosine" << endl;
//                 }
                

//                 if(!km){
//                     for (int l = 0; l < n_clusters; ++l){
//                         output_file << "Cluster-" << l+1 << " { size : " << clusters[l]->cl.size() << " , centroid : " << clusters[l]->cent->id << " }"<<endl;        
//                     }
//                 }
//                 else{
//                     for (int l = 0; l < n_clusters; ++l){
//                         output_file << "Cluster-" << l << " { size : " << clusters[l]->cl.size() << " , centroid : " ;

//                         for( int r = 0 ; r < clusters[l]->cent->coordinates.size() ; r++){
//                             output_file << clusters[l]->cent->coordinates[r] << "  " ;
//                         }

//                         output_file << " }"<< endl;      
//                     }
                              
//                 }  

//                 //EVALUATION
//                 silhouette(items,n_clusters,N,clusters,m,d);
//                 clusters.clear();             
//             }

//         }
//     }    
// } 

int read_lex(map<string, double> &lex) {
    ifstream lex_file;
    string line,temp_str;
    double curr_lex_val = 0.0;
    string temp_copy;
    // read file 
    lex_file.open(F_LEX);
    if (!lex_file.is_open()) {
        cout << "Cant find file lex_file please check the path\n";
        return -1;
    }


    while(getline(lex_file,line)) {
        istringstream curr_line(line);

        //read character
        getline(curr_line, temp_str, '\t');
        temp_copy = temp_str;

        // debug print
        //cout << "{" << temp_str << "}---{"; 

        //read value
        getline(curr_line, temp_str, '\t');
        curr_lex_val = atof(temp_str.c_str());

        lex[temp_copy] = curr_lex_val;

        //debug print
        //cout << curr_lex_val << "}"<< endl;
    }

    // print map storage
    /*
    for (auto& entry: lex) {
        cout << "{" <<entry.first << "}---{" << entry.second << "}" << '\n';
    }
    cout << "Number of lexicon words are -> " << lex.size() << endl;
    */
    
    lex_file.close();
    return 0;
}