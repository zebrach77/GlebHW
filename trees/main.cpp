#include <iostream>
#include <utility>
#include <cstdint>
struct Node{
  char elem;
  Node* left{nullptr};
  Node* right{nullptr};
}
using std::unordered_map<uint32_t, Node*> = node_storage;


std::pair<Node*, Node*> find_similiar(Node* tree, node_storage &st, uint32_t &char_set){
  if (!tree){
    return {nullptr, nullptr};
  }
  uint32_t left_set = 0u;
  uint32_t right_set = 0u;
  auto res_left = find_similiar(tree->left, st, left_set);
  if (res_left.first){
    return res_left;
  }
  auto res_right = find_similiar(tree->right, st, right_set);
  if (res_right.first){
    return res_right;
  }

  char_set |= left_set | right_set | (uint32_t(1) << (tree->elem - 'a'));
  if (st.find(char_set) != st.end()){
    return {tree, st[char_set]};
  }
  st[char_set] = tree;
  return {nullptr, nullptr};
}
