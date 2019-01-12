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

void read_input(ifstream &input_file,vector <struct User*> &users,int &N,int &d){
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
            cout << "Existing user " << endl;
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
            cout << "New user " << endl;
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