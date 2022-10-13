#include <mutex>
#include <condition_variable>
#include <iostream>
#include <thread>
#include <vector>

template <typename T>
class Mutexed {
public:
	class LockProxy {
	public:
		LockProxy(T* elem, std::mutex& m) : elem_(elem), lk_(m) {}
		T* operator->() {
			return elem_;
		}
		T& operator*() {
			return *elem_;
		}
	private:
		T* elem_;
		std::lock_guard<std::mutex> lk_;
	};

	LockProxy Lock() {
		return {std::addressof(local_var_), m_};
	}

private:
	std::mutex m_;
	T local_var_;
};


int main() {
	Mutexed<std::vector<int>> M;
	std::thread t1([&]{
		for (size_t i = 0; i < 100000; ++i) {
			auto ref = M.Lock();
			ref->push_back(i);
		}
	});
	std::thread t2([&]{
		for (size_t i = 100000; i < 200000; ++i) {
			auto ref = M.Lock();
			ref->push_back(i);
		}
	});

	t1.join();
	t2.join();
	auto ref = M.Lock();
	for (size_t i = 0; i< ref->size(); ++i) {
		std::cout<<(*ref)[i]<<" ";
	}
	std::cout<<std::endl;
}