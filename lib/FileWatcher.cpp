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
    return std::tuple<int, int, int>{};
}

