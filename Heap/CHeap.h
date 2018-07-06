#pragma once
#include "../CVector/CVector.h"

template <class T>
class c_heap
{
	c_vector<T> * data_;
	long start_items;
	bool fixed;

	void sift();
public:
	explicit c_heap(long items, bool fixed);
	~c_heap();
	bool insert(T val);

};

template <class T>
void c_heap<T>::sift()
{

}

template <class T>
c_heap<T>::c_heap(long items, bool fixed = false)
{
	data_ = new c_vector<T>(items);
	start_items = items;
	this.fixed = fixed;
}

template <class T>
c_heap<T>::~c_heap()
{
	delete data_;
}

template <class T>
bool c_heap<T>::insert(const T val)
{
	if (fixed)
	{
		if (data_->size() == start_items)
		{
			return false;
		}
	}
	// else add
	bool success = data_->push(val);
	if (!success)
	{
		return false;
	}
	auto size = data_->size();
	// re arrage now that it is added
	if (size == 1)
	{
		return true; // nothing to do
	}
	auto arr = data_->data();
	for (auto i = size - 1; i > 0;)
	{
		// compare with parent and replace if necessary
		auto pidx = i / 2 - (i % 2 == 0) ? 1 : 0;
		if (arr[pidx] < val)
		{
			arr[i] = arr[pidx];
			arr[pidx] = val;
		}
		else
		{
			break;
		}

		i = pidx;
	}

	return true;
}
