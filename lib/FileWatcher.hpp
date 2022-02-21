#pragma once
#include <string>
#include <filesystem>

class FileWatcher
{
public:
    FileWatcher(const std::string &path);
    std::tuple<int, int, int> GetStats();
};
