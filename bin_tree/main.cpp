#include <iostream>
#include <utility>
class BinTreeNode {
public:
	BinTreeNode() = default;

	void Insert(int value) {
		tree_root = Insert(tree_root, value);
	}
	bool Contains(int value) {
		return Contains(tree_root, value);
	}
	bool Erase(int value) {
		auto res = Erase(tree_root, value);
		tree_root = res.first;
		return res.second;
	}
private:
	struct Node {
		Node(int value) : element(value) {}

		int element;
		Node* left{nullptr};
		Node* right{nullptr};
	};
	Node* Insert(Node* sub_tree, int value) {
		if (!sub_tree) {
			return new Node(value);
		}
		if (value <= sub_tree->element) {
			sub_tree->left = Insert(sub_tree->left, value);
			return sub_tree;
		}
		sub_tree->right = Insert(sub_tree->right, value);
		return sub_tree;
	}

	bool Contains(Node* sub_tree, int value) {
		if (!sub_tree) {
			return false;
		}
		if (value == sub_tree->element) {
			return true;
		}
		if (value < sub_tree->element) {
			return Contains(sub_tree->left, value);
		}
		return Contains(sub_tree->right, value);
	}

	Node* FindMin(Node* tree) {
		if (tree->left == nullptr) {
			return tree;
		}
		return FindMin(tree->left);
	}

	Node* UnlinkMin(Node* tree) {
		if (tree->left == nullptr) {
			return tree->right;
		}
		return UnlinkMin(tree->left);
	}

	std::pair<Node*, bool> Erase(Node* sub_tree, int value) {
		if (!sub_tree) {
			return {nullptr, false};
		}

		if (value == sub_tree->element) {
			Node* temp = sub_tree;
			Node* left = sub_tree->left;
			Node* right = sub_tree->right;
			if (right == nullptr) {
				delete temp;
				return {left, true};
			}
			Node* min = FindMin(right);
			right = UnlinkMin(right);
			min->left = left;
			min->right = right;
			delete temp;
			return {min, true};
		}
		if (value < sub_tree->element) {
			auto res = Erase(sub_tree->left, value);
			sub_tree->left = res.first;
			return {sub_tree, res.second};
		}
		auto res = Erase(sub_tree->right, value);
		sub_tree->right = res.first;
		return {sub_tree, res.second};
	}
	Node* tree_root{nullptr};

};