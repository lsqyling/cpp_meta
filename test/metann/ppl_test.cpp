//
// Created by 10580.
//
// parallel-fibonacci.cpp
// compile with: /EHsc
#include <windows.h>
#include <ppl.h>
#include <concurrent_vector.h>
#include <array>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>


// Calls the provided work function and returns the number of milliseconds
// that it takes to call that function.
template<class Function>
int64_t time_call(Function &&f)
{
    int64_t begin = GetTickCount();
    f();
    return GetTickCount() - begin;
}

// Computes the nth Fibonacci number.
int fibonacci(int n)
{
    if (n < 2)
        return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(int argc, char *argv[])
{
    int64_t elapsed;

    // An array of Fibonacci numbers to compute.
    std::array<int, 4> a = {24, 26, 41, 42};

    // The results of the serial computation.
    std::vector<std::tuple<int, int>> results1;

    // The results of the parallel computation.
    concurrency::concurrent_vector<std::tuple<int, int>> results2;

    // Use the for_each algorithm to compute the results serially.
    elapsed = time_call([&] {
        for_each(begin(a), end(a), [&](int n) {
            results1.push_back(std::make_tuple(n, fibonacci(n)));
        });
    });
    std::wcout << L"serial time: " << elapsed << L" ms" << std::endl;

    // Use the parallel_for_each algorithm to perform the same task.
    elapsed = time_call([&] {
        concurrency::parallel_for_each(std::begin(a), std::end(a), [&](int n) {
            results2.push_back(std::make_tuple(n, fibonacci(n)));
        });

        // Because parallel_for_each acts concurrently, the results do not
        // have a pre-determined order. Sort the concurrent_vector object
        // so that the results match the serial version.
        sort(begin(results2), end(results2));
    });
    std::wcout << L"parallel time: " << elapsed << L" ms" << std::endl << std::endl;

    // Print the results.
    std::for_each(std::begin(results2), std::end(results2), [](std::tuple<int, int> &pair) {
        std::wcout << L"fib(" << std::get<0>(pair) << L"): " << std::get<1>(pair) << std::endl;
    });
}


