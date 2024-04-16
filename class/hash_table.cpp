#pragma once
#include <iostream>

using namespace std;

namespace hash_table {
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
}