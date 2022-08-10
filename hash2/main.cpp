#include <iostream>
template <typename T>
struct Cell {
	bool is_elem_deleted;
	T elem;
	bool is_empty;
};

template <typename T>
size_t hash_f(const T& key) {
	const void* p = reinterpret_cast<const void*>(&key);
	if (sizeof(key) == 1) {
		return *reinterpret_cast<const uint8_t*>(p);
	}
	if (sizeof(key) == 2) {
		return *reinterpret_cast<const uint16_t*>(p);
	}
	if (sizeof(key) == 3) {
		return *reinterpret_cast<const uint16_t*>(p);
	}
	if (sizeof(key) >= 4 && sizeof(key) < 8) {
		return *reinterpret_cast<const uint32_t*>(p);
	}
	return *reinterpret_cast<const size_t*>(p);
}
template <typename T>
size_t hash_f2(const T& key) {
	const void* p = reinterpret_cast<const void*>(&key);
	if (sizeof(key) == 1) {
		return *reinterpret_cast<const uint8_t*>(p);
	}
	if (sizeof(key) == 2) {
		return *reinterpret_cast<const uint16_t*>(p);
	}
	if (sizeof(key) == 3) {
		return *reinterpret_cast<const uint16_t*>(p);
	}
	if (sizeof(key) >= 4 && sizeof(key) < 8) {
		return *reinterpret_cast<const uint32_t*>(p);
	}
	return *reinterpret_cast<const size_t*>(p);
}

//h = x0 + x1 * p + x2 * p^2 + x3 * p^3
//h = x0 + p(x1 + p(x2 * ... ))

size_t hash_f(const std::string& key) {
	size_t t = 31;
	size_t res = 0;
	for (size_t i = 0; i < key.size(); ++i) {
		res += key[i];
		res *= t;
	}
	return res;
}

size_t hash_f(const size_t& key) {
	return key;
}

size_t hash_f(const int& key) {
	return 2*abs(key) - key;
}

size_t hash_f(const double& key) {
//	const void* p = reinterpret_cast<const void*>(&key);
//	return *reinterpret_cast<const size_t*>(p);
	return *reinterpret_cast<const size_t*>(&key);
}

size_t hash_f(const float& key) {
	return hash_f(static_cast<const double>(key));
}


template <typename T>
class HashTable {
public:
	HashTable() : deleted_(0), size_(0), capacity_(INIT_LENGTH),
		arr(reinterpret_cast<Cell<T>*>(new int8_t[sizeof(Cell<T>)*INIT_LENGTH])) {

		for(size_t i = 0; i < INIT_LENGTH; ++i) {
			arr[i]->is_empty = true;
			arr[i]->is_elem_deleted = false;
		}
	}


	void help_insert(const T& elem, Cell<T>* arr_pointer, size_t capacity) {
		size_t hash = hash_f<T>(elem) % capacity;
		size_t hash2 = hash_f2<T>(elem) % capacity;
		size_t ind = hash;
		while (!arr_pointer[ind]->is_empty) {
			ind += hash2;
		}
		arr_pointer[ind]->is_empty = false;
		arr_pointer[ind]->elem = elem;
	}

	void insert(const T& elem) {
		if (capacity_ + deleted_ >= size_) {
			rehash();
		}
		help_insert(elem, arr, capacity_*2);
	}

	void rehash() {
		Cell<T>* arr_temp = reinterpret_cast<Cell<T>*>(new int8_t[sizeof(Cell<T>)*2*capacity_]);
		for(size_t i = 0; i < capacity_*2; ++i) {
			arr_temp[i]->is_empty = true;
			arr_temp[i]->is_elem_deleted = false;
		}
		for(size_t i = 0; i < capacity_; ++i) {
			if (!(arr[i]->is_empty) && !(arr[i]->is_elem_deleted)) {
				help_insert(arr[i], arr_temp, capacity_*2);
			}
		}
		delete[] arr;
		arr = arr_temp;
	}

private:
	static constexpr size_t INIT_LENGTH = 32;
	size_t deleted_;
	size_t size_;
	size_t capacity_;
	Cell<T>* arr;




};

struct foo {
	int x;
	foo() = delete;
};

int main() {
//	HashTable<foo> x;
	int8_t* h = new int8_t[sizeof(foo)];
	foo* g = reinterpret_cast<foo*>(h);
	std::cout<<g->x<<std::endl;

}