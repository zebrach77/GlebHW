#include <iostream>

class HeapMin {
public:
	HeapMin() : arr_heap_(new int[8]), capacity_(8), size_(0) {}

	bool IsEmpty() {
		return size_ == 0;
	}

	int GetMin() {
		return arr_heap_[0];
	}

	void Insert(int value) {
		if (size_ == capacity_) {
			Reserve();
		}
		arr_heap_[size_++] = value;
		SiftUp(size_ - 1);
	}

	void PopMin() {
		std::swap(arr_heap_[0], arr_heap_[--size_]);
		SiftDown(0);
	}

private:
	void SiftUp(size_t start_index) {
		if (start_index == 0) {
			return;
		}
		size_t parent_index = (start_index - 1) / 2;
		if (arr_heap_[start_index] < arr_heap_[parent_index]) {
			std::swap(arr_heap_[start_index], arr_heap_[parent_index]);
			SiftUp(parent_index);
		}
	}

	void SiftDown(size_t start_index) {
		size_t left = start_index * 2 + 1;
		size_t right = left + 1;
		size_t min_index = start_index;
		if (left < size_ && arr_heap_[left] < arr_heap_[min_index]) {
			min_index = left;
		}
		if (right < size_ && arr_heap_[right] < arr_heap_[min_index]) {
			min_index = right;
		}
		if (min_index != start_index) {
			SiftDown(min_index);
		}
	}

	void Reserve() {
		int* new_data = new int[capacity_ * 2];
		for (size_t i = 0; i < size_; ++i) {
			new_data[i] = arr_heap_[i];
		}
		delete[] arr_heap_;
		arr_heap_ = new_data;
		capacity_ *= 2;
	}

	int* arr_heap_;
	size_t capacity_;
	size_t size_;
};


int main() {

}