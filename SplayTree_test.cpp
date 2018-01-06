//
// Created by Michal on 29/11/2017.
//

#include "SplayTree.h"

void printInt(const int& x);

class Comp {
    int x;
public:
    explicit Comp(int& x): x(x) {}
    int operator()(const int& y) const {
        if (x == y) return 0;
        else if (x > y) return 1;
        return -1;
    }
};

class getScore {
public:
    explicit getScore() {}
    int operator()(const int& T) const {
        return T;
    }
};

void printInt(const int& x) {
    std::cout << x;
    std::cout << " ";
}

int main() {
    SplayTree<int, getScore> tree;
    int arr[8] = {1,15,3,8,32,6,4,8};
    for(int i=0; i<8; i++)
        tree.insert(Comp(arr[i]), arr[i]);
    std::cout << "InOrder Print: ";
    tree.inOrder(tree.root, printInt);
    std::cout << "\nInOrder new tree Print: " << std::endl;
    tree.inOrderPrint(tree.root);
    std::cout << std::endl << "PreOrder Print: ";
    tree.preOrder(tree.root, printInt);
    std::cout << std::endl << "InOrder Reversed Print: ";
    tree.inOrderReverse(tree.root, printInt);
}


