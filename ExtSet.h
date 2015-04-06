//Content: Set implementation 
//Author: X.Z.
//Creation Date: 3/5/2014
//Description: Use Binary Search Tree. 

#ifndef ExtSet_h
#define ExtSet_h

#include <iostream>
#include <utility>
#include <vector>
#include <list>

template<typename T> class TreeNode{
public:
	TreeNode() : left(NULL), right(NULL) {}
	TreeNode(const T& init) : value(init), left(NULL), right(NULL) {}
	T value;
	
	TreeNode* left; 
	TreeNode* right;
};

template<typename T> class tree_iterator{
public:
	tree_iterator() : ptr(NULL) {}
	tree_iterator(TreeNode<T>* p) : ptr(p) {}
	tree_iterator(const tree_iterator& old) : ptr(old.ptr) {}
	~tree_iterator() {}

	tree_iterator& operator=(const tree_iterator & old){ ptr = old.ptr; return *this; }

	//operator* gives access to the value inside the iterator
	const T& operator*() const { return ptr->value; }  //TODO; 
	
	//comparison operator all == and !=
	bool operator==(const tree_iterator& old) { return old.ptr == ptr; }
	bool operator!=(const tree_iterator& old) { return old.ptr != ptr; }
private:
	TreeNode<T> *ptr;
};
//Definition of Set class, templated
template<typename T> class ExtSet{
public:
	ExtSet() : root(NULL), size(0) {}
	ExtSet(const ExtSet<T>& old){ //TODO:
		root = this->copy_tree(old.root);
	}
	~ExtSet() { this->destroyTree(root); root = NULL; }
	//assignment operator
	ExtSet& operator=(const ExtSet<T>& old) { //TODO: 
		if (&old != this){
			this->destroyTree(root);
			root = this->copy_tree(old.root);
			size = old.size;
		}
	}
	//This typedef only works within this class
	typedef tree_iterator<T> iterator;
	int getsize() const { return size; }
	bool operator==(const ExtSet<T>& old) const { return (old.root == this->root;) }// TODO: old need point, this use ->

	//Operations List
	iterator find(const T& key_value) {return find(key_value, root); }
	std::pair<iterator, bool> insert(T const& key_value){ return insert(key_value, root); }
	int erase(T const& key_value) { return erase(key_value, root); }


	//Output and Print Trees
	friend std::ostream& operator<<(std::ostream& ostr, const ExtSet<T>& s){
		s.print_in_order(ostr, s.root); //TODO
		return ostr;
	}
	void breadth_first_search() const{
		//breadth_first_search(root);
		breadth_first_search_v2(root);
	}
	void print_as_sideways_tree(std::ostream& ostr) const{
		print_as_sideways_tree(ostr, root, 0);
	}
	
	//Iterator Operations
	iterator begin() const{
		if (root == NULL) return iterator(NULL);
		TreeNode<T> *p = root;
		while (p->left)
			p = p->left;
		return iterator(p);
	}
	iterator end() const{
		return iterator(NULL);
	}

private:
	//Presentation of class
	TreeNode<T> *root;
	unsigned int size;

	//Similary to traversal
	TreeNode<T>* copy_tree(TreeNode<T> *old_root){
		if (!old_root)
			return NULL;
		TreeNode<T> *p = new TreeNode<T>(old_root->value);
		if (old_root->left)
			p->left = copy_tree(old_root->left);
		if (old_root->right)
			p->right = copy_tree(old_root->right);
		return p;

	}
	//Destroy the whole Tree, Recursion is easy.
	void destroyTree(TreeNode<T>* p){
		if (p->left)
			destroyTree(p->left);
		if (p->right)
			destroyTree(p->right);
		delete p;

	}

	iterator find(const T& key_value, TreeNode<T>* p){
		if (p == NULL)
			return iterator(NULL);
		else if (key_value < p->value)
			return find(key_value, p->left);
		else if (key_value>p->value)
			return find(key_value, p->right);
		else
			return iterator(p);
	}

	std::pair<iterator, bool> insert(const T& key_value, TreeNode<T>*& p){ //TODO: use *&
		if (p == NULL){
			p = new TreeNode<T>(key_value);
			this->size++;
			return std::pair<iterator, bool>(iterator(p), true);
		}
		else if (key_value < p->value)
			return insert(key_value, p->left);
		else if (key_value>p->value)
			return insert(key_value, p->right);
		else
			return std::pair<iterator, bool>(iterator(p), false);
	}
	//Erase: find and then replace.Three cases:(1) No child, (2) One child (3) Two children.
	//Not a good idea to use other functions such as find(), because its retval is iterator...
	//Must access to the parent node.
	int erase(T const& key_value, TreeNode<T> *p){  //TODO: 
		if (p == NULL) {
			std::cout << "NULL starting Node. Cannot Erase." << std::endl;
			return 0;
		}
		//Find the key and its parent, note the root node case: parent=NULL.
		TreeNode<T> *parent = NULL, *pos=NULL;
		while (p){
			if (key_value > p->value){
				parent = p;
				p = p->right;
			}			
			else if (key_value < p->value){
				parent = p;
				p = p->left;
			}
			else{
				pos = p;
				break;
			}
				
		}
		//Determine how many child Nodes in target position
		if (pos->left == NULL && pos->right == NULL){
			//No child nodes
			if (pos != root){
				if (parent->left == pos)
					parent->left = NULL;
				else
					parent->right = NULL;
			}
			delete pos;
			pos = NULL;
		}
		else if (pos->left != NULL && pos->right == NULL){
			//One child at left
			if (parent->left == pos)
				parent->left = pos->left;
			else
				parent->right = pos->left;
			delete pos;
			pos = NULL;

		}
		else if (pos->left == NULL && pos->right != NULL){
			//One child at right
			if (parent->left == pos)
				parent->left = pos->right;
			else
				parent->right = pos->right;
			delete pos;
			pos = NULL;
		}
		else{
			//Two children below
			TreeNode<T>* minPos = findMin(pos->right);
			pos->value = minPos->value;
			erase(minPos->value, pos->right);//Recursive
		}
		size--;
		return 1;

		
	}

	//find the minimum Node at the right side of this pointer
	TreeNode<T>* findMin(TreeNode<T> *p){
		while (p->left)
			p = p->left;
		return p;
	}

	void print_in_order(std::ostream& ostr, const TreeNode<T>* p) const{
		if (p == NULL) return;
		else {
			print_in_order(ostr, p->left);
			std::cout << p->value << "\n";
			print_in_order(ostr, p->right);
		}
	}

	void print_pre_order(std::ostream& ostr, const TreeNode<T>* p) const{ //TODO: seems not correct
		if (p == NULL) return;
		else {
			std::cout << p->value << "\n";
			print_in_order(ostr, p->left);
			print_in_order(ostr, p->right);
		}
	}

	void print_post_order(std::ostream& ostr, const TreeNode<T>* p) const{
		if (p == NULL) return;
		else {
			print_in_order(ostr, p->left);
			print_in_order(ostr, p->right);
			std::cout << p->value << "\n";
		}
	}

	void print_as_sideways_tree(std::ostream& ostr, const TreeNode<T>*p, int depth) const{
		if (p) {
			print_as_sideways_tree(ostr, p->right, depth + 1);
			for (int i = 0; i<depth; ++i) ostr << "    ";
			ostr << p->value << "\n";
			print_as_sideways_tree(ostr, p->left, depth + 1);
		}
	}


	void breadth_first_search(TreeNode<T> *p) const {
		//From Wikipedia C++ Implementation
		std::list<TreeNode<T>* > unvisited, visited;
		TreeNode<T>* curNode;
		unvisited.push_back(p);
		//Seems visited is not necesseary
		while (!unvisited.empty()){
			curNode=unvisited.front();
			if (curNode->left)
				unvisited.push_back(curNode->left);
			if (curNode->right)
				unvisited.push_back(curNode->right);
			visited.push_back(curNode);
			std::cout << curNode->value << std::endl;
			unvisited.pop_front();
		}

	}
	//Another BFS implementation of BST
	void breadth_first_search_v2(TreeNode<T> *p) const{
		std::list<TreeNode<T>* >  curLayer, nextLayer;
		unsigned int layer = 0;
		std::list<TreeNode<T>* >::iterator itr;
		if (p != NULL){
			curLayer.push_back(p);
			while (curLayer.size()!=0){
				for (itr = curLayer.begin(); itr != curLayer.end(); itr++){
					std::cout <<layer<<" : "<< (*itr)->value<<std::endl;
					if ((*itr)->left) nextLayer.push_back((*itr)->left);
					if ((*itr)->right) nextLayer.push_back((*itr)->right);
				}
				curLayer = nextLayer;
				nextLayer.clear();
				layer++;

			}
		}
	}

};



#endif
