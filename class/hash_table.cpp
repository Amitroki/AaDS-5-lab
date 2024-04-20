#pragma once
#include <iostream>
#include <vector>
#include <random>

using namespace std;

namespace lab_5 {

	double fractional_part(double num) {
		return num - floor(num);
	}

	template <typename K>
	int get_hash(K key, size_t sz, size_t i = 0) {
		int a = 1636787;
		int w = 64;
		return (int)(((sz * (fractional_part(a * key / (w * 1.0)))) / 1) + i) % sz;
	}

	int random(int a, int b) {
		std::random_device random_device;
		std::mt19937 generator(random_device());
		std::uniform_int_distribution<> distribution(a, b);
		int res = distribution(generator);
		return res;
	}

	template <typename K, typename V>
	class Pair : public pair<K, V> {
	private:

		bool _del;
		bool _init;

	public:
		Pair() : pair<K, V>() {
			_del = false;
			_init = false;
		}
		Pair(K key, V value) : pair<K, V>(key, value) {
			_del = false;
			_init = false;
		}
		void set_init() {
			_init = true;
			_del = false;
		}
		bool is_init() const {
			return _init;
		}
		bool is_del() const {
			return _del;
		}
		void del() {
			_init = false;
			_del = true;
		}
	};
	template<typename K, typename V>
	class HashTable {
	private:
		size_t _size;
		size_t _filled;
		double _fill_factor = 0.7;
		vector<Pair<K, V>> _container;

		void copy(const HashTable& other) {
			_size = other._size;
			_filled = other._filled;
			_container = vector<Pair<K, V>>(other._container);
		}

		void clear() {
			_container.clear();
			_size = 0;
			_filled = 0;
		}

		void reassemble() {
			size_t new_size = (size_t)(this->get_size() * 1.5);
			vector<Pair<K, V>> new_table(new_size);
			size_t filled_for_new_table = 0;
			for (auto& element : _container) {
				if (element.is_init()) {
					size_t function = get_hash(element.first, new_size);
					size_t i = 0;
					while (new_table[function].is_init()) {
						i++;
						function = get_hash(element.first, new_size, i);
					}
					new_table[function] = element;
					new_table[function].set_init();
					filled_for_new_table++;
				}
			}
			_container.clear();
			_container = new_table;
			_size = new_size;
			_filled = filled_for_new_table;
		}
			
	public:

		HashTable(): _container(10), _size(10), _filled(0) {}
		HashTable(size_t size) {
			_container = vector<Pair<K, V>>(size);
			_size = size;
			_filled = 0;
		}

		HashTable(const HashTable& other) {
			copy(other);
		}

		HashTable(size_t size, size_t number_of_elements, size_t lbf, size_t rbf) {
			_container = vector<Pair<K, V>>(size);
			_size = size;
			_filled = 0;
			for (int i = 0; i < number_of_elements; i++) {
				insert(random(lbf, rbf), random(lbf, rbf));
			}
		}

		~HashTable() {
			this->clear();
		}

		size_t get_size() const {
			return _size;
		}

		vector<Pair<K, V>> get_container() const {
			return _container;
		}

		HashTable& operator=(const HashTable& other) {
			*this = newTable(other);
			return *this;
		}

		V* search(K key) {
			size_t function = get_hash(key, _size);
			size_t i = 0;
			while (_container[function].is_init() || _container[function].is_del()) {
				if (_container[function].first == key && _container[function].is_del() == false) {
					return &_container[function].second;
				}
				i++;
				function = get_hash(key, _size, i);
			}
			return nullptr;
		}

		void insert(K key, V value) {
			if (search(key) != nullptr) return;
			Pair<K, V> new_element(key, value);
			size_t function = get_hash(key, this->get_size());
			size_t i = 0;
			while (_container[function].is_init()) {
				i++;
				function = get_hash(key, this->get_size(), i);
			}
			_container[function] = new_element;
			_container[function].set_init();
			_filled++;
			if ((double)_filled / _container.size() >= _fill_factor) {
				this->reassemble();
			}
		}

		void insert_or_assign(K key, V value) {
			V* current_value = search(key);
			if (current_value) {
				*current_value = value;
			}
			else {
				insert(key, value);
			}
		}

		bool contains(V value) {
			for (auto& element : _container) {
				if (element.second == value && element.is_del() == false) {
					return true;
				}
			}
			return false;
		}

		bool erase(K key) {
			if (!search(key)) return false;
			int function = get_hash(key, get_size());
			int i = 0;
			while (_container[function].first != key) {
				i++;
				function = get_hash(key, get_size(), i);
			}
			_container[function].del();
			_filled--;
		}

		int count(K key) {
			int function = get_hash(key, get_size());
			int count = 0;
			for (const auto& element : _container) {
				if (element.is_init() && !element.is_del()) {
					if (get_hash(element.first, get_size()) == function) count++;
				}
			}
			return count;
		}
		
		void print() const {
			for (const auto& element : _container) {
				cout << "< key: " << element.first << "> < value : " << element.second << " >" << " < deleted: " << (element.is_del()? "TRUE" : "FALSE") << " >" << endl;
			}
		}
	};
	
	double the_dependence_function(size_t size_of_creating_table, size_t number_of_elements, size_t lbf, size_t rbf) {
		HashTable<int, int> new_table(size_of_creating_table, number_of_elements, lbf, rbf);
		vector<int> the_keeper_of_hash;
		double result = 0;
		for (const auto& element : new_table.get_container()) {
			if (element.is_init()) the_keeper_of_hash.push_back(get_hash(element.first, new_table.get_size()));
		}
		sort(the_keeper_of_hash.begin(), the_keeper_of_hash.end());
		for (int i = 0; i < the_keeper_of_hash.size() - 1; i++) {
			if (the_keeper_of_hash[i] == the_keeper_of_hash[i + 1]) {
				result++;
			}
		}
		return result / number_of_elements;
	}

	double task(size_t size_of_creating_table, size_t number_of_elements, size_t lbf, size_t rbf) {
		double result = 0;
		for (int i = 0; i < 100; i++) {
			result += the_dependence_function(size_of_creating_table, number_of_elements, lbf, rbf);
		}
		return result / 100;
	}
}