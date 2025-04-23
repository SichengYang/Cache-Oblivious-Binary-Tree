#include "BTree.h"
#include <iostream>

void insert_to_tree(BTree<int>* tree, int num)
{
    int index = tree->insert(num);
    cout << "Inserted " << num << " at index: " << index << std::endl;
    tree->print_array();
    tree->print_tree();
    cout << "------------------------" << endl;
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
    insert_to_tree(&tree, 18);
    insert_to_tree(&tree, 1);
    insert_to_tree(&tree, 7);
    insert_to_tree(&tree, 3);
    insert_to_tree(&tree, 4);
    insert_to_tree(&tree, -1);
    insert_to_tree(&tree, -4);
    return 0;
}