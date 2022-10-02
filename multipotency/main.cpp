
#include <iostream>
#include <thread>
#include <atomic>
#include <array>
#include <queue>
#include <optional>

class PetersonMutex
{
public:
	PetersonMutex()
	{
		want[0].store(false);
		want[1].store(false);
		waiting.store(0);
	}

	void lock(int threadId)
	{
		int other = 1 - threadId;
		want[threadId].store(true); // индикатор интереса текущего потока
		waiting.store(threadId); // говорим, что этот поток будет ждать, если понадобится
		/* Цикл ожидания. Мы находимся в этом цикле, если второй процесс выполняет свою
		критическую секцию. Когда второй процесс выйдет из критической секции, выполнится
		процедура unlock(int threadId), флаг заинтересованности (want[other])
		станет равен false, и цикл закончится. */
		while (want[other].load() && waiting.load() == threadId) {
			// wait
		}
	}

	void unlock(int threadId) {
		want[threadId].store(false);
	}

private:
	std::array<std::atomic<bool>, 2> want; // флаги заинтересованности потоков
	std::atomic<int> waiting; // номер ждущего потока
};

class SpinLock {
public:
	void lock() {
		while (state_.exchange(kLocked) == kLocked) {
			while (state_.load() == kLocked) {
			}
		}
	}

	void unlock() {
		state_.store(kUnlocked);
	}
private:
	static constexpr uint32_t kLocked = 1;
	static constexpr uint32_t kUnlocked = 0;
	std::atomic<uint32_t> state_{kUnlocked};
};

class MutexTry1 {
public:
	void lock() {
		while (state_.exchange(kLocked) == kLocked) {
			state_.wait(kLocked);
		}
	}

	void unlock() {
		state_.store(kUnlocked);
		state_.notify_one();
	}

private:
	static constexpr uint32_t kLocked = 1;
	static constexpr uint32_t kUnlocked = 0;
	std::atomic<uint32_t> state_{kUnlocked};
};

class Mutex {
public:
	Mutex() : state_(kUnlocked) {
	}

	void lock() {
		uint32_t try_state = kLockedWithNoWaiters;
		while (CompareExchange(kUnlocked, try_state) != kUnlocked) {
			try_state = kLockedWithWaiters;
			if (CompareExchange(kLockedWithNoWaiters, try_state) != kUnlocked) {
				state_.wait(kLockedWithWaiters);
			}
		}
	}

	void unlock() {
		if (state_.exchange(kUnlocked) == kLockedWithWaiters) {
			state_.notify_one();
		}
	}

private:
	uint32_t CompareExchange(uint32_t old, uint32_t upd) {
		state_.compare_exchange_weak(old, upd);
		return old;
	}

	static constexpr uint32_t kLockedWithWaiters = 2u;
	static constexpr uint32_t kLockedWithNoWaiters = 1u;
	static constexpr uint32_t kUnlocked = 0u;

	std::atomic<uint32_t> state_;
};

template <typename Lockable>
class LockGuard {
public:
	LockGuard(Lockable& lk) : lock_(lk) {
		lock_.lock();
	}

	~LockGuard() {
		lock_.unlock();
	}
private:
	Lockable& lock_;
};


template <typename T>
class BlockingQueue {
public:
	void Push(const T item) {
		{
			std::lock_guard<std::mutex> lk(m_); // RAII idiom
			data_.push_back(item);
		}
		cv_.notify_one();
	}

	std::optional<T> Get() {
		std::unique_lock<std::mutex> lk(m_);
		while (!is_closed && data_.size() == 0) {
			cv_.wait(lk);
		}
		if (data_.size() > 0) {
			T elem = std::move(data_.front());
			data_.pop_front();
			return elem;
		}
		return std::nullopt;
	}

	void Close() {
		{
			std::lock_guard<std::mutex> lk(m_); // RAII idiom
			is_closed = true;
		}
		cv_.notify_all();
	}

private:
	std::mutex m_;
	std::condition_variable cv_;
	std::deque<T> data_;
	bool is_closed{false};
};

int main() {
	std::mutex m;

	int x = 0;
	BlockingQueue<int> cnt_queue;
	BlockingQueue<int> cnt_queue2;
	std::thread th1([&x, &m, &cnt_queue, &cnt_queue2]() {
		int z = 0;
		for (int i = 0; i < 10; ++i) {
			cnt_queue2.Push(z + 1);
			auto t = cnt_queue.Get();
			if (t) {
				z = *t;
				std::lock_guard<std::mutex> lk(m);
				std::cout << "Thread 1: " << z << "\n";
			}
		}
		cnt_queue2.Close();
	});

	std::thread th2([&x, &m, &cnt_queue, &cnt_queue2] () {
		int z;
		for (int i = 0; i < 10; ++i) {
			auto t = cnt_queue2.Get();
			if (t) {
				z = *t;
				{
					std::lock_guard<std::mutex> lk(m);
					std::cout << "Thread 2: " << z << "\n";
				}
				cnt_queue.Push(z + 1);
			} else {
				std::lock_guard<std::mutex> lk(m);
				std::cout << "Fail\n";
			}
		}
		cnt_queue.Close();
	});


	th1.join();
	th2.join();

	std::cout << x;

	return 0;
}
