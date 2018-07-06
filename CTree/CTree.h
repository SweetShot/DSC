#pragma once
#include <string>
using namespace std;

template <class T>
struct c_node
{
	T data;
	c_node * left;
	c_node * right;
};

template <class T>
class c_bst

{
	c_node<T> root_;
	int count_;

public:
	c_bst();
	~c_bst();
	c_bst * insert(T val);
	int get_node_count();
	std::string to_str(std::string type);
	void del_tree();
	bool is_in_tree();
	int get_height();
	T get_min();
	T get_max();
	T del_val(T val);
	T get_successor(T given);
};

template<class T>
c_bst<T>::c_bst()
{

}
