#include <iostream>
#include <cstdlib>

struct Node {
  int x;
  int y;
  Node* left;
  Node* right;
  Node(int x, int y): x(x), y(y) {}
  Node(): left(nullptr), right(nullptr) {}
};



class Treap {
public:
  void insert(int x) {
    treap = insert(treap, x);
    return;
  }

  bool find(int x) {
    return find(treap, x);
  }

  void remove(int x) {
    treap = find(treap, x);
    return;
  }

private:
  Node* treap{nullptr};
  Node* merge(Node* A, Node* B) {
    if (A == nullptr) {
      return B;
    }
    if (B == nullptr) {
      return A;
    }
    if (A->y > B->y) {
      A->right = merge(A->right, B);
      return A;
    }
    B->left = merge(A, B->left);
    return B;
  }

  std::pair<Node*, Node*> split(Node* tr, int num) {
    if (tr == nullptr) {
      return {nullptr, nullptr};
    }
    if (num < tr->x) {
      auto[left, right] = split(tr->left, num);
      tr->left = right;
      return {left, tr};
    }
    auto[left, right] = split(tr->right, num);
    tr->right = left;
    return {tr, right};
  }

  Node* insert(Node* tr, int x) {
    Node* k = new Node(x, std::rand());
    auto [left, right] = split(tr, x);
    k = merge(left, k);
    return merge(k, right);
  }

  bool find(Node* tr, int num) {
    if (tr == nullptr) {
      return false;
    }
    if (tr->x == num) {
      return true;
    }
    if (num < tr->x) {
      return find(tr->left, num);
    }
    return find(tr->right, num);
  }
  Node* remove(Node* tr, int num) {
    if (tr == nullptr) {
      return nullptr;
    }
      if (tr->x == num) {
        Node* aleft = tr->left;
        Node* aright = tr->right;
        delete tr;
        return merge(aleft, aright);
      }
    }
    void remove_all(Node* tr){
      if (tr == nullptr) {
        return;
      }
      remove_all(tr->left);
      remove_all(tr->right);
      delete tr;
      return;
    }

    if (num < tr->x) {
      return merge(find(tr->left, num), tr);
    }
    return merge(tr, find(tr->right, num));
  }
  ~Treap() {
    remove_all(treap);
  }

};



int main() {
  Treap t;
  t.insert(100);
  t.insert(150);
  t.insert(160);
  t.insert(170);
  std::cout << t.find(140) << std::endl;
  return 0;
}
