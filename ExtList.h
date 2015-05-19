//Content: List implementation 
//Author: X.Z.
//Creation Date: 3/4/2014



#ifndef ExtList_h
#define ExtList_h

//---------------------Node Class for Doubly linked list--------------
template <class T> class Node{
public:
	Node() :next(NULL), prev(NULL) {}
	Node(const T& v) :value(v), next(NULL), prev(NULL) {}
	//presentation values
	T value;
	Node<T>* next;
	Node<T>* prev;
};

template <class T> class ExtList;

//--------------------List Iterator Class for DoubleLinkClass---------
template <class T> class list_iterator{
public:
	list_iterator() : ptr(NULL) {}
	list_iterator(Node<T>* p) : ptr(p) {}
	list_iterator(list_iterator<T> const& old) : ptr(old.ptr) {}
	~list_iterator() {}

	list_iterator<T> & operator=(const list_iterator<T> old){
		ptr = old.ptr;
		return *this;
	}
	T& operator*() { return ptr->value; } //return value
	//increment &decrement operator
	list_iterator<T> & operator++(){
		ptr = ptr->next;
		return *this;
	}
	list_iterator<T> operator++(int){ //No & symbol
		list_iterator<T> tmp(*this); 
		ptr = ptr->next;
		return tmp;
	}
	list_iterator<T> & operator--(){
		ptr = ptr->prev;
		return *this;
	}
	list_iterator<T> operator--(int){
		list_iterator<T> tmp(*this);
		ptr = ptr->prev;
		return tmp;
	}

	friend class ExtList<T>;

	bool operator==(const list_iterator<T>& r) const{
		return ptr == r.ptr;
	}
	bool operator!=(const list_iterator<T>& r) const{
		return ptr != r.ptr;
	}
private:
	//Presentation
	Node<T>* ptr;
};

//--------------------List Class for DoubleLinkClass---------
template <class T> class ExtList {
public:
	ExtList() : head(NULL), tail(NULL), size(0) {}
	ExtList(const ExtList& old) { this->copyList(old); }
	~ExtList() { this->destroyList(); }
	ExtList<T>& operator=(const ExtList<T>& old);

	unsigned int getsize() const { return size; }// TODO: Inside class no need for this->size
	bool empty() const { return head == NULL; }
	void clear(){ this->destroyList(); }

	void push_front(const T& v);
	void pop_front();
	void push_back(const T& v);
	void pop_back();

	typedef list_iterator<T> iterator;
	iterator erase(iterator itr);
	void insert(iterator itr, T const& v);
	iterator begin() const { return iterator(head); }//TODO: 
	iterator end() const { return iterator(NULL); }

	void remove_member(const T& v);
	void printList();

private:
	void copyList(ExtList<T> const &old);
	void destroyList();
	void do_destroy(Node<T>* head);

	//Presentation of List
	Node<T>* head;
	Node<T>* tail;
	unsigned int size;
};
//List Member Functions Implementation Out of class
//Oveload of operator=
template <typename T>  ExtList<T>& ExtList<T>::operator=(const ExtList<T>& old){ 
	//Use copy function:
	if (&old != this){
		this->destroyList();
		this->copyList(old);
	}
	return *this; //TODO: return value is A list, "this" is a pointer, so return *this
}

//push back a new element
template <typename T> void ExtList<T>::push_back(const T& v){
	Node<T>* curNode=new Node<T>;
	curNode->value = v;  
	if (head == NULL){  //TODO: to check empty list
		head = tail = curNode;
	}
	else{
		curNode->prev = tail;
		curNode->next = NULL;
		curNode->prev->next = curNode; //mistake here
		this->tail = curNode; 
	}
	++size;
}
//push front a new element
template <typename T> void ExtList<T>::push_front(const T& v){
	Node<T>* curNode = new Node<T>(v);
	if (head == NULL){
		head = tail = curNode;
	}
	else{
		curNode->next = head;
		curNode->prev = NULL;
		this->head = curNode;
	}
	++size;
}
//remove a element at the tail
template <typename T> void ExtList<T>::pop_back(){
	if (size == 0){
		std::cout << "This is a empty list already. Cannot pop" << std::endl;
		return;
	}
	if (size == 1){
		delete tail;
		--size;
		tail = head = NULL;
		return;
	}
	Node<T> *tmpTail = tail->prev;
	tmpTail->next = NULL;
	delete tail;
	tail = tmpTail;
	--size;
}
//remove a element from the head
template <typename T> void ExtList<T>::pop_front(){
	Node<T>* tmpHead = head->next;
	tmpHead->prev = NULL;
	delete head;
	head = tmpHead;
	--size;
}

//erase a elemnt in the middle
template <typename T> typename ExtList<T>::iterator ExtList<T>::erase(iterator itr){ //TODO: use temp itr to save.!!!!!
	if (head == NULL){
		std::cout << "This is a blank list. Cannot erase.\n";
		return NULL;
	}
	Node<T>* curNode = itr.ptr;
	iterator tmp(itr.ptr->next);
	Node<T>* prevNode = curNode->prev;
	Node<T>* nextNode = curNode->next;
	prevNode->next = nextNode;
	nextNode->prev = prevNode;
	--size;
	delete itr.ptr;
	return tmp;

	//--size;
	//iterator result(itr.ptr);
	//itr.ptr->prev->next = itr.ptr->next;
	//itr.ptr->next->prev = itr.ptr->prev;
	//delete itr.ptr;
	//return result;

}

//insert one elememmt, use itr as argument iterator insert(iterator itr, T const& v);
template <typename T> void ExtList<T>::insert(iterator itr, const T& v){
	Node<T>* newNode = new Node<T>(v);
	newNode->prev = itr.ptr->prev;
	newNode->next = itr.ptr;
	itr.ptr->prev = newNode;
	if (itr.ptr == head)
		head = newNode;
	else
		newNode->prev->next = newNode;
	++size;
}

//copy list
template <typename T> void ExtList<T>::copyList(const ExtList<T>& old){ 
	size = old.size;
	//blank list
	if (size == 0){
		head = tail = NULL;
		return;
	}
	//Two options: iterator or just copy one by one?
	//Node<T>* newNode;
	//for (list_iterator<T> itr = old.begin(); itr != old.end(); itr++){
	//	
	//}

	
	//Option2: copy one by one directly

	head = new Node<T>(old.head->value);
	tail = head;
	Node<T> *curNode = old.head->next;
	while (curNode){
		Node<T> *newNode = new Node<T>;
		newNode->value = curNode->value;
		newNode->prev = tail;
		newNode->prev->next = newNode;
		tail = newNode;
		curNode = curNode->next;
	}

}

//destroy List

template <typename T> void ExtList<T>::destroyList(){
	//remove head, size,, and all the memory
	
	//for (list_iterator<T> itr = this->begin(); itr != this->end(); ){
	//	list_iterator<T> new_itr = itr++;
	//	delete itr.ptr;
	//	itr = new_itr;
	//}
	//head = tail = NULL;
	//size = 0;
	
	//Option2:
	//if (head == NULL)
	//	return;
	//Node<T> * curNode = head;
	//Node<T> * nextNode= head->next;
	//while (curNode){
	//	nextNode = curNode->next;
	//	delete curNode;
	//	curNode = nextNode;
	//}
	//size = 0;
	//head = tail = NULL;

	//Option3: Use recursion"
	do_destroy(head);
	size = 0;
	head = tail= NULL;
	
}
template <typename T> void ExtList<T>::do_destroy(Node<T>* head){
	if (head == NULL) return;
	do_destroy(head->next);
}

//remove member &value traverse could use iterator
template <typename T> void ExtList<T>::remove_member(const T& v){ 
	if (head == NULL){
		std::cout << "This is a blank list" << std::endl;
		return;
	}
	for (list_iterator<T> itr = this->begin(); itr != this->end(); itr++){
		if (itr.ptr->value == v){
			erase(itr);
		}
	}
}

//printlist
template <typename T> void ExtList<T>::printList(){
	if (head == NULL){
		std::cout << "This is a blank list!" << std::endl;
		std::cout << "-----------------------\n";
		return;
	}
	Node<T> *curNode;
	curNode = head; 
	for (unsigned int i = 0; i < size; i++){
		std::cout << curNode->value;
		std::cout << ((i % 10 == 9) ? "\n" : " ");
		curNode = curNode->next;
	}
	std::cout << "\n-----------------------";
	std::cout << std::endl;
}

#endif