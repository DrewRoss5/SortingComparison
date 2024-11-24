#ifndef SORTING_H
#define SORTING_H

#include <vector>
#include <functional>

void swap(int&, int&);
void bubble_sort(std::vector<int>&);
void selection_sort(std::vector<int>&);
void insertion_sort(std::vector<int>&);
void quicksort(std::vector<int>&);
void bucket_sort(std::vector<int>&, std::function<void(int, int)>);
void quicksort_multithreaded(std::vector<int>&);



#endif