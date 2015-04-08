#ifndef Ext_Hash_Set
#define Ext_Hash_Set

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>

template<typename KeyType, typename HashFunc> class ExtHashSet{

private:
	typedef typename std::list<KeyType>::iterator hash_list_itr; //XZ: why typename here?

public:
	//=========================================================
	//The iterator class
	//Defined as a nested class and thus is not seperately templated
	//XZ: why iterator class need to be nested????
	class iterator{
	public:
		friend class ExtHashSet;
	private:
		//Iterator Representation
		ExtHashSet* m_hs;// No <T>
		int m_index;	 // curennt index in the hash table
		hash_list_itr m_list_itr; //

	private:  //XZ: why these constructors are divided into two kinds.
		//Constructor for use by the ExtHashSet only
		iterator(ExtHashSet *hs) : m_hs(hs), m_index(-1) {}
		iterator(ExtHashSet *hs, int index, hash_list_itr loc) :
			m_hs(hs), m_index(index), m_list_itr(loc) {}
	public:
		//ordinary constructores and assignment operator
		iterator() : m_hs(0), m_index(-1) {}
		iterator(iterator const& itr) :
			m_hs(itr.m_hs), m_index(itr.m_index), m_list_itr(itr.m_list_itr) {}
		iterator& operator=(const iterator* old){
			m_hs = old.m_hs;
			m_index = old.m_index;
			m_list_itr = old.m_list_itr;
			return *this;
		}

		//dereference operator need only worry about the current
		//list iteatot and don't need to check the current index
		const KeyType& operator*() const { return *m_list_itr; }  

		//The comparison operator must account fo the list iterators
		//being unassigned at the end.
		friend bool operator==(const iterator &lft, const iterator &rgt){
			return lft.m_hs == rgt.m_hs && lft.m_index = rgt.m_index &&
				(lft.m_index == -1 || lft.m_list_itr == rgt.m_list_itr;)
		}
		friend bool operator!=(const iterator&lft, const iterator &rgt){
			return lft.m_hs != rgt.m_hs || lft.m_index != rgt.m_index ||
				(lft.m_index != -1 && lft.m_list_itr != rgt.m_list_itr);
		}
		//increment and decrement
		iterator & operator++(){
			this->next();
			return *this;
		}
		iterator  operator+=(int) { //XZ: no & here
			iterator temp(*this);
			this->next();
			return temp;
		}
		iterator & operator--(){
			this->prev();
			return *this;
		}
		iterator operator--(int){
			iterator temp(*this);
			this->prev();
			return temp;
		}

	private:
		//Find the next entry in the table
		void next(){
			++m_list_itr; //Next item in the list
			//If we are at the end of the list
			if (m_list_itr == m_hs->m_table[m_index].end()){
				//Find the next non-empty list in the table
				for (++m_index; m_index < int(m_hs->m_table.size()) && m_hs->m_table[m_index].empty();
					++m_index) {}
				//If one is found
				if (m_index != int(m_hs->m_table.size()))
					m_list_itr = m_hs->m_table[m_index].begin();
				else
					m_index = -1; //Now we are at the end.
			}
		}

		//Find the previous entry in the table
		void prev(){
			//If we are not at the start of the list, just decrement the list iterator
			if (m_list_itr != m_hs->m_table[m_index].begin())
				m_list_itr--;
			else{
				//If not, back down the table to find a previous non-empty list
				for (--m_index; m_index > 0 && m_hs->m_table[m_index].empty(); --m_index) {}
				//Go to the last entry in the found list
				m_list_itr = m_hs->m_table[m_index].begin();
				hash_list_itr p = m_list_itr;
				++p;
				for (; p != m_hs->m_table[m_index].end(); ++p, ++m_list_itr) {}
			}
		}
	};
//===================Here is the end of iterator class===========

private:
	//====================HashSet Representation=================
	std::vector<std::list<KeyType> > m_table; //actual table is a vector
	HashFunc m_hash;
	unsigned int m_size; //number of keys.  cannot be negative
public:
	//====================HashSet Implementations================
	//Constructor of the table accepts the size of the table. Default
	//Constructor for the hash function object is used
	ExtHashSet(unsigned int init_size = 10) :m_table(init_size), m_size(0) {}
	ExtHashSet(const ExtHashSet<KeyType, HashFunc>& old) :
		m_table(old.m_table), m_size(old.m_size) {} //XZ: this is only pointer -redirect, not copy???
	~ExtHashSet() {}

	//Assignment operator definition
	ExtHashSet& operator=(const ExtHashSet<KeyType, HashFunc>& old){
		if (this != &old){ //No need to destroy and re-copy?
			this->m_table = old.m_table;
			this->m_size = old.m_size;
			this->m_hash = old.m_hash;//Hash Function Object
		}
	}

	//Insert the key to the table
	std::pair<iterator, bool> insert(KeyType const& key){
		const float LOAD_FRACTION_FOR_RESIZE = 1.25;
		if (m_size >= LOAD_FRACTION_FOR_RESIZE*m_table.size())
			this->resize_table(2 * m_table.size() + 1);
	}

	//Find the location of one key
	iterator find(const KeyType& key){

	}

	//Erase One key
	int erase(const KeyType& key){

	}
	//An overloaded version of erase at iterator
	int erase(iterator p){
		
	}

	//Find the first entry in the table and create an iterator
	iterator begin(){

	}

	//Create and end iterator
	iterator end(){

	}

	//A public print utility
	void print(std::ostream & ostr){

	}


	//=====Some private interface of HashSet========
	void resize_table(unsigned int new_size){

	}
};

#endif