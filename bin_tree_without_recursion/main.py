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
        self.__add_antirec(value)

    def IsElement(self, value):
        return self.__is_element_antirec(value)

    def Remove(self, value):
        return self.__remove_antirec(value)


    def __add_antirec(self, value):
        if self.tree is None:
            self.tree = Node(value)
            return
        temp_tree = self.tree.left if self.tree.Compare(value) else self.tree.right
        temp_tree_parent = self.tree
        while not temp_tree is None:
            temp_tree_parent = temp_tree
            temp_tree = temp_tree.left if temp_tree.Compare(value) else temp_tree.right
        if temp_tree_parent.Compare(value):
            temp_tree_parent.left = Node(value)
            return
        temp_tree_parent.right = Node(value)
        return

    def __is_element_antirec(self, value):
        if self.tree is None:
            return False
        temp_tree = self.tree
        while not temp_tree is None and temp_tree.element != value:
            temp_tree = temp_tree.left if temp_tree.Compare(value) else temp_tree.right
        if not temp_tree is None:
            return True
        return False

    def __remove_antirec(self, value):
        if self.tree is None:
            self.tree = Node(value)
            return False
        temp_tree = self.tree.left if self.tree.Compare(value) else self.tree.right
        temp_tree_parent = self.tree
        while not temp_tree is None and temp_tree.element != value:
            temp_tree_parent = temp_tree
            temp_tree = temp_tree.left if temp_tree.Compare(value) else temp_tree.right
        if not temp_tree is None:
            ind = "l" if temp_tree_parent.Compare(value) else "r"
            lt = temp_tree.left
            rt = temp_tree.right
            if rt is None:
                temp_tree_parent.left = lt
                return True
            mn = self.__find_min(rt)
            rt = self.__unlink_min(rt)
            mn.right = rt
            mn.left = lt
            if ind == "l":
                temp_tree_parent.left = mn
            else:
                temp_tree_parent.right = mn
            return True
        return False



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