#include "lib/FileWatcher.hpp"
#include <iostream>
#include <chrono>

int main(int argc, char **argv)
{
    auto start = std::chrono::system_clock::now();

    FileWatcher fw;
    try
    {
        fw.SetPath(argv[1]);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::tuple<int, int, int> results = fw.GetStats();
    std::cout << "Number of Files:\t\t" << std::get<0>(results) << std::endl;
    std::cout << "Number of NonEmpty lines:\t" << std::get<1>(results) << std::endl;
    std::cout << "Number of Empty lines:\t\t" << std::get<2>(results) << std::endl;

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = end-start;
    std::cout << "Calculations took: " << elapsedSeconds.count() << "s" << std::endl;

    return 0;
}
    // Some computation here

