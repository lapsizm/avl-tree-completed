#include "include/avltree.hpp"

int main() {
    BMSTU::dictionary<int, int> dict(1,5);
    dict.Insert(3, 2);
    dict.Insert(15, 1);
    BMSTU::BstTree<int,int>::TreeNode* temp = dict.Find(15);
    std::cout << temp->key;
    dict.Print();

    return 0;
}
