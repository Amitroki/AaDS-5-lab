#pragma once
#include <iostream>
#include <vector>

using namespace std;

namespace lab_5 {

	double fractional_part(double num) {
		return num - floor(num);
	}

	template <typename K>
	int get_hash(K key, size_t sz) {
		int a = 1636787;
		int w = 64;
		int result = (sz * (fractional_part(a * key / (w * 1.0)))) / 1;
		return result;
	}

	template <typename K, typename V>
	class Pair : public pair<K, V> {
	private:

		bool _del;

	public:
		Pair() : pair<K, V>() {
			_del = false;
		}
		Pair(K key, V value) : pair<K, V>(key, value) {
			_del = false;
		}
		bool is_del() {
			return _del;
		}
		void del() {
			_del = true;
		}
	};
	template<typename K, typename V>
	class HashTable {
	private:
		size_t _size;
		size_t _filled;
		vector<Pair<K, V>> _container;

		void copy(const HashTable& other) {
			_size = other._size;
			_filled = other._filled;
			_container = other._container;
		}

		void clear() {
			_container.clear();
			_size = 0;
			_filled = 0;
		}
			
	public:

		HashTable(): _container(10), _size(10), _filled(0) {}
		HashTable(size_t size) {
			vector<Pair<K, V>> temp(size, {0, 0});
			_container = temp;
			_size = size;
			_filled = 0;
		}

		HashTable(const HashTable& other) {
			copy(other);
		}

		~HashTable() {
			this->clear();
		}

		size_t get_size() const {
			return _size;
		}

		HashTable operator=(const HashTable& other) {
			auto newTable(other);
			return newTable;
		}

		V* search(K key) {
			size_t function = get_hash(key, this->get_size());
			while (function < this->get_size()) {
				if (_container[function].first == key && !_container[function].is_del()) {
					return &_container[function].second;
				}
				function++;
			}
			return nullptr;
		}

		/*void insert(K key, V value) {
			if (!search(key)) return;
			Pair<K, V> new_element(key, value);
			_container[get_hash(key, this->get_size())] = new_element;
		}*/

		void print() {
			for (const auto& element : _container) {
				cout << "< key: " << element.first << "> < value : " << element.second << endl;
			}
		}
	};
}