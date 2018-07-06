#include "CVector.h"
#include <iostream>
#include <string>
using namespace std;

template <class T>
void sqr(const c_vector<T>& vec)
{
	const auto size = vec.size();
	for (long i = 0; i < size; i++)
	{
		const auto val = vec.at(i);
		vec.set(i, val * val);
	}
}

int main(void)
{
	const auto vector = new c_vector<int>(10);

	// Add 10 things 
	for (int i = 0; i < 10000000; i++)
		vector->push(i);

	//cout << vector->to_str() << endl;

	// Add 100 things 
	for (int i = 0; i < 10000000; i++)
		vector->push(i % 10);

	//cout << vector->to_str() << endl;

	//vector->del(4);

	//cout << vector->to_str() << endl;
	
	sqr(*vector);

	vector->sqr();

	//cout << vector->remove_all(5) << endl;

	//cout << vector->to_str() << endl;

	delete vector;

	char i;
	cin >> i;
}