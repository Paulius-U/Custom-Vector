#include <iostream>
#include <chrono>
#include <vector>
#include "vector.h"

int main()
{ 
    int reallocated_v1 = 0, reallocated_v2 = 0, capacity_v1, capacity_v2;
    bool Did_reallocated_v1 = false, Did_reallocated_v2 = false;
    unsigned int sz = 10000;  // 10000 100000, 1000000, 10000000, 100000000
    auto Start = std::chrono::high_resolution_clock::now();
    std::vector<int> v1;
    for (int i = 1; i <= sz; ++i)
    {
        if(v1.size() == v1.capacity())
        {
            reallocated_v1++;
            Did_reallocated_v1 = true;
        }
        v1.push_back(i);
        if(Did_reallocated_v1)
        {
            capacity_v1 = v1.capacity();
            Did_reallocated_v1 = false;
        }
    }
    auto End = std::chrono::high_resolution_clock::now();
    std::cout << "std::vector:  " << std::chrono::duration_cast<std::chrono::milliseconds>(End - Start).count() / 1000.<< " s."<< std::endl;
    std::cout << "std::vector reallocated: " << reallocated_v1 << " times\n";
    std::cout << "std::vector reached capacity: " << capacity_v1 << "\n\n";

    auto Start0 = std::chrono::high_resolution_clock::now();
    vector<int> v2;
    for (int i = 1; i <= sz; ++i)
    {
        if(v2.size() == v2.capacity())
        {
            reallocated_v2++;
            Did_reallocated_v2 = true;
        }
        v2.push_back(i);
        if(Did_reallocated_v2)
        {
            capacity_v2 = v2.capacity();
            Did_reallocated_v2 = false;
        }
    }
    auto End0 = std::chrono::high_resolution_clock::now();
    std::cout << "Custom Vector: " << std::chrono::duration_cast<std::chrono::milliseconds>(End0 - Start0).count() / 1000.<< " s."<< std::endl;
    std::cout << "custom vector reallocated: " << reallocated_v2 << " times\n";
    std::cout << "custom vector reached capacity: " << capacity_v2 << "\n\n";
    return 0;
}