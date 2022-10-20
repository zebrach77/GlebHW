#include <cstdlib>
#include <thread>
#include <atomic>
#include <vector>
#include <iostream>

const size_t R = 5000000;
const size_t dots_per_thread = 20000000;
const size_t threads_count = 8;
int main() {
	std::srand(std::time(nullptr));
	std::atomic<size_t> count_circle = 0;
	std::vector<std::thread> v;
	for (size_t i = 0; i < threads_count; ++i) {
		v.emplace_back([&]{
			for (size_t i = 0; i < dots_per_thread; ++i) {
				size_t x = (std::rand() % (2 * R)) - R;
				size_t y = (std::rand() % (2 * R)) - R;
				if (x*x+y*y<=R*R) {
					++count_circle;
				}
			}
		});
	}
	for (auto& th:v) {
		th.join();
	}
	long double x = count_circle/(long double)(threads_count*dots_per_thread)*(long double)4.0;
	std::cout<<x;
}