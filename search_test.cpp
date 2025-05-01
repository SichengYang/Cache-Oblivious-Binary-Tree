#include "PMATree.h"
#include <iostream>
#include <fstream>
#include <chrono>

int main()
{
    PMATree<int> tree;

    std::ofstream file("search_output.csv");
    if (!file.is_open())
    {
        std::cerr << "Failed to open the file!" << std::endl;
        return 1;
    }

    file << "elements,time\n";
    double time_count = 0;
    for (int i = 0; i < 10000; ++i)
    {
        tree.insert(rand());

        auto start = std::chrono::high_resolution_clock::now();
        tree.search(rand());
        auto end = std::chrono::high_resolution_clock::now();
        double duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        time_count += duration;

        if ((i % 100) == 0)
        {
            double average_time = time_count / 100;
            file << i << "," << average_time << "\n";
            cout << "Search with " << i << " elements, time: " << average_time << endl;
            time_count = 0;
        }
    }

    file.close();
    return 0;
}