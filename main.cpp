#include <filesystem>
#include <fstream>
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
    int numOfLines = 0;
    for (const auto &dir_entry : std::filesystem::recursive_directory_iterator("."))
    {
        if (dir_entry.is_regular_file())
        {
            numOfFiles++;
            std::ifstream file(dir_entry.path().c_str());
            std::string line;
            while (std::getline(file, line))
            {
                numOfLines++;
            }
        }
    }
    std::cout << numOfFiles << std::endl;
    std::cout << numOfLines << std::endl;
    return 0;
}
