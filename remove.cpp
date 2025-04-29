#include "BTree.h"
#include <iostream>
#include <fstream>
#include <chrono>

int main()
{
    BTree<int> tree;

    std::ofstream file("remove_output.csv");
    if (!file.is_open())
    {
        std::cerr << "Failed to open the file!" << std::endl;
        return 1;
    }

    file << "elements,time\n";
    double time_count = 0;
    for (int i = 0; i < 200001; ++i)
    {
        int rand1 = std::rand();
        int rand2 = std::rand();
        tree.insert(rand1);
        tree.insert(rand2);
        
        auto start = std::chrono::high_resolution_clock::now();
        tree.remove(rand2);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        time_count += duration;
        
        if( i % 1000 == 0)
        {
            file << i << "," << time_count / 1000 << "\n";
            std::cout << "delete with " << i << " elements, time: " << time_count / 1000 << " microseconds" << std::endl;
            time_count = 0;
        }
    }

    file.close();
    return 0;
}