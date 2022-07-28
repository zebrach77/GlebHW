#include <iostream>

#include <forward_list>


template <typename T>
size_t hash_f(const T& key) {
	void* p = &key;
	if (sizeof(key) == 1) {
		return *reinterpret_cast<uint8_t*>(p);
	}
	if (sizeof(key) == 2) {
		return *reinterpret_cast<uint16_t*>(p);
	}
	if (sizeof(key) == 3) {
		return *reinterpret_cast<uint16_t*>(p);
	}
	if (sizeof(key) >= 4 && sizeof(key) < 8) {
		return *reinterpret_cast<uint32_t*>(p);
	}
	return *reinterpret_cast<size_t*>(p);
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
	return hash_f(static_cast<double>(key));
}

template <typename T>
class HashTable {
public:

	HashTable() : hash_list_(new std::forward_list<T>[INITLENGTH]), length_(INITLENGTH) {}

	void insert(const T& elem) {
		if (size_ >= length_) {
			rehash();
		}
		if (help_insert(hash_list_, length_, elem)) {
			++size_;
		}
	}

	bool contains(const T& elem) {
		size_t hash = hash_f(elem) % length_;
		return std::find(hash_list_[hash].begin(), hash_list_[hash].end(), elem) != hash_list_[hash].end();
	}

	void remove(const T& elem) {
		size_t hash = hash_f(elem) % length_;

		if (std::find(hash_list_[hash].begin(), hash_list_[hash].end(), elem) == hash_list_[hash].end()) {
			--size_;
			std::erase(hash_list_[hash], elem);
		}
	}

private:
	static const size_t INITLENGTH = 32;
	std::forward_list<T>* hash_list_;
	size_t length_;
	size_t size_;

	bool help_insert(std::forward_list<T>* hash_list, size_t length, const T& elem) {
		size_t hash = hash_f(elem) % length;
		if (std::find(hash_list[hash].begin(), hash_list[hash].end(), elem) == hash_list[hash].end()) {
			hash_list[hash].push_front(elem);
			return true;
		}
		return false;
	}

	void rehash() {
		std::forward_list<T>* temp_arr = new std::forward_list<T>[length_*2];
		for (size_t i = 0; i < length_; ++i) {
			for (auto& el : hash_list_[i]) {
				help_insert(temp_arr, 2 * length_, el);
			}
		}
		delete[] hash_list_;
		hash_list_ = temp_arr;
		length_ <<= 1;
	}

};

int main() {
	HashTable<double>* Obj = new HashTable<double>();
	Obj->insert(5.34);
	Obj->insert(1.25);
	std::cout<<Obj->contains(1.25)<<std::endl;
	return 0;
}