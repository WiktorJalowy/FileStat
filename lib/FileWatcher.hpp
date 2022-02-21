#pragma once

#include <string>
#include <fstream>
#include <filesystem>

class FileWatcher
{
public:
    FileWatcher(const std::string &path);
    std::tuple<int, int, int> GetStats();

private:
    void UpdateStats();

    int numOfFiles = 0;
    int numOfNonEmptyLines = 0;
    int numOfEmptyLines = 0;
};
