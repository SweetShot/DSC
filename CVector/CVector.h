#pragma once
#include <iostream>
#include <climits>
#include <string>
using namespace std;

template <class T>
class c_vector
{
private:
	T* data_;
	long capacity_;
	long size_;

private:
	static int get_next_power_of_2(int);
	bool resize(int capacity);
	void shift_right(long index) const;
	void shift_left(long index) const;
public:
	explicit c_vector<T>(const long capacity);
	~c_vector();
	long size() const;
	long capacity() const;
	bool is_empty() const;
	int at(long index) const;
	void set(long index, T val) const;
	T* data() const;
	bool push(T val);
	bool insert(long index, T val);
	bool prepend(T val);
	int pop();
	int del(int index);
	int remove_all(T val);
	int find(T val) const;
	std::string to_str() const;

	void sqr();
};

template <class T>
int c_vector<T>::get_next_power_of_2(const int val)
{
	if (val < 16)
	{
		return 16;
	}

	int i = 2;
	while (i < val)
	{
		i = i << 1;
	}
	return i;
}

template <class T>
bool c_vector<T>::resize(const int capacity)
{
	const auto tdata = new T[capacity];
	if (tdata == nullptr)
	{
		return false;
	}
	std::copy(data_, data_ + size_, tdata);
	delete data_;
	data_ = tdata;
	return true;
}

template <class T>
void c_vector<T>::shift_right(const long index) const
{
	const auto last = data_ + size_;
	const auto indexptr = data_ + index;
	for (auto i = last; i > indexptr; --i)
	{
		*i = *(i - 1);
	}
}

template <class T>
void c_vector<T>::shift_left(const long index) const
{
	const auto start = data_ + index;
	const auto last = data_ + size_;
	for (auto i = start; i < last; ++i)
	{
		*i = *(i + 1);
	}
}

template <class T>
c_vector<T>::c_vector<T>(const long capacity)
{
	capacity_ = get_next_power_of_2(capacity);
	data_ = new T[capacity_];
	size_ = 0;
}

template <class T>
c_vector<T>::~c_vector<T>()
{
	delete data_;
}

template <class T>
long c_vector<T>::size() const
{
	return size_;
}

template <class T>
long c_vector<T>::capacity() const
{
	return capacity_;
}

template <class T>
bool c_vector<T>::is_empty() const
{
	return (size_ == 0) ? true : false;
}

template <class T>
int c_vector<T>::at(const long index) const
{
	return *(data_ + index);
}

template <class T>
void c_vector<T>::set(const long index, const T val) const
{
	if (index < size_)
	{
		data_[index] = val;
	}
}


/**
 * \brief Returns underlying array ( note how we allow access to underlying array but dont
 *        allow changing size of capacity or changing array itself, even though can change
 *        its elements 
 * \return underlying array
 */
template <class T>
T* c_vector<T>::data() const
{
	return data_;
}

template <class T>
bool c_vector<T>::push(const T val)
{
	return insert(size_, val);
}

template <class T>
bool c_vector<T>::insert(const long index, T val)
{
	// If no place for next item then make array double
	if (size_ == capacity_)
	{
		capacity_ = capacity_ << 1;
		const auto success = resize(capacity_);
		if (!success) {
			capacity_ = capacity_ >> 1;
			return false;
		}
	}
	// Easy case when append at the end
	if (index == size_)
	{
		data_[index] = val;
		size_++;
		return true;
	}
	// Case in between
	shift_right(index);
	data_[index] = val;
	size_++;
	return true;
}

template <class T>
bool c_vector<T>::prepend(const T val)
{
	return insert(0, val);
}

template <class T>
int c_vector<T>::pop()
{
	return del(size_);
}

template <class T>
int c_vector<T>::del(const int index)
{
	if (index >= size_)
	{
		return INT_MIN; // wrong index
	}

	// check if resize will be required after deleting 1
	if (size_ - 1 < capacity_ / 2)
	{
		capacity_ = capacity_ >> 1;
		const auto success = resize(capacity_);
		if (!success) {
			capacity_ = capacity_ << 1;
			return INT_MIN;
		}
	}
	// If resize succeeds then
	const auto toret = data_[index];
	// else shift left
	shift_left(index);
	size_--;
	return toret;
}

template <class T>
int c_vector<T>::remove_all(T val)
{
	auto deleted = 0;
	const auto last = data_ + size_;
	for (auto curr = data_; curr < last; ++curr)
	{
		if (*curr == val)
		{
			deleted++;
		}
		else
		{
			*(curr - deleted) = *curr;
		}
	}
	size_ -= deleted;

	if (size_ <= capacity_ / 2)
	{
		capacity_ = capacity_ >> 1;
		const auto success = resize(capacity_);
		if (!success) {
			capacity_ = capacity_ << 1;
			return INT_MIN;
		}
	}

	return deleted;
}

template <class T>
int c_vector<T>::find(const T val) const
{
	long index = -1, curridx = 0;
	const auto start = data_ + index;
	const auto last = data_ + size_;
	for (auto curr = start; curr < last; ++curr)
	{
		if (*curr == val)
		{
			index = curridx;
			break;
		}
		curridx++;
	}
	return index;
}

template <class T>
std::string c_vector<T>::to_str() const
{
	std::string ans = "";
	const auto start = data_;
	const auto last = data_ + size_;
	for (auto curr = start; curr < last; ++curr)
	{
		ans += std::to_string(*curr) + " ";
	}
	return ans;
}

template <class T>
void c_vector<T>::sqr()
{
	const auto start = data_;
	const auto last = data_ + size_;
	for (auto curr = start; curr < last; ++curr)
	{
		*curr *= *curr;
	}
}


