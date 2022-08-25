#include "TestVector.h"
#include <string>

#include "Domain.h"

#include <iostream>


void test_adding_int();
void test_adding_big_list();
void test_adding_Movie();
void test_adding_string();
void test_adding_vector();

void test_pop_int();
void test_pop_big_list();

void TestVector::test_push_back() {
	test_adding_int();
	test_adding_big_list();
	test_adding_Movie();
	test_adding_string();
	test_adding_vector();
}

void TestVector::test_pop_back() {
	test_pop_int();
	test_pop_big_list();
}

void TestVector::test_begin() {
	Vector < int > v;
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	int* bg = v.begin();

	assert(*bg == v[0]);
}

void TestVector::test_end() {
	Vector < int > v;
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	int* bg = v.end();

	assert(*(bg - 1) == v[2]);
}

void TestVector::test_size() {
	Vector < int > v;
	for (int i = 1; i <= 1000; i++) {
		v.push_back(i);
		assert(v.size() == i);
	}
}

void TestVector::test_iterator() {
	Vector < int > v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	IteratorVector<int> it = v.iterator();
	assert(it.current_value() == 1);
	for (int i = 0; i < 4; i++)
		assert(it.value(i) == i + 1);
	for (int i = 1; i <= 4; i++) {
		assert(it.current_value() == i);
		it.next();
	}
}

void TestVector::run_all_tests() {
	test_iterator();
	test_push_back();
	test_pop_back();
	test_begin();
	test_end();
	test_size();
}


void test_adding_int() {
	Vector < int > v;
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	assert(v.size() == 4);
	assert(v[0] == 2);
	assert(v[1] == 3);
	assert(v[2] == 4);
	assert(v[3] == 5);

	for (auto it : v)
		assert(it == 2 || it == 3 || it == 4 || it == 5);

	Vector < int > a = v;
	v.push_back(25);
	assert(v.size() == 5);
	assert(a.size() == 4);
	assert(v[0] == 2);
	assert(v[1] == 3);
	assert(v[2] == 4);
	assert(v[3] == 5);
	assert(v[4] == 25);

	a.push_back(43);
	assert(v.size() == 5);
	assert(a.size() == 5);
	assert(a[0] == 2);
	assert(a[1] == 3);
	assert(a[2] == 4);
	assert(a[3] == 5);
	assert(a[4] == 43);

	assert(v[0] == 2);
	assert(v[1] == 3);
	assert(v[2] == 4);
	assert(v[3] == 5);
	assert(v[4] == 25);
}

void test_adding_big_list() {
	Vector < int > v;
	for (int i = 1; i <= 1000; i++) {
		v.push_back(i);
		assert(v.size() == i);
	}
}

void test_adding_Movie() {
	Vector < Movie > v;
	Movie m{ "No time to die", "Action", 2021, "Daniel Craig" };
	v.push_back(m);
	v.push_back(m);

	v[1].set_gen("das");
	assert(v[1].get_gen() == "das");
	assert(v[0].get_gen() == "Action");

	assert(v.size() == 2);

}

void test_adding_string() {
	std::string  s[4];
	s[0] = "dorel";
	s[1] = "gelu";
	s[2] = "demian";
	s[3] = "das";

	Vector < std::string > v;
	for (int i = 0; i < 4; i++)
		v.push_back(s[i]);

	for (int i = 0; i < 4; i++)
		assert(v[i] == s[i]);
}

Vector<int> create_pseudo_vector() {
	Vector < int > v;
	v.push_back(2);
	v.push_back(43);
	return v;
}

void test_adding_vector() {
	Vector < int > v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	Vector < Vector < int > > v2;
	v2.push_back(v);
	for (int i = 0; i < v.size(); i++)
		assert(v[i] == v2[0][i]);

	v2 = v2;

	v.resize(1);

	v = create_pseudo_vector();
	assert(v[0] == 2);
	assert(v[1] == 43);

	Vector<int> *v32, *v33;
	v32 = &v;
	v33 = &v;
	v32 = v33;
}

void test_pop_int() {
	Vector < int > v;
	for (int i = 1; i <= 5; i++)
		v.push_back(i);

	v.pop_back();

	assert(v.size() == 4);
	for (int i = 0; i < 4; i++)
		assert(v[i] == i + 1);
}

void test_pop_big_list() {
	Vector < int > v;
	for (int i = 1; i <= 1000; i++)
		v.push_back(i);

	for (int i = 999; i >= 0; i--) {
		v.pop_back();
		assert(v.size() == i);
		for (int j = 0; j < i - 1; j++)
			assert(v[j] == j + 1);
	}
}