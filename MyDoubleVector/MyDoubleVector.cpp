#include <cstdlib>	// to use size_t
#include <algorithm>	// to use copy
#include <cassert>	// to use assert
#include "MyDoubleVector.h"

MyDoubleVector::MyDoubleVector(static const size_t init_capacity) {
	// precondition : init_capacity >= 0
	// postcondition : construct MyDoubleVector that has init_capacity.
	assert(init_capacity >= 0);
	data = new double[init_capacity];
	v_capacity = init_capacity;
	v_size = 0;
}

MyDoubleVector::MyDoubleVector(const MyDoubleVector& source) {
	// precondition : x
	// postcondition : construct MyDoubleVector that has same capacity, size, data with source.
	data = new double[source.v_capacity];
	v_capacity = source.v_capacity;
	v_size = source.v_size;
	std::copy(source.data, source.data + v_size, data);
}

MyDoubleVector::~MyDoubleVector() {
	// precondition : X
	// postcondition : destruct.
	delete[] data;
}

MyDoubleVector& MyDoubleVector::operator=(const MyDoubleVector& source) {
	// precondition : X
	// postcondition : copy source.
	if (this == &source) {	// if copy the same like a=a
		return *this;
	}
	if (v_capacity != source.v_capacity) {	// if copy vector's capacity is equal to source vector
		delete[] data;
		data = new double[source.v_capacity];
		v_capacity = source.v_capacity;		// create capacity to copy
	}
	v_size = source.v_size;
	std::copy(source.data, source.data + v_size, data);
	return *this;
}

void MyDoubleVector::operator +=(const MyDoubleVector& addend) {
	// precondition : X
	// postcondition : appends RHS object to LHS one. If v_capacity isn't enough, increase capacity.
	if (v_size + addend.v_size > v_capacity) {
		reserve(v_size + addend.v_size);
	}
	std::copy(addend.data, addend.data + addend.v_size, data + v_size);
	v_size += addend.v_size;
}

double& MyDoubleVector::operator[](int index) {
	// precondition : index < v_size
	// postcondition : returns a reference to the element at the index position
	assert(index < v_size);
	return data[index];
}

MyDoubleVector MyDoubleVector::operator+(const MyDoubleVector& v) {
	// precondition : RHS's size == LHS's size
	// postcondition : returns an object that is a vector-sum of the two operand objects
	assert(v_size == v.v_size);
	MyDoubleVector answer(v_size);
	answer = *this;
	for (size_t i = 0; i < v_size; i++) {
		answer.data[i] = answer.data[i] + v.data[i];
	}
	return answer;
}

MyDoubleVector MyDoubleVector::operator-(const MyDoubleVector& v) {
	// precondition : RHS's size == LHS's size
	// postcondition : returns an object that is a vector-difference of the two operand objects
	assert(v_size == v.v_size);
	MyDoubleVector answer(v_size);
	answer = *this;
	for (size_t i = 0; i < v_size; i++) {
		answer.data[i] = answer.data[i] - v.data[i];
	}
	return answer;
}

double  MyDoubleVector::operator*(const MyDoubleVector& v) {
	// precondition : RHS's size == LHS's size
	// postcondition : returns the scalar product of the two operand objects
	assert(v_size == v.v_size);
	double answer = 0;
	for (size_t i = 0; i < v_size; i++) {
		answer += data[i] * v.data[i];
	}
	return answer;
}

MyDoubleVector MyDoubleVector:: operator-() {
	// precondition : X
	// postcondition : returns an object of which each element is the unary negation of the corresponding element in the operand object
	MyDoubleVector answer(*this);
	for (size_t i = 0; i < v_size; i++) {
		answer.data[i] = data[i] * (-1);
	}
	return answer;
}

bool MyDoubleVector::operator==(const MyDoubleVector& v) {
	// precondition : X
	// postcondition : returns whether or not the the two operand vectors are the same. If the two vector have different size, return false.
	if (v_size != v.v_size) {
		return false;
	}
	for (size_t i = 0; i < v_size; i++) {
		if (data[i] != v.data[i]) {
			return false;
		}
	}
	return true;
}

MyDoubleVector MyDoubleVector::operator()(double x) {
	// precondition : X
	// postcondition : makes every element of this object become x.
	MyDoubleVector answer(*this);
	for (size_t i = 0; i < v_size; i++) {
		answer.data[i] = x;
	}
	return answer;
}

void MyDoubleVector::pop_back() {
	// precondition : v_size > 0; (if v_size < 0, v_size = 0)
	// postcondition : removes the last element in the vector.
	v_size = v_size > 0 ? v_size - 1 : 0;
}

void MyDoubleVector::push_back(double x) {
	// precondition : X
	// postcondition : adds a new element at the end of the vector. If v_capacity isn't enough, v_capacity++.
	if (v_capacity <= v_size) {
		v_capacity++;
		double* larger_array = new double[v_capacity];
		for (size_t i = 0; i < v_size; i++) {
			larger_array[i] = data[i];
		}
		delete[] data;
		data = larger_array;
	}
	data[v_size++] = x;
}

size_t MyDoubleVector::capacity() const {
	// precondition : X
	// postcondition : returns capacity of vector.
	return v_capacity;
}

size_t MyDoubleVector::size() const {
	// precondition : X
	// postcondition : returns size of vector.
	return v_size;
}

void MyDoubleVector::reserve(size_t n) {
	// precondition : X
	// postcondition : the capacity of the allocated storage space for the elements of the vector container be at least enough to hold n elements.
	double* larger_array;
	if (n == v_capacity) {
		return;
	}
	if (n < v_size) {
		n = v_size;
	}

	larger_array = new double[n];
	std::copy(data, data + v_size, larger_array);
	delete[] data;
	data = larger_array;
	v_capacity = n;
}

bool MyDoubleVector::empty() const {
	// precondition : X
	// postcondition : returns whether the vector container is empty.(size == 0)
	return (v_size == 0);
}

void MyDoubleVector::clear() {
	// precondition : X
	// postcondition : all the elements of the vector are dropped.
	v_size = 0;
}