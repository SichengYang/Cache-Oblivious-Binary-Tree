#include "BTree.h"
#include <iostream>

void insert_to_tree(BTree<int>* tree, int num)
{
    int index = tree->insert(num);
    cout << "Inserted 10 at index: " << index << std::endl;
    tree->print_tree();
    cout << endl;
}

int main()
{
    BTree<int> tree;
    insert_to_tree(&tree, 10);
    insert_to_tree(&tree, 20);
    insert_to_tree(&tree, 5);
    insert_to_tree(&tree, 15);
    insert_to_tree(&tree, 25);
    insert_to_tree(&tree, 30);
    return 0;
}