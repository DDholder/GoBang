#pragma once
#include"stack"
template<typename T> class mystack:public
std::stack<T>
{
public:
	mystack(){}
	virtual ~mystack(){}
	T mypop()
	{
		T value = mystack::top();
		mystack::pop();
		return value;
	}
	void operator--() { mystack::pop(); }
	void operator+=(T data) { mystack::push(data); }
};



