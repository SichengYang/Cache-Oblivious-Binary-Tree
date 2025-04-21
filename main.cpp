#include "BTree.h"
#include <iostream>

int main()
{
    BTree<int> tree;
    int index = tree.insert(10);
    cout << "Inserted 10 at index: " << index << std::endl;
    index = tree.insert(20);
    cout << "Inserted 20 at index: " << index << std::endl;

    tree.print_tree();
    return 0;
}