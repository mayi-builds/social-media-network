#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <stack>
#include <vector>
#include <cctype>
#include <ctime>
using namespace std;

int max(int& x,int& y){
	if(x>y) return x;
	return y;
}

int min(int& x,int& y){
	if(x<y) return x;
	return y;
}


/* TreeNode -- A Post */

class TreeNode{
public:
	string post_content;
	time_t created_timestamp;
	TreeNode* left;
	TreeNode* right;
	int height;
	TreeNode(string content):left(NULL),right(NULL),post_content(content),created_timestamp(time(0)),height(1){}
};

int height(TreeNode* node){
	if(node==NULL) return 0; /*Considering Empty tree has height 0 */
	return node->height;
}

/* Rotations in AVL Tree */

TreeNode* left_rotate(TreeNode* y){
	TreeNode* x=y->left;
	TreeNode* z=y->right;
	
	y->right=z->left;
	z->left=y;
	
	y->height=max(height(y->left),height(y->right))+1;
	z->height=max(height(z->left),height(z->right))+1;
	
	return z;
}

TreeNode* right_rotate(TreeNode* y){
	TreeNode* x=y->left;
	TreeNode* z=y->right;
	
	y->left=x->right;
	x->right=y;
	
	y->height=max(height(y->left),height(y->right))+1;
	x->height=max(height(x->left),height(x->right))+1;
	
	return x;
}

/* Insertion into an AVL Tree */

TreeNode* avl_insert(TreeNode* T,TreeNode* x){
	
	/* Key -- (x->created_timestamp) */
	
	if(T==NULL) return x;
	else if((x->created_timestamp)<(T->created_timestamp)) T->left=avl_insert(T->left,x);
	else T->right=avl_insert(T->right,x);
	
	T->height=max(height(T->left),height(T->right))+1;
	
	/* Balance Factor */
	int balance;
	if(T==NULL) balance=0;
	else balance=height(T->left)-height(T->right);
	
	/* RR -- [ONLY USEFUL CASE] */
	if(balance<-1 && (x->created_timestamp)>=(T->right->created_timestamp)) return left_rotate(T);
	
	/* LL */
	else if(balance>1 && (x->created_timestamp)<=(T->left->created_timestamp)) return right_rotate(T);
	
	/* RL */
	else if(balance<-1 && (x->created_timestamp)<=(T->right->created_timestamp)){
		T->right=right_rotate(T->right);
		return left_rotate(T);
	}
	
	/* LR */
	else if(balance>1 && (x->created_timestamp)>=(T->left->created_timestamp)){
		T->left=left_rotate(T->left);
		return right_rotate(T);
	}
	
	/* Node of balanced sub AVL Tree */
	return T;
}

/* An User -- A vertex in Undirected Graph */

class User{
public:
	string username;
	vector<string> friends;/* Friends (usernames) -- [Neighboring Vertices] */
	TreeNode* posts=NULL;/* An AVL Tree represented by root node as posts */
	
	User(string uname):username(uname){}
	
	/* Add a New Post by this User */
	
	void add_post(string post_content){
		
		TreeNode* newpost=new TreeNode(post_content);
		posts=avl_insert(posts,newpost);/* posts represents root node of AVL tree after inserting newpost */
		
	}
	
	/* Output Posts created by this User */
	
	void output_posts(int n){
		
		if(n==-1) n=100000;/* Something like infinte */
		
		int cnt=0;/* Number of Posts printed So far */
		stack<TreeNode*> stk;
		TreeNode* curr=posts; /* root -- AVL tree (Posts) */
		
		/* REVERSE INORDER TREE WALK [ITERATIVE] */
		
		while((curr!=NULL || !stk.empty()) && cnt<n){
			while(curr!=NULL){
				stk.push(curr);
				curr=curr->right;
			}
			TreeNode* u=stk.top();
			stk.pop();
			
			cout<<(u->post_content)<<endl;
			
			cnt++;
			
			curr=u->left;
		}
		
	}
};

/* A Suggestion */
typedef struct{
	string username;
	int mutual_cnt;
} person;

/* Checking Priority */
bool high_prior(person& p1,person& p2){
	
	/* Ranking: Number of Mutual Friends [high] -- (Ties) Alphabetical Username */
	
	if(p1.mutual_cnt>p2.mutual_cnt) return true;
	else if(p1.mutual_cnt<p2.mutual_cnt) return false;
	else return (p1.username)<(p2.username);
}

/* Sort Suggestions by Priority */
void sort_suggestions(vector<person>& arr){
	int sz=arr.size();
	for(int i=0;i<sz;++i){
		for(int j=sz-1;j>i;--j){
			if(high_prior(arr[j],arr[j-1])){
				person temp=arr[j-1];
				arr[j-1]=arr[j];
				arr[j]=temp;
			}
		}
	}
}

/* [LIST_FRIENDS] Sorting Friends of an User before printing */
void sort_friends(vector<string>& arr){
	int n=arr.size();
	for(int i=0;i<n;++i){
		int flag=0;
		for(int j=n-1;j>i;--j){
			if(arr[j]<arr[j-1]){
				string temp=arr[j-1];
				arr[j-1]=arr[j];
				arr[j]=temp;
				flag=1;
			}
		}
		if(!flag) break;
	}
}


/* SocialNet -- An Undirected Graph of Users(Vertices) */
class SocialNet{
public:
	/* Tagging username strings to corresponding User(vertex) */
	map<string,User*> allusers;
	
	/* Mapping LowerCase(converted) Username to Real Username (Created) */ 
	map<string,string> original;
	
	/* Add New User */
	void add_user(string uname){
		
		string real=uname;
		
		for(auto& c:uname) c=tolower(c);
		
		/* Skip if User already in Network */
		if(allusers.find(uname)!=allusers.end()) return;
		
		User* newuser=new User(uname);
		allusers[uname]=newuser;
		original[uname]=real;
	}
	
	/* Establish Bidirectional Friendship */
	void add_friend(string uname1,string uname2){
		
		for(auto& c:uname1) c=tolower(c);
		for(auto& c:uname2) c=tolower(c);
		
		/* Skip if aleast one of users doesn't exist */
		if(allusers.find(uname1)==allusers.end() || allusers.find(uname2)==allusers.end()) return;
		
		/* Skip if User adding himself as friend */
		if(uname1==uname2) return;
		
		/* Skip If already both are friends */
		for(auto frnd:allusers[uname1]->friends) if(frnd==uname2) return;
		
		allusers[uname1]->friends.push_back(uname2);
		allusers[uname2]->friends.push_back(uname1);
		
	}
	
	/* Print all Friends */
	void list_friends(string uname){
		
		for(auto& c:uname) c=tolower(c);
		
		/* Skip if User doesn't exist */
		if(allusers.find(uname)==allusers.end()) return;
		
		sort_friends(allusers[uname]->friends);
		
		for(auto& frnd:allusers[uname]->friends) cout<<original[frnd]<<endl;
		
	}
	
	/* New Suggestions */
	void suggest_friends(string uname,int n){
		
		for(auto& c:uname) c=tolower(c);
		
		/* Skip if User doesn't exist */
		if(allusers.find(uname)==allusers.end()) return;
		
		/* username--string and mutual_cnt--int (Our User,Friend of Friend) */
		map<string,int> mutual_frnd;
		
		for(auto& frnd:allusers[uname]->friends){
			
			for(auto& newfrnd:allusers[frnd]->friends){
				mutual_frnd[newfrnd]++;
			}	
			
		}
		
		/* Remove already friends */
		for(auto& frnd:allusers[uname]->friends){
			auto it=mutual_frnd.find(frnd);
			if(it!=mutual_frnd.end()) mutual_frnd.erase(it);
		}
		
		/* Remove Our User */
		auto my_it=mutual_frnd.find(uname);
		if(my_it!=mutual_frnd.end()) mutual_frnd.erase(my_it);
		
		/* All Suggestions*/
		vector<person> suggestion_list;
		for(auto& p:mutual_frnd) suggestion_list.push_back({p.first,p.second});
		
		/* Sort by priority */
		sort_suggestions(suggestion_list);
		
		/* if fewer candidates exists */
		n=min(n,(int) suggestion_list.size());
		
		for(int i=0;i<n;++i) cout<<original[suggestion_list[i].username]<<endl;
		
	}
	
	/* Seperation between 2 Users */
	int deg_of_sep(string uname1,string uname2){
		
		for(auto& c:uname1) c=tolower(c);
		for(auto& c:uname2) c=tolower(c);
		
		/* No Path exist if aleast one of users doesn't exist */
		if(allusers.find(uname1)==allusers.end() || allusers.find(uname2)==allusers.end()) return -1;
		
		/* BFS Iterative */
		string source=uname1,target=uname2;
		
		queue<string> track;
		map<string,int> visited_dist;/* Visted vertices and their distance from our source */
		
		track.push(source);
		visited_dist[source]=0;
		
		string curr;
		while(!track.empty()){
			curr=track.front();
			track.pop();
			for(auto& frnd:allusers[curr]->friends){
				if(visited_dist.find(frnd)==visited_dist.end()){
					visited_dist[frnd]=visited_dist[curr]+1;
					track.push(frnd);
				}
				/* Found Shortest Relation */
				if(frnd==target) return visited_dist[target];
			}
		}
		
		/* No Relation */
		return -1;
		
	}
	
};