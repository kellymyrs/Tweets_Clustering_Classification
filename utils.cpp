#include "utils.h"
void com_line_parser(int argc,char* argv[],ifstream& input_file,ofstream& output_file,int & validation){
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

void read_input(ifstream &input_file,vector <struct User*> &users,int &N,int &d,map<int, struct Tweet*> &totaltweets){
	string line,temp_str;
	struct Tweet* tweet;
    struct User* user; 
    int i = 1,tweetid,userid,id=0;
    vector<string> w;

    while(getline(input_file,line)) {

        istringstream curr_line(line);

        //user id
        getline(curr_line, temp_str, '\t');
        userid = atoi(temp_str.c_str());
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
        //cout << endl;

        //cout << "READ INPUT" << endl; 
        tweet = new struct Tweet(tweetid,w);
        totaltweets[tweetid] = tweet;
        if( userid == id){ //add new tweet to the existing user
            //cout << "Existing user " << endl;
            if(users[i-1] != NULL && users[i-1]->tweets.size() != 0 ){
                //cout << "OK" << endl;
                users[i-1]->tweets.push_back(tweet);
            }
            else{
                cout << "PROBLEM !!!!!!!!" << endl;
            }
            //cout << "Tweet inserted ok" << endl;
        }
        else{//create a new user
            //cout << "New user " << endl;
            user = new struct User(userid , tweet);
            users.push_back(user); 
            id = userid;
            if( users.size() !=1 )
                i++;   
        }
        
        //users[0]->Print_User();
        // auto res = users.find(userid);
        // if (res != users.end()) {
        //     cout << "Found " << res->first << '\n';
        //     res->second.tweets.push_back(tweet);

        // } 
        // else {
        //     std::cout << "Not found\n";
        //     users.emplace(make_pair(userid, user));
        // }
        //cout << "Next iteration " << endl;
        w.clear(); 

    }

    input_file.close();
    
    d--;
    N = i-1;

    // for( i = 0 ; i < N ; i++ ){
    //     items[i]->Print_Item();
    // }
    

    cout << "Number of users = " << N << endl;
    cout << "Number of words = " << d << endl;
        
}


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

int read_bitcoins(vector<vector<string>> &bc_vect) {
    ifstream bitcoins_file;
    string line,temp_str;
    double curr_lex_val = 0.0;
    string temp_copy;

    vector<string> temp_vect;

    // read file 
    bitcoins_file.open(F_BIT);
    if (!bitcoins_file.is_open()) {
        cout << "Cant find file lex_file please check the path\n";
        return -1;
    }

    while(getline(bitcoins_file,line)) {       

        istringstream curr_line(line);

        while (getline(curr_line, temp_str, '\t')) {
            temp_vect.push_back(temp_str); 
        }
        bc_vect.push_back(temp_vect);
        temp_vect.clear();
    }

    //print vector
    /*
    for (auto& vec : bc_vect) {
        for (int i = 0; i < vec.size() ; i++) {
            cout <<"|" << vec[i] << "|";
        }
        
        cout << "\n";
    }
    */

    bitcoins_file.close();

    return 0;
}




void read_oldinput(vector<struct Item <double>*> &items){
    string line,temp_str;
    vector<double> coordinates; //coordinates
    struct Item <double>* item;
    int i = 1,ident;
    ifstream oldinput_file;
    int m = 1; //cosine metric

    oldinput_file.open("twitter_dataset_small_v2.csv");
    if(!oldinput_file.is_open()){
        cout << "Cannnot open the old input file" << endl ;
    }

    while(getline(oldinput_file,line)) {

        ident = i;
        
        istringstream curr_line(line);
        getline(curr_line, temp_str, ',');
        
        // d = 1;
        while (getline(curr_line, temp_str, ',')) {

            //cout << stod(temp_str.c_str()) << " ";
            coordinates.push_back(atof(temp_str.c_str())); 
            // d++;
        }
        //cout << endl;

        item = new struct Item<double>(ident , coordinates, -1);
        items.push_back(item);

        coordinates.clear();
        
        i++;
    }

    oldinput_file.close();
    
    // d--;
    // N = i-1;

    // // for( i = 0 ; i < N ; i++ ){
    // //     items[i]->Print_Item();
    // // }
    
    // cout << "Number of points = " << N << endl;
    // cout << "Dimension = " << d << endl;
        
}

void read_conf(int& k, int & L, int& n_clusters ){
    ifstream conf_file;
    string line,temp_str;   

    conf_file.open("cluster.conf");
    if(!conf_file.is_open()){
        cout << "Cannnot open the configuration file" << endl ;
    }   

    while(getline(conf_file,line)){

        istringstream curr_line(line);

        getline(curr_line, temp_str, ' ');

        if(!temp_str.compare("number_of_clusters:")){
            
            getline(curr_line, temp_str, ' ');
            n_clusters = atoi(temp_str.c_str());
            
        }
        else if(!temp_str.compare("number_of_hash_functions:")){

            getline(curr_line, temp_str, ' ');
            if(temp_str.compare("")){
               k = atoi(temp_str.c_str());
            }
        }
        else if(!temp_str.compare("number_of_hash_tables:")){

            getline(curr_line, temp_str, ' ');
            if(temp_str.compare("")){
               L = atoi(temp_str.c_str());
            }
        }        
    }

    conf_file.close();

    cout << "Number of clusters = " << n_clusters << endl;
    cout << "Number of hash functions = " << k << endl;
    cout << "Number of Hashtables = " << L << endl;
    
}


// void u_problem(vector <struct User*> &users,vector < vector< pair<double,int> > > &dist,ofstream& output_file){
//     vector< pair<int,int> > coins; //number of neighbors that talk about the coin,number of coin
    
//     for(int i = 0 ; i < users.size() ; i++ ){

//         if(!users[i]->Ignore_User()){

//             //for every unrated item
//             for( int j = 0 ; j < users[i]->u.size() ; j++){

//                 if ( !(users[i]->uex[j]) ){ //if the item is unrated
                    
//                     //search neighbors
//                     for(int n = 0; n < dist[i].size ; n++){

//                         if( users[dist[n][0].second]->uex[n] ){
//                             coins
//                         } 
//                     }

//                 }
//                 else{
//                     coins[j].first = -1;
//                     coins[j].second = j;
//                 }
//             }
//             //print coins

//             coins.clear();
//         }
//     }
// }


// void find simularity(vector <struct User*> &users,vector<struct Item <double>*>& pnearest){

// }