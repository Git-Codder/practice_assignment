#include<bits/stdc++.h>
#define mod 1000000007

using namespace std;

// creating class
class Node{
public:
	int id;
	bool locked;
	int lockedDescendent;
	int lockerUserId;
	Node* parent;
	vector<Node*> children;

	Node(int x){
		this->id = x;
		this->lockedDescendent = 0;
		this->locked = false;
		this->parent = NULL;
		this->lockerUserId = -1;
	}

	~Node(){}
};


// create vectorMap to store the node corresponding integer  value
vector<Node*> TreeMap;

// locking the node
string lockNode(int node, int uId){
	Node* treeNode = TreeMap[node];
	if(treeNode->lockedDescendent > 0) return "false";

	Node* tempNode = treeNode;
	while(tempNode != NULL){
		if(tempNode->locked == true){
			return "false";
		}
		tempNode = tempNode->parent;
	}

	//lock the node and put the name of user who lock that node
	treeNode->lockerUserId = uId;
	treeNode->locked = true;

	//increment the locked descendent value in anscester nodes
	tempNode = treeNode->parent;
	while(tempNode != NULL){
		tempNode->lockedDescendent++;
		tempNode = tempNode->parent;
	}

	return "true";
}

//unlocking... the node
string unlockNode(int node, int uId){
	Node* treeNode = TreeMap[node];
	if(treeNode->locked == false || treeNode->lockerUserId != uId) return "false";

	//unlock the node and remove the name of user who locked that node
	treeNode->locked = false;
	treeNode->lockerUserId = -1;

	//decrement the locked descendent value in ansecester
	Node* tempNode = treeNode->parent;
	while(tempNode != NULL){
		tempNode->lockedDescendent--;
		tempNode = tempNode->parent;
	}

	return "true";
}



//check a node having all descendent same user who locked them all are locked or not
bool check(Node* root, int &uId, bool &atleastOne){
	if(root->locked == true) atleastOne = true;
	if(root->locked && root->lockerUserId != uId) return false;
	for(Node* child : root->children){
		if(check(child, uId, atleastOne) == false) return false;
	}
	return true;
}


//release the descendent node and upgrade it's anscester 
int releaseNode(Node* root){
	int cnt = 0;
	if(root->locked == true){
		cnt = 1;
	}
	root->lockerUserId = -1;
	root->locked = false;
	root->lockedDescendent = 0;
	for(Node* child : root->children){
		cnt += releaseNode(child);
	}
	return 1;
}

// upgrading the lock
string upgradeLock(int node, int uId){
	Node* treeNode = TreeMap[node];

	// check if node is already locked
	if(treeNode->locked == true) return "false";

	//check if node has a different user who has locked it's decescendent
	bool atleast = false;
	treeNode->lockerUserId = uId;
	bool ok = check(treeNode, uId, atleast);
	if(ok == false || atleast == false){
		treeNode->lockerUserId = -1;
		return "false";
	}

	//release the nodes
	int cnt = releaseNode(treeNode);
	cnt--;

	//upgrading lock the node 
	treeNode->locked = true;
	treeNode->lockerUserId = uId;
	treeNode->lockedDescendent = 0;

	Node* tempNode = treeNode->parent;
	while(tempNode != NULL){
		tempNode->lockedDescendent -= cnt;
		tempNode = tempNode->parent;
	}


	return "true";
}


void solve(){
	//clear golbal container
	TreeMap.clear();

	int n, m, q;
	cin >> n >> m >> q;

	// map the user inpute to a number
	map<string, int> nameToNode;
	vector<string> strNode(n);

	for(int i = 0; i < n; i++){
		cin >> strNode[i];
		nameToNode[strNode[i]] = i;
		TreeMap.push_back(new Node(i));
	}

	//create Tree
	int root = 0;
	queue<int> qu;
	qu.push(root);
	int i = 1;
	while(!qu.empty()){
		int root = qu.front();
		Node* treeNode = TreeMap[root];
		qu.pop();

		int j = min(n, i+m);
		for(;i < j; i++){
			Node* child = TreeMap[i];
			child->parent = treeNode;
			treeNode->children.push_back(child);
			qu.push(i);
		}
	}

	//taking operation, node, user who is locking
	int op, uId;
	string node;

	while(q--){
		cin >> op >> node >> uId;

		if(op == 1){
			cout << lockNode(nameToNode[node], uId) << endl;
		}else if(op == 2){
			cout << unlockNode(nameToNode[node], uId) << endl;
		}else{
			cout << upgradeLock(nameToNode[node], uId) << endl;
		}
	}
}

int32_t main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	solve();
	return 0;
}



















