#include <iostream>
#include <random>
#include <vector>
#include <sstream>
#include <chrono>
#include <functional>

#include "sorting.hpp"

std::string display_vec(std::vector<int> vec){
    std::stringstream ss;
    ss << "{ ";
    for (int i = 0; i < vec.size(); i++)
        ss << vec[i] << " ";
    ss << "}";
    return ss.str();
}

void sort(std::function<void (std::vector<int>&)> sort_algo, int size = 10'000){
    std::vector<int> nums;
    for (int i = 0; i < size; i++)
        nums.push_back(rand() % 50);
    auto t1 = std::chrono::high_resolution_clock::now();
    sort_algo(nums);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    std::cout << "\tSorted " << size << " items in " << duration_ms.count() << "ms" << std::endl;
}

int main(int argc, char** argv){  
    std::srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::cout << "Bubble Sort:" << std::endl;
    sort(bubble_sort, 50000);
    std::cout << "Selection Sort:" << std::endl;
    sort(selection_sort, 50000);
    std::cout << "Insertion Sort:" << std::endl; 
    sort(insertion_sort, 50000);
    std::cout << "Quicksort:" << std::endl;
    sort(quicksort, 100'000);
    return 0;
}