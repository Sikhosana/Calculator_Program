#pragma once
#ifndef STACKCLASS_H
#define STACKCLASS_H
namespace sikhosana
{
	template <class Item>
	class STACK
	{
	private:
		static const int CAPACITY = 30;
		Item data[CAPACITY];
		int used;

	public:
		STACK() { used = 0; }
		void push(const Item& entry);
		void pop();
		Item top();
		int size();
		bool empty();
	};
}

#include "myStack.temp"
#endif