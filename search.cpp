#include "BTree.h"
#include <iostream>
#include <fstream>
#include <chrono>

int main()
{
    BTree<int> tree;

    std::ofstream file("search_output.csv");
    if (!file.is_open())
    {
        std::cerr << "Failed to open the file!" << std::endl;
        return 1;
    }

    file << "elements,time\n";
    for (int i = 0; i < 300001; ++i)
    {
        tree.insert(rand());

        if ((i % 1000) == 0)
        {
            auto start = std::chrono::high_resolution_clock::now();

            tree.search(rand());

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            
            file << i << "," << duration << "\n";
            cout << "Search with " << i << " elements, time: " << duration << endl;
        }
    }

    file.close();
    return 0;
}