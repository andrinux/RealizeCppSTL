#ifndef Ext_Hash_Func_
#define Ext_Hash_Func_

#include <string>


class hash_string_obj{
public:
	//Experiment 
	unsigned int operator() (std::string const&key) const{
		unsigned int hash = 1315423911;
		for (unsigned int i = 0; i < key.length(); i++)
			hash ^= ((hash << 5) + key[i] + (hash >> 2));
		return hash;
	}
};


#endif