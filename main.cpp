#include "BTree.h"
#include <iostream>

void insert_to_tree(BTree<int>* tree, int num)
{
    cout << "Insert " << num << endl;
    int index = tree->insert(num);
    cout << "Insert at index: " << index << endl;
    tree->print_array();
    tree->print_tree();
    cout << "------------------------" << endl;
    cout << endl;
}

void remove_from_tree(BTree<int>* tree, int num)
{
    cout << "Remove " << num << endl;
    tree->remove(num);

    tree->print_array();
    tree->print_tree();
    cout << "------------------------" << endl;
    cout << endl;
}

int main()
{
    BTree<int> tree;

    for(int i = 0; i < 100000; ++i)
    {
        tree.insert(i);
    }

    tree.print_tree();

    return 0;
}