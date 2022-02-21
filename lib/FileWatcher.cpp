#include "lib/FileWatcher.hpp"

FileWatcher::FileWatcher(std::string path)
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
