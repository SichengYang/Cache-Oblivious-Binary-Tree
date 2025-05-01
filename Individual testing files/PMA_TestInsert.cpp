#include "PackMemoryArray.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <time.h>
#include <chrono>
using namespace std;
int main()
{
    //Search test
    std::ofstream file("insert_outputPMA.csv");
    if (!file.is_open())
    {
        std::cerr << "Failed to open the file!" << std::endl;
        return 1;
    }
    file << "elements,time\n";
    // Random number
    random_device rd;                         // obtain a random number from hardware
    mt19937 gen(rd());                        // seed the generator
    int initial_size=16000;
    PackMemoryArray<int> pma(initial_size);
    // Check Insert
    vector<int> array;
    int test_size = 500000;
    //Generate Random inputs
    vector<int> index_array;
    vector<int> value_array;
    //Debug mode
    bool print_array_pma=false;
    for (int i = 0; i < test_size; i++)
    {
        uniform_int_distribution<> distr1(0, i);
        index_array.push_back(distr1(gen));
        uniform_int_distribution<> distr2(0, 100);
        value_array.push_back(distr2(gen));
    }
    if(print_array_pma){
        for (auto i : index_array)
            cout << i << " ";
        cout<<endl;
        for (auto i : value_array)
            cout << i << " ";
        cout<<endl;
    }
    //Set up Timer
    float timer1=0;
    float timer2=0;
    pma.insert(0, 0);
    array.insert(array.begin(), 0);
    const clock_t begin_time1 = clock();
    for (int i = 0; i < test_size; i++)
    {
        if ((i % 5000) == 0)
        {
            uniform_int_distribution<> distr3(0, i);
            int temp_index=distr3(gen);
            auto start = std::chrono::high_resolution_clock::now();
            pma.insert(index_array[i], value_array[i]);

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            
            file << i << "," << duration << "\n";
            cout << "Insert with " << i << " elements, time: " << duration << endl;
        }
        else{
            pma.insert(index_array[i], value_array[i]);
        }


    }
    
    return 0;
}