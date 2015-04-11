/*
* In this Implementation, parent Node is larger than child Node.
* which is consistent with C++ STL
* If you want to change, Need to update push, pop, checkHeap
* Author: XZ
* Apr.10.2015
*/

#ifndef Ext_Priority_Queue_h
#define Ext_Priority_Queue_h

#include <iostream>
#include <vector>
#include <math.h> 
#include <cassert>



template<typename T> class Ext_priority_queue{
private:
	std::vector<typename T> m_heap;
public:
	Ext_priority_queue() {}
	Ext_priority_queue(std::vector<T>const& values) { //where to put const 
	//constructor with vector
		for (unsigned int i = 0; i < values.size(); i++)
			push(values[i]);
	}

	const T& top() const{
		assert(!m_heap.empty());
		return m_heap[0];
	}
	//Add One more element. 
	//Percolate up: swap layer by layer
	void push_v2(const T& entry){
		m_heap.push_back(entry);
		if (m_heap.size() == 1)
			return;
		int cur, par;
		cur = m_heap.size() - 1;
		par = parent(cur);
		while (par >= 0){
			if (m_heap[par] < m_heap[cur]){
				//swap
				swap(par, cur);
				cur = par;
				par = parent(cur);
			}
			else
				break;
		}
	}
	
	inline void swap(int par, int cur){
		T temp;
		temp = m_heap[cur];
		m_heap[cur] = m_heap[par];
		m_heap[par] = temp;
	}
	inline int parent(int child){
		return int(floor((child - 1) / 2));
	}

	void push(const T& entry){
		m_heap.push_back(entry);
		int sub = size() - 1;
		while (sub != 0 && m_heap[int(floor((sub - 1) / 2))] < m_heap[sub]){
			T temp = m_heap[int(floor((sub - 1) / 2))];
			m_heap[int(floor((sub - 1) / 2))] = m_heap[sub];
			m_heap[sub] = temp;
			sub = int(floor((sub - 1) / 2));
		}

	}
	//DeleteMin, remove one Node
	//(1). Remove heap[0]. 
	//(2). Replace heap[0] by heap[size()-1];
	//(3). Percolate Down
	void pop()
	{
		if (m_heap.empty())
			return;
		else
		{
			//do the DeleteMin
			std::cout << "Pop: " << m_heap[0] << std::endl;
			m_heap[0] = m_heap[m_heap.size() - 1];
			m_heap.pop_back();
			int cur=0, child;
			while ((child = largeChild(cur)) > 0){
				if (m_heap[cur] > m_heap[child])
					break;
				else{
					//swap
					swap(cur, child);
					cur = child;
				}
			}
		}
	}

	//find the number of largest child
	int largeChild(int cur){
		int child_1 = 2 * cur + 1;
		int child_2 = 2 * cur + 2;
		int child = -1;;
		int size = m_heap.size();
		if (child_1 >= size)
			return -1; //no children
		else if (child_2 >= size)
			child = child_1; //one left child.
		else //Two children
			child = (m_heap[child_1] > m_heap[child_2]) ? child_1 : child_2;
		//child is the largest child
		return child;
	}
	
	//Another version of pop Implementation(T.L. top is smallest)
	void pop_v2(){
		assert(!m_heap.empty());
		m_heap[0] = m_heap[size() - 1];
		m_heap.pop_back();
		int sub = 0;
		int swap_index;
		int left = sub * 2 + 1;
		int right = sub * 2 + 2;
		while (left <= size()) {
			if (right <= size() && m_heap[right] <= m_heap[left]) {
				swap_index = right;
			}
			else 
				swap_index = left;
			if (m_heap[swap_index] < m_heap[sub]) {
				T tmp = m_heap[sub];
				m_heap[sub] = m_heap[swap_index];
				m_heap[swap_index] = tmp;
				sub = swap_index;
			}
			else {
				break;
			}
			left = sub * 2 + 1;
			right = sub * 2 + 2;
		}
	}
	
	int size() const{
		return m_heap.size();
	}
	bool empty() const{
		return m_heap.empty();
	}
	bool checkHeap(){
		return this->checkHeap(m_heap);
	}
	//Several Useful functions
	//CheckHeap, to make sure the next checkpoint exists, we can do in reverse order
	bool checkHeap(const std::vector<T>& heap){
		if (heap.empty())
			return true;
		int sub = heap.size() - 1;
		while (sub > 0){
			if (heap[int(floor((sub - 1) / 2))] > heap[sub])
				sub--;
			else{
				return false;
			}
		}
		return true;
	}

	//A utilitu to print the contents
	void printHeap(std::ostream &ostr){
		ostr << "Print Heap by order:" << std::endl;
		for (unsigned int i = 0; i<m_heap.size(); ++i)
			ostr << i << ": " << m_heap[i] << std::endl;
		ostr << "Print Heap by level:" << std::endl;
		int height = int(log2(m_heap.size()))+1;
		for (int level = 0; level < height; level++){
			int blank = 2 << (height - level -1);
			for (int idx = ((1 << level) - 1); idx <= ((1 << (level + 1)) - 2) && idx < int(m_heap.size()); idx++)
				printElement(blank, idx, ostr);
			ostr << std::endl;
		}
	}

	void printElement(int blank, int idx, std::ostream &ostr){
		for (int i = 0; i < blank; i++){
			ostr << " ";
		}
		ostr << m_heap[idx];
		for (int i = 0; i < blank; i++)
			ostr << " ";
	}
};

template <typename T> void heapSort(std::vector<T> & v){
	Ext_priority_queue<T> Seq(v);
	int len = v.size();
	v.clear();
	for (int i = 0; i < len; i++){
		v.push_back(Seq.top());
		Seq.pop();
	}
}
#endif