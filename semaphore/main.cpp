#include <condition_variable>
#include <mutex>
#include <thread>
#include <iostream>

class Semaphore {
public:
	Semaphore(size_t number_of_coins): coins_count_(number_of_coins) {}
	void Acquire() {
		std::unique_lock<std::mutex> lk(m_);
		while (coins_count_ == 0) {
			cv_.wait(lk);
		}
		--coins_count_;
	}

	void Release() {
		std::unique_lock<std::mutex> lk(m_);
		++coins_count_;
		if (coins_count_ == 1) {
			cv_.notify_one();
		}
	}
	void print() {
		std::cout<<coins_count_<<std::endl;
	}
private:
	std::condition_variable cv_;
	size_t coins_count_;
	std::mutex m_;
};


int main() {
	Semaphore s(2000000);
	std::thread t2([&] {
		for (size_t i = 0; i < 1000000; ++i) {
			s.Acquire();
//			s.print();
		}
		for (size_t i = 0; i < 1000000; ++i) {
			s.Release();
//			s.print();
		}
	});
	std::thread t1([&]{
		for (size_t i = 0; i < 1000000; ++i) {
			s.Acquire();
//			s.print();
		}
		for (size_t i = 0; i < 1000000; ++i) {
			s.Release();
//			s.print();
		}
	});
//	std::thread t3([&] {
//		for (size_t i = 0; i < 10000; ++i) {
//
//		}
//	});
	t1.join();
	t2.join();
//	t3.join();
	s.print();
}