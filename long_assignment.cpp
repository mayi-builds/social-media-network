#include <iostream>
#include "classes.hpp"
using namespace std;

int main(){
	
	/* Creating a Social Network name myNetwork -- An Undirected Graph */
	SocialNet myNetwork;
	
	/* Name of Operation */
	string cmdname;
	while(cin>>cmdname){
		
		if(cmdname=="ADD_USER"){
			string uname;
			cin>>uname;
			
			myNetwork.add_user(uname);
			
		}
		else if(cmdname=="ADD_FRIEND"){
			string uname1,uname2;
			cin>>uname1>>uname2;
			
			myNetwork.add_friend(uname1,uname2);
			
		}
		else if(cmdname=="LIST_FRIENDS"){
			string uname;
			cin>>uname;
			
			myNetwork.list_friends(uname);
			
			/*Empty Line Seperation */
			cout<<endl;
		}
		else if(cmdname=="SUGGEST_FRIENDS"){
			string uname;
			int n;
			cin>>uname>>n;
			
			myNetwork.suggest_friends(uname,n);
			
			/*Empty Line Seperation */
			cout<<endl;
		}
		else if(cmdname=="DEGREES_OF_SEPARATION"){
			string uname1,uname2;
			cin>>uname1>>uname2;
			
			cout<<myNetwork.deg_of_sep(uname1,uname2)<<endl;
			
			/*Empty Line Seperation */
			cout<<endl;
			
		}
		else if(cmdname=="ADD_POST"){
			string uname,content;
			cin>>uname;
			
			cin.ignore();
			getline(cin,content);
			
			/* Changing to ByDefault lowercase-format of username to process */ 
			for(auto& c:uname) c=tolower(c);
			
			/* Skip if User doesn't exist */
			if(myNetwork.allusers.find(uname)==myNetwork.allusers.end()) continue;
			
			myNetwork.allusers[uname]->add_post(content);
			
		}
		else if(cmdname=="OUTPUT_POSTS"){
			string uname;
			int n;
			cin>>uname>>n;
			
			for(auto& c:uname) c=tolower(c);
			
			/* Skip if User doesn't exist */
			if(myNetwork.allusers.find(uname)==myNetwork.allusers.end()) continue;
			
			myNetwork.allusers[uname]->output_posts(n);
			
			/*Empty Line Seperation */
			cout<<endl;
			
		}
		else if(cmdname=="EXIT") break;
	}
	
	return 0;
}