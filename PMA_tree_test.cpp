#include "PMATree.h"
#include <iostream>

void insert_to_tree(PMATree<int>* tree, int num)
{
    int index = tree->insert(num);
    cout << "Inserted " << num << " at index: " << index << std::endl;
    tree->print_array();
    tree->print_tree();
    cout << "------------------------" << endl;
    cout << endl;
}

void remove_from_tree(PMATree<int>* tree, int num)
{
    tree->remove(num);
    cout << "Removed " << num << endl;
    tree->print_array();
    tree->print_tree();
    cout << "------------------------" << endl;
    cout << endl;
}

int main()
{
    PMATree<int> tree;
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

    cout << "Index of 20: " << tree.search(20) << endl;
    cout << "Index of 7: " << tree.search(7) << endl;

    remove_from_tree(&tree, -1);
    remove_from_tree(&tree, 3);
    remove_from_tree(&tree, 20);
    remove_from_tree(&tree, 30);
    remove_from_tree(&tree, -100);

    return 0;
}