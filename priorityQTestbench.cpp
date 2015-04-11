#include <iostream>
#include <queue>
#include "ExtPriorityQ.h"

int main()
{
	Ext_priority_queue<int> myQueue1;
	
	std::priority_queue<int> Queue1;
	myQueue1.push(5);  Queue1.push(5);
	myQueue1.push(13); Queue1.push(13);
	myQueue1.push(3);  Queue1.push(3);
	myQueue1.push(11); Queue1.push(11);
	myQueue1.push(6);  Queue1.push(6);
	myQueue1.push(23); Queue1.push(23);
	myQueue1.push(8);  Queue1.push(8);
	myQueue1.push(12); Queue1.push(12);
	myQueue1.push(17); Queue1.push(17);
	myQueue1.push(19); Queue1.push(19);
	myQueue1.push(9); Queue1.push(9);
	myQueue1.push(24); Queue1.push(24);


	myQueue1.printHeap(std::cout);
	std::cout << "Check heap: " << ((myQueue1.checkHeap()==true)?"Success":"Fail") << std::endl;

	while (Queue1.empty() == false && myQueue1.empty() == false){
		if (Queue1.top() != myQueue1.top()){
			std::cout << "Exception Occured. Quit." << std::endl;
			return 0;
		}
		Queue1.pop(); myQueue1.pop();
	}
	std::cout << "pop works..." << std::endl;

	std::vector<int> Vdata1;
	for (int i = 0; i < 100; i++){
		Vdata1.push_back(rand() % 200);
	}
	heapSort(Vdata1);
	for (int i = 99; i >0; i--){
		std::cout  <<Vdata1[i] << ((i % 10 == 0) ? "\n" : ", ");
	}


	return 1;
}