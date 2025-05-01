#include "PMATree.h"

// debug and printing purpose
using namespace std;
#include <iostream>
#include <iomanip>

template <typename T>
PMATree<T>::PMATree() : root(-1), leave_height(100) {}

template <typename T>
PMATree<T>::~PMATree() {}

// Balance the node by checking differene between left and right child. According to the paper, the difference between the left and right should be within the factor of 4 (for binary tree, we choose d = 2).
template <typename T>
void PMATree<T>::rebalance_helper(int index)
{
    // if it is a leaf node, do nothing
    if (array[index].childCount <= 1)
    {
        return;
    }

    // if the left or right is empty and the parent has more than 2 children, this is not a balanced node
    // this case is specially treated to avoid divition by zero
    if (!is_valid_node(array[index].left))
    {
        int balance_count = (array[array[index].right].childCount + 1) / 2;
        for (int i = 0; i < balance_count; i++)
        {
            int data = array[index].data;
            remove_helper(data);
            insert_helper(data);
        }
        return;
    }
    else if (!is_valid_node(array[index].right))
    {
        int balance_count = (array[array[index].left].childCount + 1) / 2;
        for (int i = 0; i < balance_count; i++)
        {
            int data = array[index].data;
            remove_helper(data);
            insert_helper(data);
        }
        return;
    }

    int left_child = array[array[index].left].childCount + 1;
    int right_child = array[array[index].right].childCount + 1;
    int average = array[index].childCount / 2;
    if (left_child > right_child * 4 || left_child * 4 < right_child)
    {
        int balance_count = 0;
        if (left_child > right_child)
        {
            balance_count = left_child - average;
        }
        else
        {
            balance_count = right_child - average;
        }

        for (int i = 0; i < balance_count; i++)
        {
            int data = array[index].data;
            remove_helper(data);
            insert_helper(data);
        }
    }

    if (array[index].left != -1)
        rebalance_helper(array[index].left);
    if (array[index].right != -1)
        rebalance_helper(array[index].right);
}

template <typename T>
void PMATree<T>::rebalance(int index)
{
    if (index == -1)
    {
        return;
    }

    int current = index;
    bool need_rebalance = false;
    while (current != root)
    {
        int parent = array[current].parent;

        if (!is_valid_node(array[parent].left) && array[array[parent].right].childCount >= 1)
        {
            current = parent;
            need_rebalance = true;
            break;
        }

        if (!is_valid_node(array[parent].right) && array[array[parent].left].childCount >= 1)
        {
            current = parent;
            need_rebalance = true;
            break;
        }

        int left_count = array[array[parent].left].childCount + 1;
        int right_count = array[array[parent].right].childCount + 1;
        if (left_count > right_count * 4 || left_count * 4 < right_count)
        {
            current = parent;
            need_rebalance = true;
            break;
        }

        current = parent;
    }

    if (need_rebalance)
        rebalance_helper(current);
}

template <typename T>
void PMATree<T>::shift_right(int index, int right_index)
{
    int start = array[array[array[index].parent].parent].left;
    // shift all elements to the right by 3 elements
    for (int i = 0; i < array.getNcount(); i += 1)
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
int PMATree<T>::left_insert(T value, int parent, int current)
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
    int index = array.insert(insert_after_index + 1, new_node);
    array[parent].left = index;

    return index;
}

template <typename T>
int PMATree<T>::right_insert(T value, int parent, int current)
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
    int index = array.insert(insert_after_index + 1, new_node);
    array[parent].right = index;

    return index;
}

template <typename T>
bool PMATree<T>::is_valid_node(int index)
{
    return index != -1 && array[index].parent != -1;
}

template <typename T>
bool PMATree<T>::is_leaf_node(int index)
{
    return (array[index].left == -1 || array[array[index].left].parent == -1) && (array[index].right == -1 || array[array[index].right].parent == -1);
}

template <typename T>
int PMATree<T>::insert_helper(T value)
{
    int insert_height = 100;
    int insert_index = -1;

    // if tree is empty, create a new root node
    if (root == -1)
    {
        Node<T> root_node(value, insert_height);
        array[0] = root_node;
        root = 0;
        insert_index = 0;
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
    if (insert_index != -1 && insert_height % 2 == 0 && array[insert_index].left == -1 && array[insert_index].right == -1)
    {
        Node<T> left(0, insert_height - 1);
        Node<T> right(0, insert_height - 1);

        array[insert_index].left = array.insert(insert_index + 1, left);

        array[insert_index].right = array.insert(insert_index + 2, right);
    }

    if (leave_height > insert_height)
    {
        leave_height = insert_height;
    }

    return insert_index;
}

template <typename T>
int PMATree<T>::remove_helper(T value)
{
    if (search(value) == -1)
    {
        return -1;
    }

    int index = -1;
    int return_index = -1;
    int current = root;

    while (current != -1)
    {
        if (array[current].data == value)
        {
            return_index = array[current].parent;
            index = current;
            break;
        }
        else if (value < array[current].data)
        {
            if (array[current].childCount > 0)
            {
                array[current].childCount--;
            }
            current = array[current].left;
        }
        else
        {
            if (array[current].childCount > 0)
            {
                array[current].childCount--;
            }
            current = array[current].right;
        }
    }

    // if it is leaf, just delete it.
    if (is_leaf_node(index))
    {
        array[index].data = -1;
        array[index].parent = -1;
        return return_index;
    }

    // find a value between left and right child and replace the current node with it, we prioritize the the branch
    // with more children so that we can save memory transfer in potential rebalance
    int left_count = is_valid_node(array[index].left) ? array[array[index].left].childCount : 0;
    int right_count = is_valid_node(array[index].right) ? array[array[index].right].childCount : 0;
    bool has_leaf = false;
    int replace_index = index;
    if (left_count > right_count) // find a node from left branch
    {
        while (replace_index != -1)
        {
            if (array[replace_index].childCount > 0)
            {
                array[replace_index].childCount--;
            }

            if (!is_valid_node(array[replace_index].left))
            {
                array[replace_index].parent = -1;
                array[replace_index].data = -1;
                break;
            }
            else
            {
                array[replace_index].data = array[array[replace_index].left].data;
            }

            if (is_valid_node(array[array[replace_index].left].right))
            {
                has_leaf = true;
                array[array[replace_index].left].childCount--;
                replace_index = array[array[replace_index].left].right;
                break;
            }

            replace_index = array[replace_index].left;
            index = replace_index;
        }
    }
    else // find a node from right branch
    {
        while (replace_index != -1)
        {
            if (array[replace_index].childCount > 0)
            {
                array[replace_index].childCount--;
            }

            if (!is_valid_node(array[replace_index].right))
            {
                array[replace_index].parent = -1;
                array[replace_index].data = -1;
                break;
            }
            else
            {
                array[replace_index].data = array[array[replace_index].right].data;
            }

            if (is_valid_node(array[array[replace_index].right].left))
            {
                has_leaf = true;
                array[array[replace_index].right].childCount--;
                replace_index = array[array[replace_index].right].left;
                break;
            }

            replace_index = array[replace_index].right;
            index = replace_index;
        }
    }

    if (has_leaf)
    {
        while (replace_index != -1)
        {
            if (array[replace_index].childCount > 0)
            {
                array[replace_index].childCount--;
            }

            if (is_valid_node(array[replace_index].right) && is_valid_node(array[replace_index].left))
            {
                if (array[array[replace_index].right].childCount > array[array[replace_index].left].childCount)
                {
                    replace_index = array[replace_index].right;
                }
                else
                {
                    replace_index = array[replace_index].left;
                }
            }
            else if (is_valid_node(array[replace_index].right))
            {
                replace_index = array[replace_index].right;
            }
            else if (is_valid_node(array[replace_index].left))
            {
                replace_index = array[replace_index].left;
            }
            else
            {
                array[index].data = array[replace_index].data;
                array[replace_index].parent = -1;
                array[replace_index].data = -1;
                break;
            }
        }
    }

    return return_index;
}

// This function will return the index of element if found, otherwise -1
template <typename T>
int PMATree<T>::search(T value)
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
void PMATree<T>::print_array()
{
    cout << "Array: ";
    for (int i = 0; i < array.getNcount(); ++i)
    {
        cout << array[i].data << " ";
    }
    cout << endl;
}

template <typename T>
void PMATree<T>::print_tree()
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
        cout << setw(4) << array[root].data << "(" << array[root].height << ", " << array[root].childCount << ")" << endl;
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
            if (array[children[i]].parent != -1)
                cout << "(" << array[array[children[i]].parent].data << ", " << array[children[i]].height << ", " << array[children[i]].childCount << ")";
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
int PMATree<T>::insert(T value)
{
    int search_result = search(value);
    if(search_result != -1)
    {
        return search_result;
    }
    int index = insert_helper(value);
    rebalance(index);
    return search(value);
}

template <typename T>
void PMATree<T>::remove(T value)
{
    int index = remove_helper(value);
    if (index != -1)
        rebalance(index);
}

template <typename T>
int PMATree<T>::get_height()
{
    return 100 - leave_height;
}

template <typename T>
PMATree<T>::Iterator::Iterator() : index(0) {}

template <typename T>
bool PMATree<T>::Iterator::hasNext()
{
    return index < array.getNcount();
}

template <typename T>
int PMATree<T>::Iterator::operator++()
{
    return ++index;
}

template <typename T>
T PMATree<T>::Iterator::operator[](int index)
{
    return array[index];
}