#include "BTree.h"
#include <iostream>
#include <fstream>

int main()
{
    BTree<int> tree;

    std::ofstream file("output.csv");
    if (!file.is_open()) {
        std::cerr << "Failed to open the file!" << std::endl;
        return 1;
    }

    file << "elements,height\n";

    for(int i = 0; i < 200000; ++i)
    {
        tree.insert(rand());

        if((i % 100) == 0)
        {
            file << i << "," << tree.get_height() << "\n";
            cout << "Insert " << i << " elements, height: " << tree.get_height() << endl;
        }
    }

    file.close();
    return 0;
}