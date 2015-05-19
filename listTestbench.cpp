#include <iostream>
#include "ExtList.h"

int main()
{
	ExtList<int> myList;
	unsigned int i = 0;
	for (i = 20; i < 40; i++)
		myList.push_back(i);
	myList.printList();
	for (i = 10; i < 20; i++)
		myList.pop_back();
	myList.printList();
	for (i = 10; i < 20; i++)
		myList.push_front(i);
	myList.printList();
	for (i = 10; i < 20; i++)
		myList.pop_front();
	myList.printList();

	ExtList<int> myList_2(myList);
	myList_2.printList();
	//myList_2.clear();
	//myList_2.printList();

	ExtList<int>::iterator itr;
	itr = myList_2.begin();
	itr++; ++itr;
	itr=myList_2.erase(itr);
	itr=myList_2.erase(itr);
	myList_2.printList();
	myList_2.insert(itr, 99);
	myList_2.insert(itr, 98);
	myList_2.printList();





	return 0;
}