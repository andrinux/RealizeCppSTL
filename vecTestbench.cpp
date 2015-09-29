//testbench of Vec
#include <iostream>

#include "ExtVec.h"

int main()
{
	ExtVec<int> a(20, 5);
	ExtVec<double> b(8, 4.1);
	a.print();
	for (ExtVec<int>::size_type i = 0; i < a.size(); i++)
		a[i] = 3 * a[i];
	a.print();

	ExtVec<int> c(a);
	c.print();
	c.push_back(6);
	c.push_back(8);
	c.push_back(100);
	c.print();

	c.resize(28, 99);
	c.print();
	c.remove_member(100);
	c.print();
	return 1;
}
