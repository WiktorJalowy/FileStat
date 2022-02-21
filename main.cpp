#include <filesystem>
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Niepoprawna ilosc argumentow!" << std::endl;
        return -1;
    }

    try
    {
        std::filesystem::current_path(argv[1]);
    }
    catch (std::exception e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }
    int numOfFiles = 0;
    for (const auto &dir_entry : std::filesystem::recursive_directory_iterator("."))
    {
        if (dir_entry.is_regular_file())
        {
            numOfFiles++;
        }
    }
    std::cout << numOfFiles << std::endl;
    return 0;
}
