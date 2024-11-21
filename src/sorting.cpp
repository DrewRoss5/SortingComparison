#include <iostream>
#include <vector>
#include <limits>

#include "sorting.hpp"

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

void quicksort(std::vector<int>& arr){
    pivot_arr(arr, 0, arr.size());
}