import random

class Node:
    def __init__(self, value):
        self.left = None
        self.right = None
        self.element = value

    def Compare(self, value):
        return value <= self.element

    def IsEmpty(self):
        return self.element is None


class BinTree:
    def __init__(self, value):
        self.tree = Node(value)

    def Add(self, value):
        self.tree = self.__add(self.tree, value)

    def IsElement(self, value):
        return self.__is_element(self.tree, value)

    def Remove(self, value):
        bool_value, self.tree = self.__remove(self.tree, value)
        return bool_value

    def __add(self, sub_tree, value):
        if sub_tree is None:
            return Node(value)
        if sub_tree.Compare(value):
            sub_tree.left = self.__add(sub_tree.left, value)
            return sub_tree
        sub_tree.right = self.__add(sub_tree.right, value)
        return sub_tree

    def __is_element(self, sub_tree, value):
        if sub_tree is None:
            return False
        if sub_tree.element == value:
            return True
        if sub_tree.Compare(value):
            return self.__is_element(sub_tree.left, value)
        return self.__is_element(sub_tree.right, value)

    def __remove(self, sub_tree, value):
        if sub_tree is None:
            return False, None
        if sub_tree.element == value:
            t_left = sub_tree.left
            t_right = sub_tree.right
            if t_right.IsEmpty:
                return True, t_left
            min_node = self.__find_min(t_right)
            t_right = self.__unlink_min(t_right)
            min_node.left = t_left
            min_node.right = t_right
            return True, min_node
        if sub_tree.Compare(value):
            bool_val, tree = self.__remove(sub_tree.left, value)
            sub_tree.left = tree
            return bool_val, sub_tree
        bool_val, tree = self.__remove(sub_tree.right, value)
        sub_tree.right = tree
        return bool_val, sub_tree

    def __find_min(self, sub_tree):
        if sub_tree.left is None:
            return sub_tree
        return self.__find_min(sub_tree.left)

    def __unlink_min(self, sub_tree):
        if sub_tree.left is None:
            return sub_tree.right
        return self.__unlink_min(sub_tree.left)


btr = BinTree(51)
for i in range(50,100, 2):
    btr.Add(i)
for i in range(35, 5, -1):
    btr.Add(i)
for i in range(100):
    print(i, btr.IsElement(i))
print("\n\n\n")
for i in range(70, 80):
    print(i, btr.Remove(i))
for i in range(100):
    print(i, btr.IsElement(i))