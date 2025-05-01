#include "PackMemoryArray.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <time.h>
#include <chrono>
using namespace std;
void test_function(int initial_size, int test_size, ofstream& file){
    // Random number
    random_device rd;                         // obtain a random number from hardware
    mt19937 gen(rd());                        // seed the generator

    PackMemoryArray<int> pma(initial_size);
    // Check Insert
    vector<int> array;
    //Generate Random inputs
    vector<int> index_array;
    vector<int> value_array;
    //Debug mode
    bool print_array_pma=false;
    for (int i = 0; i < test_size; i++)
    {
        uniform_int_distribution<> distr1(0, i+1);
        index_array.push_back(distr1(gen));
        //index_array.push_back(i);
        uniform_int_distribution<> distr2(0, 100);
        value_array.push_back(distr2(gen));
        //value_array.push_back(i);
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
        //cout<<"i = "<<i<<" index_array[i]= "<<index_array[i]<<" value_array[i]="<< value_array[i]<<endl;
        //pma.printPMA();
        pma.insert(index_array[i], value_array[i]);
        
    }
    timer1=float( clock () - begin_time1 ) /  CLOCKS_PER_SEC;
    cout<<"Done for pma"<<endl;
    const clock_t begin_time2 = clock();
    for (int i = 0; i < test_size; i++)
    {
        array.insert(array.begin() + index_array[i], value_array[i]);
    }
    timer2=float( clock () - begin_time2 ) /  CLOCKS_PER_SEC;
    cout<<"Done for vector"<<endl;
    if(print_array_pma){
        pma.printPMA();
        cout << "Array:" << endl;
        for (auto i : array)
            cout << i << " ";
        cout << endl;
    }
    //Validation check
    bool found_error = false;
    for (int i = 0; i < test_size; i++)
    {
        if (pma[i] != array[i])
        {
            found_error = true;
            cout << "Error for " << i << " " << pma[i] << endl;
        }
    }
    if (found_error != true)
    {
        cout << "VALID! for test case size: " << test_size <<" Initial pma size:"<<initial_size<<endl;
        cout<< "Time: (pma) "<<timer1<<" (vector) "<<timer2<<endl;
        file<<test_size<<", "<<initial_size<< ", "<<timer1<<", "<<timer2;
    }
    else{
        file<<"Error:"<<test_size<<", "<<initial_size<< ", "<<timer1<<", "<<timer2;
    }
}


int main()
{
    //Export the result into file
    std::ofstream file("total insertion_outputPMA111.csv");
    if (!file.is_open())
    {
        std::cerr << "Failed to open the file!" << std::endl;
        return 1;
    }
    file << "elements,pma_size, pma_time, vector_time\n";
    int initial_size[7]= {1600,16000,32000};
    int test_size[8] = {80000,100000,120000,140000,160000,180000,200000};
    for(int i=0; i<7;i++){
        for(int j=0;j<7;j++){
            test_function(initial_size[i], test_size[j], file);
        }
    }

    return 0;
}