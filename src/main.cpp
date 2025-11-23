#include "../include/sorting.h"
#include <iostream>
#include <random>
#include <chrono>

void bubble_sort_wrapper(int *beg, int *end)
{
    IMD::bubble_sort(beg, end);
}

void Hoare_recursive_sort_wrapper(int *beg, int *end)
{
    IMD::Hoare_recursive_sort(beg, end);
}

void Hoare_iterative_sort_wrapper(int *beg, int *end)
{
    IMD::Hoare_iterative_sort(beg, end);
}

void Lomuto_recursive_sort_wrapper(int *beg, int *end)
{
    IMD::Lomuto_recursive_sort(beg, end);
}

void Lomuto_iterative_sort_wrapper(int *beg, int *end)
{
    IMD::Lomuto_iterative_sort(beg, end);
}

void Shell_sort_wrapper(int *beg, int *end)
{
    IMD::Shell_sort(beg, end);
}

void Shell_Knuth_sort_wrapper(int *beg, int *end)
{
    IMD::Shell_Knuth_sort(beg, end);
}

void insertion_sort_wrapper(int *beg, int *end)
{
    IMD::insertion_sort(beg, end);
}

void selection_sort_wrapper(int *beg, int *end)
{
    IMD::selection_sort(beg, end);
}

void comb_sort_wrapper(int *beg, int *end)
{
    IMD::comb_sort(beg, end);
}

void counting_sort_wrapper(int *beg, int *end)
{
    IMD::counting_sort(beg, end);
}

using sort_func = void (*)(int *, int *);

int *generate_random_array(size_t size, int min_val, int max_val)
{
    int *res = new int[size];

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min_val, max_val);

    for (size_t i{0}; i < size; ++i)
        res[i] = dist(gen);

    return res;
}

int *copy_array(const int *src, size_t size)
{
    int *dest = new int[size];
    for (size_t i{0}; i < size; ++i)
        dest[i] = src[i];

    return dest;
}

bool is_sorted(const int *arr, size_t size)
{
    for (size_t i{1}; i < size; ++i)
        if (arr[i] < arr[i - 1])
            return false;
    return true;
}

void test_sort(const std::string &alg_name, sort_func sf, int *arr, size_t size)
{
    int *tmp = copy_array(arr, size);

    auto start = std::chrono::high_resolution_clock::now();
    sf(tmp, tmp + size);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    bool sorted{is_sorted(tmp, size)};

    std::cout << alg_name << ": " << duration.count() << " microseconds, " << (sorted ? "sorted" : "not sorted!") << std::endl;

    delete[] tmp;
}

int main()
{
    const size_t AMOUNT{1'000'000};

    std::cout << "Performance comparison on an array of " << AMOUNT << " elements:" << std::endl;

    int *arr = generate_random_array(AMOUNT, -1'000'000, 1'000'000);
    test_sort("Hoare Iterative Sort", Hoare_recursive_sort_wrapper, arr, AMOUNT);
    test_sort("Hoare Recursive Sort", Hoare_recursive_sort_wrapper, arr, AMOUNT);

    test_sort("Lomuto Iterative Sort", Lomuto_iterative_sort_wrapper, arr, AMOUNT);
    test_sort("Lomuto Recursive Sort", Lomuto_recursive_sort_wrapper, arr, AMOUNT);

    test_sort("Bubble Sort", bubble_sort_wrapper, arr, AMOUNT);
    test_sort("Comb Sort", comb_sort_wrapper, arr, AMOUNT);
    test_sort("Insertion Sort", insertion_sort_wrapper, arr, AMOUNT);
    test_sort("Shell Sort", Shell_sort_wrapper, arr, AMOUNT);
    test_sort("Shell Knuth Sort", Shell_Knuth_sort_wrapper, arr, AMOUNT);
    test_sort("Selection Sort", selection_sort_wrapper, arr, AMOUNT);
    test_sort("Counting Sort", counting_sort_wrapper, arr, AMOUNT);

    delete[] arr;

    return 0;
}