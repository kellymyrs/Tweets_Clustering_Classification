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

void read_input(ifstream &input_file,vector <struct User*> &users,int &N,int d){
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


void find_P_NN(vector <struct User*> &users,vector<struct Item <double>*>& pnearest,int &d){
    Cosine_Lsh_Hashtable* co_h;
    uint32_t t_size;
    struct Item <double>* item;
    int k = 4 ,L = 5;
    double R = 0.9,temp_dist;
    vector< pair<double,int> > dist;
    vector<struct Item <double>*> range;

    //create Cosine LSH Hashtable
    co_h = new Cosine_Lsh_Hashtable(k,d,L);
    t_size = pow(2,(k-1));

    for (int i = 0; i < users.size(); ++i){ //inserting u vectors in the hashtable
        if(!users[i]->Ignore_User()){    
            item = new struct Item<double>(users[i]->id,users[i]->u,-1);

            //cout << "Inserting" << endl;
            co_h->Insert_Lsh_Hashtable(item,t_size,L);
        }
    }

    for(int j = 0 ; j < users.size() ; j++){
        if(!users[j]->Ignore_User()){

            //range search
            co_h->Get_Buckets(users[j]->u,L,t_size,range);
            cout << "range size is -> " << range.size() << endl;

            //find the distances from the neigbors and create a table with them to get the P nearest 
            for( int i = 0 ; i < range.size() ; i++){

                range[i]->Cosine_Distance(users[j]->u,temp_dist);
                cout << "will insert {dist,i}->" <<"{" << temp_dist << "," << i << "}" << endl;
                dist.push_back(make_pair(temp_dist,i));

            }

            cout << "Starting sorting" << endl;
            sort(dist.begin(),dist.end());
            
            cout << "The vector after sort operation is:\n" ; 
            for (int i=0; i < dist.size(); i++) { 
                cout << "i->" << i << endl;
                // "first" and "second" are used to access 
                // 1st and 2nd element of pair respectively 
                cout << dist[i].first << " "
                     << dist[i].second << endl; 
            } 

            //P nearest neighbors
            for(int i = 0 ; i < P ; i++ ){
                cout << dist[i].second << endl;
                pnearest.push_back(range[dist[i].second]);
            }


            for(int i = 0 ; i < pnearest.size() ; i++){
                cout <<"item_id"<< pnearest[j]->id << " ";
                for( int k = 0 ; k < d ; k++){
                    cout << pnearest[i]->coordinates[k] << " ";
                }
                cout << endl;
            }
            break;
        }
    }
}

void unrated_items(vector <struct User*> &users,vector<struct Item <double>*>& pnearest){

    for(int i = 0 ; i < users.size() ; i++){

        if(!users[i]->Ignore_User()){

            //for every unrated item
            for( int j = 0 ; j < users[i]->u.size() ; j++){

                if ( !(users[i]->uex[j]) ){ //if the item is unrated
                    users[i]->calculate_R(pnearest,j);
                }
            }
        }
    }
}

// void find simularity(vector <struct User*> &users,vector<struct Item <double>*>& pnearest){

// }