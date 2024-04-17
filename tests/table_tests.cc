#include <gtest/gtest.h>
#include <C:/Users/Alex/Desktop/AaDS/lab_5/class/hash_table.cpp>
#include <iostream>

using namespace lab_5;
using namespace std;

TEST(Pair, Creating) {
	my_pair<int, int> a = {4, 2};
	cout << a.get_del() << endl;
	cout << a.get_init() << endl;
	a.set_init();
	cout << a.get_init() << endl;
	a.del();
	cout << a.get_del() << endl;
}
TEST(HashTable, PrintHashTable) {
	hash_table<int, int> a(10);
	a.print();
}