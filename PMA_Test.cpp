#include "PackMemoryArray.h"
#include <iostream>
#include <fstream>

int main()
{
    PackMemoryArray<int> pma(16);

    std::ofstream file("output.csv");
    if (!file.is_open())
    {
        std::cerr << "Failed to open the file!" << std::endl;
        return 1;
    }

    file << "elements,height\n";
    // pma.printPMA();
    bool error_found = false;
    for (int i = 0; i < 30; i++)
    {
        //cout << "!!! insert: " << 2 * i << endl;
        if (pma.insert(2 * i) == false)
        {
            pma.printPMA();
            error_found = true;
            break;
        };
    }
    if (error_found != true)
    {
        pma.printPMA();
        for (int i = 0; i < 30; i++)
        {
            // cout<<"!!! insert: "<<i+1<<endl;
            if (pma.insert(2 * i+1) == false)
            {
                pma.printPMA();
                error_found = true;
                break;
            };
        }
    }
    pma.printPMA();

    file.close();
    return 0;
}