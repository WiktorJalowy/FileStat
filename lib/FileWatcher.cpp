#include "lib/FileWatcher.hpp"

FileWatcher::FileWatcher(std::filesystem::path path)
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
    ClearStats();
    UpdateStats();
    WaitForTasks();
    return std::make_tuple(numOfFiles, numOfNonEmptyLines.load(), numOfEmptyLines.load());
}

void FileWatcher::WaitForTasks()
{
    for (unsigned i = 0; i < threads.size(); i++)
    {
        threads[i].join();
    }
}

void FileWatcher::ClearStats()
{
    numOfFiles = 0;
    numOfNonEmptyLines = 0;
    numOfEmptyLines = 0;
}

void FileWatcher::UpdateLineStats(const std::filesystem::directory_entry &dir_entry)
{
    std::ifstream file(dir_entry.path());
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
void FileWatcher::UpdateStats()
{
    for (const auto &dir_entry : std::filesystem::recursive_directory_iterator("."))
    {
        if (dir_entry.is_regular_file())
        {
            numOfFiles++;
            threads.push_back(std::thread(
                [this, dir_entry]()
                {
                    UpdateLineStats(dir_entry);
                }
            ));
        }
    }
}
