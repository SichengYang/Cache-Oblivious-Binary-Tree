#include "PackMemoryArray.h"
#include <iostream>
#include <fstream>


int main()
{
    PackMemoryArray<int> pma(16);

    std::ofstream file("output.csv");
    if (!file.is_open()) {
        std::cerr << "Failed to open the file!" << std::endl;
        return 1;
    }

    file << "elements,height\n";
    //pma.printPMA();
    for(int i=0;i<18;i++){
        //cout<<"!!! insert: "<<2*i<<endl;
        pma.insert(2*i);
    }
    for(int i=0;i<18;i++){
        //cout<<"!!! insert: "<<i+1<<endl;
        pma.insert(2*i+1);
    }
    pma.printPMA();
    pma.insert(36);
    pma.printPMA();
    //pma.printPMA();
    // for(int i = 0; i < 200000; ++i)
    // {
    //     pma.add(1);

    //     if((i % 100) == 0)
    //     {
    //         file << i << "," << tree.get_height() << "\n";
    //         cout << "Insert " << i << " elements, height: " << tree.get_height() << endl;
    //     }
    // }

    file.close();
    return 0;
}