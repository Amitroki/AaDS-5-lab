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
	a.insert(0, 100);
	EXPECT_EQ(100, *a.search(0));
}
TEST(HashTableTest, SearchElement2) {
	HashTable<int, int> a(10);
	a.insert(10, 105);
	EXPECT_EQ(*a.search(10), 105);
}
TEST(HashTableTest, InsertElement1) {
	HashTable<int, int> a(10);
	a.insert(111, 905);
	a.insert(109, 703);
	a.insert(109, 311);
	a.print();
}
TEST(HashTableTest, ReassembleTest) {
	HashTable<int, int> a(10);
	a.insert(111, 905);
	a.insert(109, 703);
	a.insert(109, 311);
	a.insert(10, 505);
	a.insert(93, 27);
	a.insert(754, 0);
	a.print();
	cout << endl << endl;
	a.insert(1, 9);
	a.insert(34, 27);
	a.print();
	cout << "size: " << a.get_size();
}
//TEST(HashTableTest, ContainsElement) {
//	HashTable<int, int> a(10);
//	a.insert(111, 905);
//	a.insert(109, 703);
//	EXPECT_EQ(a.contains(702), true);
//}
TEST(HashTableTest, InsertOrAssignElement) {
	HashTable<int, int> a(10);
	a.insert(111, 905);
	a.insert(109, 703);
	a.insert_or_assign(109, 311);
	a.print();
	cout << endl << endl;
	a.insert_or_assign(109, 703);
	a.print();
}