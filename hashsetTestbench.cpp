#include <iostream>
#include <string>
#include <utility>
#include <cassert>

#include "ExtHashSet.h"
#include "ExtHashFunc.h"

typedef ExtHashSet<std::string, hash_string_obj> ExtHashSetType;

int main()
{
	ExtHashSetType set1;
	std::pair<ExtHashSetType::iterator, bool> insertRes;
	insertRes = set1.insert("AAA");
	insertRes = set1.insert("BBB");
	insertRes = set1.insert("CCC");
	insertRes = set1.insert("DDD");
	insertRes = set1.insert("EEE");
	insertRes = set1.insert("FFF");
	insertRes = set1.insert("A110");
	insertRes = set1.insert("A678");
	insertRes = set1.insert("FGH");
	insertRes = set1.insert("B111");
	insertRes = set1.insert("F234");


	set1.print(std::cout);

	set1.erase("AAA");
	set1.print(std::cout);

	ExtHashSetType::iterator p;
	p = set1.find("MMM");
	if (p == set1.end())
		std::cout << "Not found." << std::endl;
	else
		std::cout << "Found: " << *p << std::endl;


	/*set1.resize_table(set1.si)*/
	return 1;
}

