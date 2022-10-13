#include <mutex>
#include <condition_variable>
#include <iostream>
#include <thread>
#include <vector>

class SharedMutex {
public:
	SharedMutex() : count_readers_(0), is_writer_(false){}
	void lock() {
		std::unique_lock lk(m_);
		while (count_readers_ != 0 || is_writer_){
			cv_.wait(lk);
		}
		is_writer_ = true;
	}
	void unlock() {
		std::lock_guard lk(m_);
		is_writer_ = false;
		cv_.notify_all();
	}

	bool try_lock() {
		std::lock_guard lk(m_);
		if (count_readers_ != 0 || is_writer_) {
			return false;
		}
		is_writer_ = true;
		return true;
	}

	void lock_shared() {
		std::unique_lock lk(m_);
		while(is_writer_) {
			cv_.wait(lk);
		}
		++count_readers_;
	}
	void unlock_shared() {
		std::lock_guard lk(m_);
		--count_readers_;
		if (count_readers_ == 0) {
			cv_.notify_one();
		}
	}

	bool try_lock_shared() {
		std::lock_guard lk(m_);
		if (is_writer_) {
			return false;
		}
		++count_readers_;
		return true;
	}


private:
	std::condition_variable cv_;
	std::mutex m_;
	size_t count_readers_;
	bool is_writer_;
};

int main(){
	SharedMutex m;
	std::vector<int> v;
	v.reserve(20000000);
	int temp = 50;
	std::thread t1([&]{
		for (int i = 0; i < 10000000; ++i) {
			m.lock();
			++temp;
			m.unlock();
		}
	});
	std::thread t2([&]{
		for (int i = 0; i < 10000000; ++i) {
			m.lock();
			++temp;
			m.unlock();
		}
	});
	std::thread t3([&]{
		for (int i = 0; i < 10000000; ++i) {
			m.lock_shared();
			v.push_back(temp);
			m.unlock_shared();
		}
	});
	std::thread t4([&]{
		for (size_t i = 0; i < 10000000; ++i) {
			m.lock_shared();
			v.push_back(temp);
			m.unlock_shared();
		}
	});
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	std::sort(v.begin(), v.end());
	auto l = std::unique(v.begin(), v.end());
	v.erase(l, v.end());
	std::cout<<10000000/v.size()<<std::endl;
	for(auto x:v){
		std::cout<<x<<" ";
	}
}


