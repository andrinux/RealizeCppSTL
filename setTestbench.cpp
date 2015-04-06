#include <iostream>
#include "ExtSet.h"
#include <string>
#include <cassert>

int main()
{
	ExtSet<std::string> data;
	std::pair < ExtSet<std::string>::iterator, bool > insert_result;
	insert_result = data.insert("bbb");
	assert(insert_result.second);
	insert_result = data.insert("aaa");
	assert(insert_result.second);
	insert_result = data.insert("ddd");
	assert(insert_result.second);
	insert_result = data.insert("ccc");
	assert(insert_result.second);
	insert_result = data.insert("fff");
	assert(insert_result.second);
	insert_result = data.insert("eee");
	assert(insert_result.second);
	insert_result = data.insert("ggg");
	assert(insert_result.second);
	insert_result = data.insert("CCC");
	assert(insert_result.second);
	insert_result = data.insert("BBB");
	assert(insert_result.second);
	insert_result = data.insert("DDD");
	assert(insert_result.second);

	ExtSet<std::string>::iterator itr=data.begin();
	std::cout << (*itr);

	itr = data.find("BBB");
	if (itr == data.end())
		std::cout << "\"ddd\" is not in the set\n";
	else
		std::cout << "\"ddd\" is in the set\n"
		<< "The iterator points to: " << *itr << std::endl;


	itr = data.find("pappy");
	if (itr == data.end())
		std::cout << "\"pappy\" is not in the set\n";
	else
		std::cout << "\"pappy\" is in the set\n"
		<< "The iterator points to:" << *itr << std::endl;

	std::cout << data;
	data.print_as_sideways_tree(std::cout);
	std::cout << "\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
	data.breadth_first_search();
	data.erase("BBB");
	std::cout << "\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
	data.print_as_sideways_tree(std::cout);
	data.breadth_first_search();
	std::cout << "\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
	ExtSet < std::string> newData = data;
	newData.print_as_sideways_tree(std::cout);
	return 1;
}