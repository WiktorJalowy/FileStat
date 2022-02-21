#include "lib/FileWatcher.hpp"

FileWatcher::FileWatcher(const std::string &path)
{
    try
    {
        std::filesystem::current_path(path);
    }
    catch (...)
    {
        throw;
    }
}

std::tuple<int, int, int> FileWatcher::GetStats()
{
    numOfFiles = 0;
    numOfNonEmptyLines = 0;
    numOfEmptyLines = 0;
    UpdateStats();
    return std::make_tuple(numOfFiles, numOfNonEmptyLines, numOfEmptyLines);
}

void FileWatcher::UpdateStats()
{
    for (const auto &dir_entry : std::filesystem::recursive_directory_iterator("."))
    {
        if (dir_entry.is_regular_file())
        {
            numOfFiles++;
            std::ifstream file(dir_entry.path().c_str());
            std::string line;
            while (std::getline(file, line))
            {
                if (line.length() == 0)
                {
                    numOfEmptyLines++;
                }
                else
                {
                    numOfNonEmptyLines++;
                }
            }
        }
    }
}
