#include <iostream>
#include <vector>
#include <limits>
#include <thread>

#include "sorting.hpp"


// this is a global vector to be used for multithreaded alogrithm
std::vector<int> parallel_vec;

void swap(int& a, int& b){
    int tmp = a;
    a = b;
    b = tmp;
}

void bubble_sort(std::vector<int>& arr){
    int len = arr.size();
    for (int i = 0; i < len; i++){
        for (int j = 1; j < len - i; j++){
            if (arr[j] < arr[j - 1])
                swap(arr[j], arr[j - 1]);
        }   
    }
}

void selection_sort(std::vector<int>& arr){
    int len = arr.size();
    for (int i = 0; i < len; i++){
        int min = std::numeric_limits<int>().max();
        int min_index = i;
        for (int j = i; j < len; j++){
            if (arr[j] < min){
                min_index = j;
                min = arr[j];
            }
        }
        swap(arr[min_index], arr[i]);
    }
}

void insertion_sort(std::vector<int>& arr){
    int len = arr.size();
    for (int i = 1; i < len; i++){
        int pivot_index = i;
        int tmp = arr[i];
        // scan to the left and push all values to the right until we find one that's less than the current
        for (int j = pivot_index - 1; ; j--){
            if (tmp < arr[j]){
                swap(arr[j], arr[j + 1]);
            }
            else{
                arr[j + 1] = tmp; 
                break;
            }
        }
    }
}

void pivot_arr(std::vector<int>& arr, int start, int end){
    if (end - start <= 1)
        return;
    int pivot = arr[start];
    int pivot_index = start;
    for (int i = start; i < end; i++){
        if (arr[i] < pivot){
            swap(arr[pivot_index], arr[pivot_index + 1]);
            swap(arr[pivot_index], arr[i]);
            pivot_index++;
        }
    }
    swap(arr[start], arr[pivot_index]);
    pivot_arr(arr, start, pivot_index);
    pivot_arr(arr, pivot_index+1, end);
}

void pivot_arr_multithread(int start, int end){
    if (end - start <= 1)
        return;
    int pivot = parallel_vec[start];
    int pivot_index = start;
    for (int i = start; i < end; i++){
        if (parallel_vec[i] < pivot){
            swap(parallel_vec[pivot_index], parallel_vec[pivot_index + 1]);
            swap(parallel_vec[pivot_index], parallel_vec[i]);
            pivot_index++;
        }
    }
    swap(parallel_vec[start], parallel_vec[pivot_index]);
    pivot_arr_multithread(start, pivot_index);
    pivot_arr_multithread(pivot_index+1, end);
}

void quicksort(std::vector<int>& arr){
    pivot_arr(arr, 0, arr.size());
}

// performs a simplified bucket sort using quicksort as the base
void quicksort_multithreaded(std::vector<int>& arr){
    parallel_vec = arr;
    unsigned thread_count = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    // split the array into segments and sort each
    std::vector<int> offsets;
    int segment_size = arr.size() / thread_count;
    for (int i = 0; i < thread_count; i++){
        int offset = segment_size * i;
        offsets.push_back(offset);
        threads.push_back(std::thread(&pivot_arr_multithread, offset, segment_size * (i + 1)));

    }
    for (int i = 0; i < thread_count; i++)
        threads[i].join();
    // combine the segments
    arr.clear();
    while (true){
        int min_offeset = 0;
        int min = std::numeric_limits<int>().max();
        bool break_loop = true;
        // find the minimum value
        for (int i = 0; i < thread_count; i++){
            if (offsets[i] < (segment_size * (i + 1))){
                break_loop = false;
                if (parallel_vec[offsets[i]] < min){
                    min = parallel_vec[offsets[i]];
                    min_offeset = i;
                }
            }
        }
        offsets[min_offeset]++;
        if (break_loop)
            break;
        else
            arr.push_back(min);
    }



}
