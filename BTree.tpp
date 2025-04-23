#include "BTree.h"

// debug purpose
using namespace std;
#include <iostream>
#include <iomanip>

template <typename T>
BTree<T>::BTree() : root(-1), leave_height(100) {}

template <typename T>
BTree<T>::~BTree() {}

template <typename T>
void BTree<T>::rebalance(int index)
{
    
}

template <typename T>
void BTree<T>::shift_right(int index, int right_index)
{
    cout << "shifting right from index: " << index << " by " << right_index << endl;
    int start = array[array[array[index].parent].parent].left;
    // shift all elements to the right by 3 elements
    for (int i = 0; i < array.size(); i += 1)
    {
        if (array[i].parent >= index)
        {
            array[i].parent += right_index;
        }
        if (array[i].left >= index)
        {
            array[i].left += right_index;
        }
        if (array[i].right >= index)
        {
            array[i].right += right_index;
        }
    }
}

template <typename T>
int BTree<T>::left_insert(T value, int parent, int current)
{
    int insert_height = array[parent].height - 1;

    int left_of_parent = array[array[parent].parent].left;
    int insert_after_index = 0;
    // if the parent is the left child of its parent
    if (parent == left_of_parent)
    {
        // parent of right is current's parent's parent's right child
        insert_after_index = array[array[parent].parent].right;
    }
    // if the parent is the right child of its parent
    else
    {
        if (array[left_of_parent].right != -1)
        {
            insert_after_index = array[array[left_of_parent].right].right;
        }
        else if (array[left_of_parent].left != -1)
        {
            insert_after_index = array[array[left_of_parent].left].right;
        }
        else
        {
            insert_after_index = parent;
        }
    }

    shift_right(insert_after_index + 1, 3); // shift everything to the right by 3 elements since we inserted 3 new nodes

    // insert new node in the array after the right element of parent
    Node<T> new_node(value, insert_height);
    new_node.parent = parent;
    auto pos = array.insert(array.begin() + insert_after_index + 1, new_node);
    int index = pos - array.begin();
    array[parent].left = index;

    return index;
}

template <typename T>
int BTree<T>::right_insert(T value, int parent, int current)
{
    int insert_height = array[parent].height - 1;

    int left_of_parent = array[array[parent].parent].left;
    int insert_after_index = 0;

    // if the parent is the left child of its parent
    if (parent == left_of_parent)
    {
        if (array[parent].left != -1)
        {
            insert_after_index = array[array[parent].left].right;
        }
        else
        {
            insert_after_index = array[array[parent].parent].right;
        }
    }
    // if the parent is the right child of its parent
    else
    {
        // sequentially check if there are blocks of parent-children before
        if (array[parent].left != -1)
        {
            insert_after_index = array[array[parent].left].right;
        }
        else if (array[left_of_parent].right != -1)
        {
            insert_after_index = array[array[left_of_parent].right].right;
        }
        else if (array[left_of_parent].left != -1)
        {
            insert_after_index = array[array[left_of_parent].left].right;
        }
        else
        {
            // insert after the parent if there is nothing ahead
            insert_after_index = parent;
        }
    }

    shift_right(insert_after_index + 1, 3); // shift everything to the right by 3 elements since we inserted 3 new nodes

    // insert new node next to the parent (right of the previous parent)
    Node<T> new_node(value, insert_height);
    new_node.parent = parent;
    auto pos = array.insert(array.begin() + insert_after_index + 1, new_node);
    int index = pos - array.begin();
    array[parent].right = index;

    return index;
}

template <typename T>
int BTree<T>::insert(T value)
{
    int insert_height = 100;
    int insert_index = -1;

    // if tree is empty, create a new root node
    if (root == -1)
    {
        Node<T> root_node(value, insert_height);
        auto pos = array.insert(array.begin(), root_node);
        int index = pos - array.begin();
        root = index;
        insert_index = index;
    }
    // if tree is not empty, follow normal insertion
    else
    {
        int current = root;
        while (true)
        {
            array[current].childCount++;

            // if the value is less than the current node's data, go left
            if (value < array[current].data)
            {
                int parent = current;
                current = array[current].left;

                // if the left child is empty, insert the new node here
                if (current == -1)
                {
                    int index = left_insert(value, parent, current);
                    insert_height = array[index].height;
                    insert_index = index;
                    break;
                }
                // if the left child is empty, insert the new node here
                else if (array[current].parent == -1)
                {
                    array[current].data = value;
                    array[current].parent = parent;
                    insert_height = array[current].height;
                    insert_index = current;
                    break;
                }
            }
            // if the value is greater than or equal to the current node's data, go right
            else
            {
                int parent = current;
                current = array[current].right;

                // if the right child is empty, insert the new node here
                if (current == -1)
                {
                    int index = right_insert(value, parent, current);
                    insert_height = array[index].height;
                    insert_index = index;
                    break;
                }
                // if the right child is empty, insert the new node here
                else if (array[current].parent == -1)
                {
                    array[current].data = value;
                    array[current].parent = parent;
                    insert_height = array[current].height;
                    insert_index = current;
                    break;
                }
            }
        }
    }

    // if the height is even, pre-insert children for space efficiency
    if (insert_index != -1 && insert_height % 2 == 0)
    {
        Node<T> left(0, insert_height - 1);
        Node<T> right(0, insert_height - 1);

        auto left_pos = array.insert(array.begin() + insert_index + 1, left);
        array[insert_index].left = left_pos - array.begin();

        auto right_pos = array.insert(array.begin() + insert_index + 2, right);
        array[insert_index].right = right_pos - array.begin();

        cout << "insert children at index: " << array[insert_index].left << " and " << array[insert_index].right << endl;
    }

    if (leave_height > insert_height)
    {
        leave_height = insert_height;
    }

    cout << "Parent: " << array[insert_index].parent << endl;
    cout << "Left: " << array[insert_index].left << endl;
    cout << "Right: " << array[insert_index].right << endl;

    return insert_index; // return -1 if insertion fails
}

template <typename T>
void BTree<T>::remove(T value)
{
    int index = search(value);
    if (index == -1)
    {
        cout << "Value not found in the tree." << endl;
        return;
    }
    else
    {
        int current = index;
        while (current != -1)
        {
            // This means both children is valid
            if (array[current].left != -1 && array[current].right != -1)
            {
                if(array[array[current].left].childCount > array[array[current].right].childCount)
                {
                    array[current].data = array[array[current].left].data;
                    current = array[current].left;
                }
                else
                {
                    array[current].data = array[array[current].right].data;
                    current = array[current].right;
                }
            }
            else if (array[current].left == -1 && array[current].right != -1)
            {
                array[current].data = array[array[current].right].data;
                current = array[current].right;
            }
            else if (array[current].left != -1 && array[current].right == -1)
            {
                array[current].data = array[array[current].left].data;
                current = array[current].left;
            }
            else
            {
                array[current].data = 0;
                array[current].parent = -1;
                break;
            }
        }
    }
}

// This function will return the index of element if found, otherwise -1
template <typename T>
int BTree<T>::search(T value)
{
    int current = root;
    while (current != -1)
    {
        if (array[current].data == value)
        {
            return current;
        }
        else if (value < array[current].data)
        {
            current = array[current].left;
        }
        else
        {
            current = array[current].right;
        }
    }

    return -1;
}

template <typename T>
void BTree<T>::print_array()
{
    cout << "Array: ";
    for (int i = 0; i < array.size(); ++i)
    {
        cout << array[i].data << " ";
    }
    cout << endl;
}

template <typename T>
void BTree<T>::print_tree()
{
    vector<int> parents;
    vector<int> children;
    if (root != -1)
    {
        cout << "Root:      ";
        for (int i = 0; i < 100 - leave_height; ++i)
        {
            cout << "    ";
        }
        cout << setw(4) << array[root].data << endl;
        parents.push_back(root);
        if (array[parents[0]].left != -1)
        {
            children.push_back(array[parents[0]].left);
        }
        if (array[parents[0]].right != -1)
        {
            children.push_back(array[parents[0]].right);
        }
    }
    else
    {
        cout << "Tree is empty." << endl;
    }

    int level = 1;
    while (!children.empty())
    {
        cout << "Level " << level << ": ";
        for (int i = 0; i < array[children[0]].height - leave_height; ++i)
        {
            cout << "    ";
        }

        for (int i = 0; i < children.size(); ++i)
        {
            cout << setw(4) << array[children[i]].data;
            for (int j = 0; j < array[children[i]].height - leave_height; ++j)
            {
                cout << "  ";
            }
        }
        cout << endl;

        parents = children;
        children.clear();
        for (int i = 0; i < parents.size(); ++i)
        {
            if (array[parents[i]].left != -1)
            {
                children.push_back(array[parents[i]].left);
            }
            if (array[parents[i]].right != -1)
            {
                children.push_back(array[parents[i]].right);
            }
        }
        level += 1;
    }
}

template <typename T>
BTree<T>::Iterator::Iterator() : index(0) {}

template <typename T>
bool BTree<T>::Iterator::hasNext()
{
    return index < array.getSize();
}

template <typename T>
int BTree<T>::Iterator::operator++()
{
    return ++index;
}

template <typename T>
T BTree<T>::Iterator::operator[](int index)
{
    return array[index];
}