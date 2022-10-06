#include <condition_variable>
#include <atomic>
#include <mutex>
#include <iostream>
#include <thread>

class CyclicBarrier {
public:
	explicit CyclicBarrier(size_t n): p_count_(n){

	}

	// Blocks until all participants have invoked Arrive()
	void Arrive() {
		std::unique_lock<std::mutex> lk(m_);
		size_t index = counter_index_;
		++threads_count_[index];
		if (threads_count_[index] < p_count_) {
			while (index == counter_index_) {
				cv_.wait(lk);
			}
			--threads_count_[index];
		}
		else {
			counter_index_ ^= 1;
			--threads_count_[index];
			lk.unlock();
			cv_.notify_all();
		}
	}

private:
	size_t p_count_;
	size_t threads_count_[2]{0,0};
	std::condition_variable cv_;
	std::mutex m_;
	size_t counter_index_{0};
};

int main(){
	CyclicBarrier barrier(3);
	std::thread t1([&]{
		for (int i = 0; i < 100; ++i) {
			std::cout<<1;
			barrier.Arrive();
		}
	});
	std::thread t2([&]{
		for (int i = 0; i < 100; ++i) {
			std::cout << 2;
			barrier.Arrive();
		}
	});
	std::thread t3([&]{
		for (int i = 0; i < 100; ++i) {
			std::cout << 3;
			barrier.Arrive();
		}
	});
	t1.join();
	t2.join();
	t3.join();


}
