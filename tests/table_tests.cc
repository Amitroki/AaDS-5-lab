#include <gtest/gtest.h>
#include <C:/Users/Alex/Desktop/AaDS/lab_5/class/hash_table.cpp>
#include <iostream>

using namespace lab_5;
using namespace std;

TEST(PairTest, Creating) {
	Pair<int, int> a = {4, 2};
	cout << a.is_del() << endl;
	a.del();
	cout << a.is_del() << endl;
}
TEST(HashTableTest, PrintHashTable) {
	HashTable<int, int> a(10);
	a.print();
}
TEST(HashTableTest, CopyHashTable) {
	HashTable<int, int> a(10);
	HashTable<int, int> b(a);
	b.print();
}
TEST(HashTableTest, OperatorHashTable) {
	HashTable<int, int> a(10);
	HashTable<int, int> b = a;
	b.print();
}
TEST(HashTableTest, SearchElement1) {
	HashTable<int, int> a(10);
	int *b = a.search(10);
	int* c = a.search(0);
	EXPECT_EQ(nullptr, b);
}

//TEST(HashTable, Insert) {
//	HashTable<int, int> a(10);
//	a.insert(111, 905);
//	a.insert(109, 703);
//	a.print();
//}