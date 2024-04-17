#pragma once
#include <iostream>
#include <vector>

using namespace std;

namespace lab_5 {
	template <typename K, typename V>
	class my_pair : public pair<K, V> {
	private:
		bool _init;
		bool _del;
	public:
		my_pair() : pair<K, V>() {
			_init = false;
			_del = false;
		}
		my_pair(K key, V value) : pair<K, V>(key, value) {
			_init = false;
			_del = false;
		}
		void set_init() {
			_init = true;
		}
		bool get_init() {
			return _init;
		}
		bool get_del() {
			return _del;
		}
		bool is_init() {
			return _init;
		}
		bool is_del() {
			return _del;
		}
		void del() {
			_init = false;
			_del = true;
		}
	};
	template<typename K, typename V>
	class hash_table {
	private:
		size_t _size;
		size_t _filled;
		vector<my_pair<K, V>> _container;
	public:
		hash_table(): _container(10), _size(10), _filled(0) {}
		hash_table(size_t size) {
			vector<my_pair<K, V>> temp(size, {0, 0});
			_container = temp;
			_size = size;
			_filled = 0;
		}
		void print() {
			for (const auto& element : _container) {
				cout << "< key: " << element.first << "> < value : " << element.second << endl;
			}
		}
	};
}