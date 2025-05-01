#include "BTree.h"
#include <iostream>
#include <fstream>
#include <chrono>

int main()
{
    BTree<int> tree;

    std::ofstream file("insert_output.csv");
    if (!file.is_open()) {
        std::cerr << "Failed to open the file!" << std::endl;
        return 1;
    }

    file << "elements,time\n";

    double time_count = 0;
    for(int i = 0; i < 200001; ++i)
    {
        auto start = std::chrono::high_resolution_clock::now();

        tree.insert(rand());

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        time_count += duration;

        if((i % 1000) == 0)
        {
            file << i << "," << time_count / 1000 << "\n";
            cout << "Insert " << i << " elements, average time: " << time_count / 1000 << endl;
            time_count = 0;
        }
    }

    file.close();
    return 0;
}