#include <atomic>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>



class SpinLock {
public:
	void lock(){
		while(state_.exchange(kLocked) != kUnLocked){
//			iterations_count.fetch_add(1);
		}
	}
	void unlock() {
		state_.store(kUnLocked);
	}
//	std::atomic<uint32_t> iterations_count;
private:
	static constexpr uint32_t kLocked = 1;
	static constexpr uint32_t kUnLocked = 0;
	std::atomic<uint32_t> state_{kUnLocked};

};


class Mutex {
public:
	void lock(){
		while(state_.exchange(kLocked) != kUnLocked) {
//			iterations_count.fetch_add(1);
			state_.wait(kLocked);
		}
	}
	void unlock() {
		if (state_.load() == kLockedEnd) {
			state_.store(kUnLocked);
		}
		else {
			state_.store(kUnLocked);
			state_.notify_one(); //order of store and notify_one is important!!!!!
		}
	}
//	std::atomic<uint32_t> iterations_count;
private:
	static constexpr uint32_t kUnLocked = 0;
	static constexpr uint32_t kLocked = 1;
	static constexpr uint32_t kLockedEnd = 2;
	std::atomic<uint32_t> state_{kUnLocked};
};


int main() {
	std::mutex S;
//	std::vector<int> v;
	size_t x = 0;
	std::thread t1([&](){
		for (int i = 0; i < 1000000; ++i) {
			S.lock();
//			v.push_back(i);
			++x;
			S.unlock();
		}
	});
	std::thread t2([&](){
		for (int i = 0; i < 1000000; ++i) {
			S.lock();
//			v.push_back(i);
			++x;
			S.unlock();
		}
	});

	t1.join();
	t2.join();
	std::cout<<x<<"\n";
//	std::cout << x<<" "<<S.iterations_count<<"\n"; //730382 13228


//	SpinLock S;
//	std::vector<int> v;
//	std::thread t1([&](){
//		for (int i = 0; i < 1000000; ++i) {
//			S.lock();
////			S.lock(); DEADLOCK with one thread
//			v.push_back(i);
//			S.unlock();
//		}
//	});
//	t1.join();
//
//	SpinLock S1;
//	SpinLock S2;
//	std::vector<int> v;
//	std::thread t1([&](){
//		for (int i = 0; i < 1000000; ++i) {
//			S1.lock();
//			S2.lock();
//			v.push_back(i);
//			S1.unlock();
//		}
//	});
//	std::thread t2([&](){
//		for (int i = 0; i < 1000000; ++i) {
//			S2.lock();
//			S1.lock();
//			v.push_back(i);
//			S2.unlock();
//		}
//	});
//	t2.join();
//	t1.join();
}