#include <iostream>
#include <array>
#include <limits>
#include <cmath>
int weight(std::array<uint32_t, 24> &arr, uint32_t mask, size_t n) {
  int summ = 0;
  for (int i = 0; i < n; ++i) {
    uint32_t j = 1<<i;
    if ((mask&j) == j) {
      summ += arr[i];
    }
  }
  return summ;
}


int main() {
  size_t n;
  std::cin>>n;
  std::array<uint32_t, 24> arr;
  int sum_all = 0;
  for (int i = 0; i < n; ++i) {
    std::cin>>arr[i];
    sum_all += arr[i];
  }
  uint32_t mask_end = 1<<n;
  uint32_t mask_temp = 0;
  int mn_diff = std::numeric_limits<int>::max();
  for (uint32_t mask = 0; mask < mask_end; ++mask) {
    int sum1 = weight(arr, mask, n);
    int sum2 = sum_all - sum1;
    if (std::abs(sum2-sum1) < mn_diff) {
      mn_diff = std::abs(sum2-sum1);
    }
  }
  std::cout<<mn_diff<<std::endl;
}
