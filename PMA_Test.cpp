#include "PackMemoryArray.h"
#include <iostream>
#include <fstream>

int main()
{
    PackMemoryArray<int> pma(16);
    //Check Insert
    bool error_found = false;
    for (int i = 0; i < 30; i++)
    {
        //cout << "!!! insert: " << 2 * i << endl;
        if (pma.insert(3 * i) == false)
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
            if (pma.insert(3 * i+1) == false)
            {
                pma.printPMA();
                error_found = true;
                break;
            };
        }
    }
    if (error_found != true)
    {
        pma.printPMA();
        for (int i = 0; i < 30; i++)
        {
            // cout<<"!!! insert: "<<i+1<<endl;
            if (pma.insert(3 * i+2) == false)
            {
                pma.printPMA();
                error_found = true;
                break;
            };
        }
    }
    //Check []
    pma.printPMA();
    cout<<"pma[67] = "<<pma[67]<<endl;//should be 67
    cout<<"pma[8] = "<<pma[8]<<endl; //should be 8
    cout<<"pma[91] = "<<pma[91]<<endl; //should be -1 (DNE)
    cout<<"pma[101] = "<<pma[101]<<endl; //should be -1 (DNE)
    //Validation Check for insert
    bool insert_valid=true;
    for(int i=0;i<90;i++){
        if(pma[i]!=i){
            cout<<"Error Found! at i = "<<i<<" with pma[]="<<pma[i]<<endl;
            insert_valid==false;
            break;
        }
    }
    if(insert_valid){
        cout<<"Insert Valid check"<<endl;
    }
    //Check search, output the actual position
    cout<<"Search for 10: "<<pma.search(10)<<endl;
    cout<<"Search for 1: "<<pma.search(1)<<endl;
    cout<<"Search for 53: "<<pma.search(53)<<endl;
    cout<<"Search for 101: "<<pma.search(101)<<endl;
    cout<<"Search for 83: "<<pma.search(83)<<endl;
    cout<<"Search for 99: "<<pma.search(99)<<endl;
    //Check Remove
    cout<<"After Remove:"<<endl;
    pma.remove(10);
    pma.remove(1);
    pma.remove(53);
    pma.remove(83);
    cout<<"Search for 10: "<<pma.search(10)<<endl;
    cout<<"Search for 1: "<<pma.search(1)<<endl;
    cout<<"Search for 53: "<<pma.search(53)<<endl;
    cout<<"Search for 83: "<<pma.search(83)<<endl;
    pma.printPMA();
    return 0;
}