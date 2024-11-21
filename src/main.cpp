#include <iostream>
#include <random>
#include <vector>
#include <sstream>
#include <chrono>
#include <functional>

#include "sorting.hpp"


// returns the first index out of order if the vector is not sorted or -1 if it is
int is_sorted(std::vector<int> vec){
    int prev = vec[0];
    for (int i = 1; i < vec.size(); i++){
        if (prev > vec[i])
            return i;
        prev = vec[i];
    }
    return -1;
}

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
    // ensure the algorithm was functional before displaying the benchemark
    int sorted = is_sorted(nums);
    if (sorted == -1)
        std::cout << "\tSorted " << size << " items in " << duration_ms.count() << "ms" << std::endl;
    else
        std::cout << "Sort failed at index " << sorted << std::endl;

}

int main(int argc, char** argv){  
    std::srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::cout << "Bubble Sort:" << std::endl;
    sort(bubble_sort, 50'000);
    std::cout << "Selection Sort:" << std::endl;
    sort(selection_sort, 50'000);
    std::cout << "Insertion Sort:" << std::endl; 
    sort(insertion_sort, 50'000);
    std::cout << "Quicksort (singlethreaded):" << std::endl;
    sort(quicksort, 500'000);
    return 0;
}
