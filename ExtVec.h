//This is the header file of vector implementation
//Use a dynamic allocate array as the container
//should be a templated class/function
// ExtVec means "extended vector"
//Content: Vector implementation 
//Author: X.Z.
//Creation Date: 3/3/2014

#ifndef EXT_VEC_H
#define EXT_VEC_H
//Defination of the class ExtVec

template<typename T> class ExtVec{
public:
	//TypeDefs
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef unsigned int size_type;

	//Constructor function/Destructor
	ExtVec() { this->create(); }
	ExtVec(size_type n, const T& t=T()) { this->create(n, t); } 
	ExtVec(const ExtVec& v) { copy(v); }
	ExtVec<T>& operator=(const ExtVec& v); 
	~ExtVec() { delete[] m_data; }

	//Member Functions and other operations list
	T& operator[] (size_type i){ return m_data[i]; }
	const T& operator[] (size_type i) const { return m_data[i]; }
	void push_back(const T& val);
	iterator erase(iterator p);
	void resize(size_type n, const T& fill_in_val = T());
	void clear() { delete[] m_data; }
	bool empty() { return m_size == 0; }
	size_type size() { return m_size; }
	void remove_member(const T& t);
	void print();

	//Iterator Operations
	iterator begin() { return m_data; }
	const_iterator begin() const { return m_data; }
	iterator end() { return m_data + m_size; }
	const_iterator end() const { return m_data + m_size; }

private:
	//Private member functions
	void create();
	void create(size_type n, const T& val);
	void copy(const ExtVec<T>& v);
	//Presentation Variables
	T* m_data; //Pointer to the first element of the array
	size_type m_size; //Used size
	size_type m_alloc;//Allocated total size
};

//Templated functions implementation out of class:
template<typename T> void ExtVec<T>::create()
{
	m_data = NULL;
	m_size = 0;
	m_alloc = 0;
}
// create a vector with size n and same vals
template<typename T> void ExtVec<T>::create(size_type n, const T& val)
{
	m_data = new T[n];
	m_size = m_alloc = n;
	for (T* itr = m_data; itr != m_data + m_size; itr++){
		*itr = val;
	}
}

template <typename T> void ExtVec<T>::copy(const ExtVec<T>& v)
{
	this->m_data = new T[v.m_alloc];
	this->m_size = v.m_size;
	this->m_alloc = v.m_alloc;
	for (size_type i = 0; i < m_size; i++){  //use i here, not iterator again
		m_data[i] = v.m_data[i];
	}
}

//Overload of operator
template<typename T> ExtVec<T>&  ExtVec<T>::operator=(const ExtVec<T>& v){
	if (this != &v){  //m_data!=v.m_data???
		delete[] m_data;
		this->copy(v);
	}
	return *this;
}

//Add one element at the tail of the array
template <typename T> void ExtVec<T>::push_back(const T& val)
{
	if (m_size == m_alloc){
		m_alloc *= 2;
		if (m_alloc < 1)
			m_alloc = 1;
		//Create a new array and copy the old values to it
		T* new_data = new T[m_alloc];
		for (size_type i = 0; i < m_size; i++)
			new_data[i] = m_data[i];
		//Delete the old array and reset the pointer to the new array
		delete[] m_data;
		m_data = new_data;

	}
	//Add the new values to it
	m_data[m_size] = val;
	m_size += 1;
}

//Erase Function, delete one element and shift the following ones
//return the iterator, but point to a different value
template<typename T> typename ExtVec<T>::iterator ExtVec<T>::erase(iterator p)
{
	for (iterator q = p; q < m_data + m_size - 1; q++){
		*q = *(q + 1);
	}
	m_size--;
	return p;
}

//Resize Function, if n is less or equal to the current size, just change the size
//if n is larger than the size, fill in with val
//pushback should not be used to resize
//return value should be none
template<typename T> void ExtVec<T>::resize(size_type n, const T& fill_in_value)
{
	//if n<=m_size,  just short it, otherwise, 
	//if n<=m_alloc, fill in value, otherwise, allocate space and copy-fill
	if (n <= m_size)
		m_size = n;
	else{
		if (n <= m_alloc){
			for (size_type i = m_size; i != n; i++)
				m_data[i] = fill_in_value;
			m_size = n;
		}
		else{
			m_alloc = n;
			T* new_data = new T[n];
			for (size_type i = 0; i != m_size; i++)
				new_data[i] = m_data[i];
			for (size_type i = m_size; i != n; i++)
				new_data[i] = fill_in_value;
			delete[] m_data;
			m_data = new_data;
			
			m_size = n;
		}
	}
}

//Remove the member with value t
template<typename T> void ExtVec<T>::remove_member(const T& t)
{
	T* newdata = new T[m_size];
	size_type i, j;
	for (i = 0, j=0; i != m_size; i++)
	{
		if (m_data[i] != t)
			newdata[j++] = m_data[i];
	}
	delete[] m_data;
	m_data = newdata;
	m_size = j;
}
//Printf
template<typename T> void ExtVec<T>::print()
{
	std::cout << "-----Print of ExtVec:-----" << std::endl;
	for (size_type i = 0; i != m_size; i++){
		std::cout << m_data[i];
		std::cout << ((i % 10 == 9) ? "\n" : " ");
	}
	std::cout << std::endl;
}


#endif