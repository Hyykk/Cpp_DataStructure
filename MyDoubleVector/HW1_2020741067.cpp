#include <iostream>	// to use cout
#include "MyDoubleVector.h"

using namespace std;

void ShowVector(MyDoubleVector v);	// function that show all elements of vector

int main()
{
	// test constructor
	// get v1 vector that has {1, 3, 4, 5} elements and 10 capacity
	MyDoubleVector v1(10);
	v1.push_back(1);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);

	// copy v1 vector to v2, v3
	// test copy constructor
	MyDoubleVector v2(v1);
	// test =
	MyDoubleVector v3 = v1;

	// print
	cout << "v1 = "; ShowVector(v1);
	cout << "v2 = "; ShowVector(v2);
	cout << "v3 = "; ShowVector(v3);
	// test capacity()
	cout << "v1's capacity = " << v1.capacity() << endl;
	
	// test +=
	v1 += v2;
	cout << "v1 += v2 = ";  ShowVector(v1);

	// test +(binary)
	cout << "v2 + v3 = ";  ShowVector(v2 + v3);

	// test -(binary)
	cout << "v2 - v3 = ";  ShowVector(v2 - v3);

	// test *(binary)
	cout << "v2 * v3 = " << v2 * v3 << endl;

	// test -(unary)
	cout << "-v1 = "; ShowVector(-v1);

	// test ==(binary)
	cout << "v2 == v3 (true : 1, false : 0) = " << (v2 == v3) << endl;

	// test pop_back, push_back
	v2.pop_back();
	v2.push_back(2);
	cout << "changed v2 = "; ShowVector(v2);
	cout << "v2 == v3 (true : 1, false : 0) = " << (v2 == -v3) << endl;

	// test ()
	cout << "All element of v3 is 9 = "; ShowVector(v3(9));

	// test reserve
	v1.reserve(20);
	cout << "capacity of v1 is 20 = " << v1.capacity() << endl;

	// test clear()
	v1.clear();
	cout << "v1 is cleared!" << endl;
	
	//test empty()
	cout << "Is v1 empty? (true : 1, false : 0) = " << v1.empty() << endl;
	cout << "Is v2 empty? (true : 1, false : 0) = " << v2.empty() << endl;

	return 0;
}

void ShowVector(MyDoubleVector v) {
	cout << "{";
	// test size()
	for (int i = 0; i < v.size()-1; i++) {
		// test []
		cout << v[i] << ", ";
	}
	cout << v[v.size()-1] << "}" << endl;
}