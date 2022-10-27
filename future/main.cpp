#include <condition_variable>
#include <mutex>
#include <iostream>
#include <thread>
#include <vector>
#include <cstdlib>

template <typename T>
struct SharedState {
	SharedState() = default;
	void set_value_for_state(T value) {
		std::lock_guard<std::mutex> lk(m_);
		new (reinterpret_cast<T*>(bytes)) T (std::move(value));
		is_res_avaliable = true;
		cv_.notify_one();
	}
	T get_value() {
		std::unique_lock<std::mutex> lk(m_);
		while (!is_res_avaliable) {
			cv_.wait(lk);
		}
		return *reinterpret_cast<T*>(bytes);
	}

//	T data_var;
	uint8_t bytes[sizeof(T)];
	bool is_res_avaliable = false;
	std::condition_variable cv_;
	std::mutex m_;
};


template <typename T>
class Future {
public:
	Future(SharedState<T>* state) : state_(state) {}
	T get() {
		return state_->get_value();
	}
private:
	SharedState<T>* state_;
};

template <typename T>
class Promise {
public:
	void set_value(T data) {
		state_.set_value_for_state(data);
	}
	Future<T> get_future() {
		return Future(std::addressof(state_));
	}
private:
	SharedState<T> state_;
};



int main() {
	srand(time(nullptr));

	const uint64_t TH_CNT = 24;
	std::vector<Promise<double>> promises(TH_CNT);
	std::vector<Future<double>> futures;
	std::vector<std::thread> threads;

	for (auto& promise : promises) {
		futures.emplace_back(promise.get_future());
	}

	for (int i = 0; i < TH_CNT; ++i) {
		threads.emplace_back([i, &promises]() {
			int64_t N = 100000000ull;
			int64_t in_circle = 0;
			int64_t R = RAND_MAX / 2;

			for (int j = 0; j < N; ++j) {
				int64_t x = rand() % (2 * R) - R;
				int64_t y = rand() % (2 * R) - R;
				if (x * x + y * y <= R * R) {
					++in_circle;
				}
			}
			double pi = static_cast<double>(in_circle) / static_cast<double>(N) * 4.0;
			promises[i].set_value(pi);
		});
	}

	double result = 0;
	for (auto& future : futures) {
		double pi = future.get();
		std::cout << pi << "\n";
		result += pi;
	}
	std::cout << result / TH_CNT;

	for (auto& th : threads) {
		th.join();
	}
}
