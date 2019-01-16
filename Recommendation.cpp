#include "Recommendation.h"

void find_P_NN(vector <struct User*> &users,vector < vector<struct Item <double>*> >& totalpnearest,int d){
    Cosine_Lsh_Hashtable* co_h;
    uint32_t t_size;
    struct Item <double>* item;
    int k = 4 ,L = 5;
    double R = 0.9,temp_dist;
    vector<struct Item <double>*> range; //items in the same bucket
    vector<struct Item <double>*> pnearest; //pnearest neibors

    //create Cosine LSH Hashtable
    co_h = new Cosine_Lsh_Hashtable(k,d,L);
    t_size = pow(2,(k-1));

    for (int i = 0; i < users.size(); ++i){ //inserting u vectors in the hashtable
        if(!users[i]->Ignore_User()){

            if(users[i]->norm){    
                item = new struct Item<double>(users[i]->id,users[i]->u,-1);

            }
            else{
                item = new struct Item<double>(users[i]->id,users[i]->ux,-1);            
            }

            //cout << "Inserting" << endl;
            co_h->Insert_Lsh_Hashtable(item,t_size,L);   
        }
    }

    cout << users.size() << endl;

    vector< pair<double,int> >temp;
    for(int j = 0 ; j < users.size() ; j++){

        if(!users[j]->Ignore_User()){

            if(users[j]->norm){
                //range search
                co_h->Get_Buckets(users[j]->u,L,t_size,range);
                //cout << "range size is -> " << range.size() << endl;

                //find the distances from the neigbors and create a table with them to get the P nearest 
                for( int i = 0 ; i < range.size() ; i++){

                    range[i]->Cosine_Distance(users[j]->u,temp_dist);
                    //cout << "will insert {dist,i}->" <<"{" << temp_dist << "," << i << "}" << endl;
                    temp.push_back(make_pair(temp_dist,i));

                }
            }
            else{
                //range search
                co_h->Get_Buckets(users[j]->ux,L,t_size,range);
                //cout << "range size is -> " << range.size() << endl;

                //find the distances from the neigbors and create a table with them to get the P nearest 
                for( int i = 0 ; i < range.size() ; i++){

                    range[i]->Cosine_Distance(users[j]->ux,temp_dist);
                    //cout << "will insert {dist,i}->" <<"{" << temp_dist << "," << i << "}" << endl;
                    temp.push_back(make_pair(temp_dist,i));

                }                
            }

            //cout << "Starting sorting" << endl;
            sort(temp.begin(),temp.end());
            
            //cout << "The vector after sort operation is:\n" ; 
            // for (int i=0; i < temp.size(); i++) { 
            //     cout << "i->" << i << endl;
            //     // "first" and "second" are used to access 
            //     // 1st and 2nd element of pair respectively 
            //     cout << temp[i].first << " "
            //          << temp[i].second << endl; 
            // } 

            //P nearest neighbors
            for(int i = 0 ; i < P ; i++ ){
                //cout << temp[i].second << endl;
                pnearest.push_back(range[temp[i].second]);
            }

            //print pnearest
            // for(int i = 0 ; i < pnearest.size() ; i++){
            //     cout <<"item_id"<< pnearest[j]->id << " ";
            //     for( int k = 0 ; k < d ; k++){
            //         cout << pnearest[i]->coordinates[k] << " ";
            //     }
            //     cout << endl;
            // }

            cout << "Found pnearest for user : " << users[j]->id << endl;

            totalpnearest.push_back(pnearest);
            pnearest.clear();
            temp.clear();
        }
    }
}

void find_P_NN(vector <struct User*> &users,vector< struct User*> &cusers,vector < vector<struct Item <double>*> >& totalpnearest,int d){
    Cosine_Lsh_Hashtable* co_h;
    uint32_t t_size;
    struct Item <double>* item;
    int k = 4 ,L = 5;
    double R = 0.9,temp_dist;
    vector<struct Item <double>*> range; //items in the same bucket
    vector<struct Item <double>*> pnearest; //pnearest neibors

    //create Cosine LSH Hashtable
    co_h = new Cosine_Lsh_Hashtable(k,d,L);
    t_size = pow(2,(k-1));

    for (int i = 0; i < cusers.size(); ++i){ //inserting u vectors in the hashtable
        if(!cusers[i]->Ignore_User()){

            if(cusers[i]->norm){    
                item = new struct Item<double>(cusers[i]->id,cusers[i]->u,-1);

            }
            else{
                item = new struct Item<double>(cusers[i]->id,cusers[i]->ux,-1);            
            }

            //cout << "Inserting" << endl;
            co_h->Insert_Lsh_Hashtable(item,t_size,L);   
        }
    }

    cout << users.size() << endl;

    vector< pair<double,int> >temp;
    for(int j = 0 ; j < users.size() ; j++){

        if(!users[j]->Ignore_User()){

            if(users[j]->norm){
                //range search
                co_h->Get_Buckets(users[j]->u,L,t_size,range);
                //cout << "range size is -> " << range.size() << endl;

                //find the distances from the neigbors and create a table with them to get the P nearest 
                for( int i = 0 ; i < range.size() ; i++){

                    range[i]->Cosine_Distance(users[j]->u,temp_dist);
                    //cout << "will insert {dist,i}->" <<"{" << temp_dist << "," << i << "}" << endl;
                    temp.push_back(make_pair(temp_dist,i));

                }
            }
            else{
                //range search
                co_h->Get_Buckets(users[j]->ux,L,t_size,range);
                //cout << "range size is -> " << range.size() << endl;

                //find the distances from the neigbors and create a table with them to get the P nearest 
                for( int i = 0 ; i < range.size() ; i++){

                    range[i]->Cosine_Distance(users[j]->ux,temp_dist);
                    //cout << "will insert {dist,i}->" <<"{" << temp_dist << "," << i << "}" << endl;
                    temp.push_back(make_pair(temp_dist,i));

                }                
            }

            //cout << "Starting sorting" << endl;
            sort(temp.begin(),temp.end());
            
            //cout << "The vector after sort operation is:\n" ; 
            // for (int i=0; i < temp.size(); i++) { 
            //     cout << "i->" << i << endl;
            //     // "first" and "second" are used to access 
            //     // 1st and 2nd element of pair respectively 
            //     cout << temp[i].first << " "
            //          << temp[i].second << endl; 
            // } 

            //P nearest neighbors
            for(int i = 0 ; i < P ; i++ ){
                //cout << temp[i].second << endl;
                pnearest.push_back(range[temp[i].second]);
            }

            //print pnearest
            // for(int i = 0 ; i < pnearest.size() ; i++){
            //     cout <<"item_id"<< pnearest[j]->id << " ";
            //     for( int k = 0 ; k < d ; k++){
            //         cout << pnearest[i]->coordinates[k] << " ";
            //     }
            //     cout << endl;
            // }

            cout << "Found pnearest for user : " << users[j]->id << endl;

            totalpnearest.push_back(pnearest);
            pnearest.clear();
            temp.clear();
        }
    }
}

void clustering(vector <struct User*> &users,vector < vector<struct Item <double>*> >& totalclusters,int d){
    Cosine_Lsh_Hashtable* co_h;
    uint32_t t_size;
    struct Item <double>* item;
    int k = 4 ,L = 5;
    double R = 0.9,temp_dist;
    vector<struct Item <double>*> range; //items in the same bucket
    vector<struct Item <double>*> pnearest; //pnearest neibors
    vector<struct Item <double>*> items; //table with the users
    vector<Cluster*> clusters;
    vector<Cluster*> old_clusters;
    vector< vector <Tweet*>> newclusters;
    vector <Tweet*> cluster;
    int as =1;

    //create table items with the users and the vectors u
    for( int i = 0 ; i < users.size() ; i++){
        if(!users[i]->Ignore_User()){
            if(users[i]->norm){
                item = new struct Item<double>(users[i]->id,users[i]->u,-1);            
            }
            else{
                item = new struct Item<double>(users[i]->id,users[i]->ux,-1); 
            }
            items.push_back(item);
        }
    }

    cout << "Created table items with size : " << items.size() << endl; 

    //clustering to the users of the table items

    //INITIALISIATION
    int N = items.size();
    int m = 0; //euclidean metric
    int n_clusters = 100;
    random_selection(items,n_clusters,N,clusters);

    cout << "Random selection OK" << endl;

    // while(as != -1){
        //ASSIGNMENT
        lloyds(items,n_clusters,N,clusters,m);

        old_clusters = clusters;

        //UPDATE
        d = items[0]->coordinates.size();
        kmeans(items,n_clusters,N,clusters,m,d);

    //     int b = 0;
    //     for (int i = 0; i < n_clusters ; i++){
    //         if(old_clusters[i]->cent->id == clusters[i]->cent->id){
    //             b++;
    //         }
    //     }   
    //     if( b == n_clusters ){
    //         break;
    //     }
    // }                        

    cout << "Clustering ok!!" << endl;
    

    vector< pair<double,int> >temp;
    for(int j = 0 ; j < items.size() ; j++){

        if(!users[j]->Ignore_User()){

            //find the neigbors of the user in the cluster
            totalclusters.push_back(clusters[items[j]->cluster_id]->cl);


            cout << "Found cluster neighbors for user : " << users[j]->id << endl;
        }
    }
}

void clustering(vector <struct User*> &users,vector< struct User*> &cusers,vector < vector<struct Item <double>*> >& totalclusters,int d){
    Cosine_Lsh_Hashtable* co_h;
    uint32_t t_size;
    struct Item <double>* item;
    int k = 4 ,L = 5;
    double R = 0.9,temp_dist;
    vector<struct Item <double>*> range; //items in the same bucket
    vector<struct Item <double>*> pnearest; //pnearest neibors
    vector<struct Item <double>*> items; //table with the users
    vector<Cluster* > clusters,old_clusters;
    vector< vector <Tweet*>> newclusters;
    vector <Tweet*> cluster;
    int as =1;

    for( int i = 0 ; i < cusers.size() ; i++){
        if(!cusers[i]->Ignore_User()){
            if(cusers[i]->norm){
                item = new Item<double>(cusers[i]->id,cusers[i]->u,-1);            
            }
            else{
                item = new Item<double>(cusers[i]->id,cusers[i]->ux,-1); 
            }
            items.push_back(item);
        }
    }

    for(int j ; j < users.size() ; j++){

        //create table items with the iconic users and the vectors u and the current user
        item = new Item<double>(users[j]->id,users[j]->u,-1);  
        items.push_back(item);

        cout << "Created table items" << endl; 

        //clustering to the users of the table items

        //INITIALISIATION
        int N = cusers.size() + 1;
        int m = 0; //euclidean metric
        int n_clusters = 100;
        random_selection(items,n_clusters,N,clusters);

        while(as != -1){
            //ASSIGNMENT
            lloyds(items,n_clusters,N,clusters,m);

            old_clusters = clusters;

            //UPDATE
            int d = items[0]->coordinates.size();
            kmeans(items,n_clusters,N,clusters,m,d);

            int b = 0;
            for (int i = 0; i < n_clusters ; i++){
                if(old_clusters[i]->cent->id == clusters[i]->cent->id){
                    b++;
                }
            }   
            if( b == n_clusters ){
                break;
            }
        }  
        cout << "Clustering ok!!" << endl;

        totalclusters.push_back(clusters[items[cusers.size()]->cluster_id]->cl);
        
        cout << "Found cluster neighbors for user : " << users[j]->id << endl;
        
        items.pop_back();

    }
}

void unrated_items(vector <struct User*> &users,vector < vector<struct Item <double>*> >& pnearest){

    for(int i = 0 ; i < users.size() ; i++){

        if(!users[i]->Ignore_User()){

            //for every unrated item
            for( int j = 0 ; j < users[i]->u.size() ; j++){

                if ( !(users[i]->uex[j]) ){ //if the item is unrated
                    users[i]->calculate_R(pnearest[i],j);
                }
            }
            cout << "Found unrated items user : " << users[i]->id << endl;
        }
    }
}

void u_problem(vector <struct User*> &users,vector<vector<string>> &bc_vect,ofstream& output_file){
    vector< pair<double,int> > coins;

    for(int i = 0 ; i < users.size() ; i++ ){

        if(!users[i]->Ignore_User()){

            //for every unrated item
            for( int j = 0 ; j < users[i]->u.size() ; j++){    
                
                if ( !(users[i]->uex[j]) ){ //if the item is unrated

                    if(users[i]->norm){
                        //insert to coins
                        coins.push_back(make_pair(users[i]->u[j],j));                        
                    }
                    else{
                        coins.push_back(make_pair(users[i]->ux[j],j)); 
                    }
                    
                }

            }
            sort(coins.begin(),coins.end());

            //print
            output_file << "<u" << users[i]->id << "> ";
            for( int j = 0 ; j < 5 ; j++){ 
                string s = bc_vect[coins[j].second][0];             
                output_file << s << " ";
            }
            output_file << endl;
            coins.clear();
        }
    }
}

void Create_C(vector<struct Item <double>*> &items,int &n_clusters,vector< struct User*> &cusers,map<int, struct Tweet*> &totaltweets,map<string, double>& lex,vector <vector<string>>& bc_vect){
    vector<Cluster* > clusters,old_clusters;
    vector< vector <Tweet*>> newclusters;
    vector <Tweet*> cluster;
    int as =1;
    
    //clustering to the tweets of the table items

    //INITIALISIATION
    int N = items.size();
    int m = 1; //cosine metric
    kmeansplus(items,n_clusters,N,clusters,m);

    while(as != -1){
        //ASSIGNMENT
        lloyds(items,n_clusters,N,clusters,m);

        old_clusters = clusters;

        //UPDATE
        int d = items[0]->coordinates.size();
        kmeans(items,n_clusters,N,clusters,m,d);

        int b = 0;
        for (int i = 0; i < n_clusters ; i++){
            if(old_clusters[i]->cent->id == clusters[i]->cent->id){
                b++;
            }
        }   
        if( b == n_clusters ){
            break;
        }
    }                        

    cout << "Clustering ok!!" << endl;

    //create new table cluster with tweets
    for( int i = 0 ; i < n_clusters ; i++){

        //for every item in the cluster
        for (int j = 0; j < clusters[i]->cl.size() ; j++){
            
            //map the item with the tweet
            Tweet* tweet = totaltweets[clusters[i]->cl[j]->id];

            cluster.push_back(tweet);
        }

    
        newclusters.push_back(cluster);
        cluster.clear();    
    }

    cout << "Created clusters filled with tweets" << endl;

    //create iconic users
    User* user;
    for( int i = 0 ; i < n_clusters ; i++){
        user = new User(i,newclusters[i]);
        cusers.push_back(user);
        cout << "Created iconic User : " << i << endl;
        cout << "Number of tweets of the iconic user : " << newclusters[i].size() << endl;
        cusers[i]->Create_U(bc_vect,lex);
    }
    cout << "Created iconic users" << endl;

}

void c_problem(vector <struct User*> &users,vector<vector<string>> &bc_vect,ofstream& output_file){
    vector< pair<double,int> > coins;

    output_file << endl;
    for(int i = 0 ; i < users.size() ; i++ ){

        if(!users[i]->Ignore_User()){

            //for every unrated item
            for( int j = 0 ; j < users[i]->u.size() ; j++){    
                
                if ( !(users[i]->uex[j]) ){ //if the item is unrated

                    if(users[i]->norm){
                        //insert to coins
                        coins.push_back(make_pair(users[i]->u[j],j));                        
                    }
                    else{
                        coins.push_back(make_pair(users[i]->ux[j],j)); 
                    }
                    
                }

            }
            sort(coins.begin(),coins.end());

            //print
            output_file << "<u" << users[i]->id << "> ";
            for( int j = 0 ; j < 2 ; j++){ 
                string s = bc_vect[coins[j].second][0];             
                output_file << s << " ";
            }
            output_file << endl;
            coins.clear();
        }
    }
}

void Validation(vector <struct User*> &users) {
    vector<pair<int,int>> fold_v; // (int,int)->(user_index,index_coin)
    vector<pair<int,int>> training,test;
    // create dataset
    for (int i = 0 ; i < users.size(); i++) {
        for (int j = 0 ; j < users[i]->u.size(); j++) {
            if (users[i]->uex[j]) {
                fold_v.push_back(make_pair(i,j));
            }
        }
    }

    int split_f =  int(floor(double(fold_v.size())/10.0));
    int up = 0;
    int down = split_f;

    double error = 0.0;
    
    // 10-fold validation
    for (int i = 0; i < 10; i++) {
        
        for (int j1 = 0; j1 < up; j1++) {
            test.push_back(fold_v[j1]);
        }
        
        for (int j_h = up; j_h < down; j_h++) {
            training.push_back(fold_v[j_h]);        
        }
        
        for (int j2 = down; j2 < fold_v.size(); j2++) {
            test.push_back(fold_v[j2]);
        }

        //create items for calculate R
        struct Item<double>* item;
        vector < struct Item<double> *> test_items;
        for(int it = 0 ; it < test.size() ; it++){
            item = new struct Item<double>(0,users[test[it].first]->u,-1);
            test_items.push_back(item);
        }
        
        // for every training shit
        for (int jj = 0 ; jj < training.size() ; jj++) {

                double r = users[training[jj].first]->u[training[jj].second];
                users[training[jj].first]->calculate_R(test_items,training[jj].second);
                double p = users[training[jj].first]->u[training[jj].second];
                error += abs(p-r);
        }
        

        up = down;
        down += split_f;
        
        test_items.clear();
        training.clear();
        test.clear();
    }
    double mean_error = 1.0/fold_v.size()*error;
    cout << mean_error << endl;
}
