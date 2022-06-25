#include <iostream>
#include <vector>
std::vector<uint32_t> sort_rad(std::vector<uint32_t> &arr, int ref, int shift){
  int map_arr[256];
  std::vector<uint32_t> res(arr.size());
  for (int i = 0; i < 256; ++i){
    map_arr[i] = 0;
  }
  for (int i = 0; i < arr.size(); ++i){
    ++map_arr[(arr[i]&ref)>>shift];
  }
  int temp = map_arr[0];
  int temp2;
  map_arr[0] = 0;
  for (int i = 1; i < 256; ++i){
    temp2 = map_arr[i];
    map_arr[i] = temp + map_arr[i-1];
    temp = temp2;
  }
  int ind;
  for (int i = 0; i < arr.size(); ++i){
    ind = map_arr[(arr[i]&ref)>>shift];
    res[ind] = arr[i];
    ++map_arr[(arr[i]&ref)>>shift];
  }
  return res;
}

void LSD_sort(std::vector<uint32_t> &arr){
  uint32_t ref = 255;
  for (int i = 0; i < 4; ++i){
    arr = sort_rad(arr, ref, 8*i);
    ref = ref<<8;
  }
}

int main(){
  int k;
  std::cin>>k;
  std::vector<uint32_t> v(k);
  for (int i = 0; i < k; ++i){
    std::cin>>v[i];
  }
  LSD_sort(v);
  for (int i = 0; i < k; ++i){
    std::cout<<v[i]<<" ";
  }
  return 0;
}

// 0 1 4 3 6
// 0 0 1 5 32
