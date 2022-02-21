#pragma once

#include <string>
#include <fstream>
#include <filesystem>
#include <thread>

class FileWatcher
{
public:
    FileWatcher(std::filesystem::path path);
    std::tuple<int, int, int> GetStats();

private:
    void UpdateStats();
    void ClearStats();
    void UpdateLineStats(const std::filesystem::directory_entry &dir_entry);

    int numOfFiles = 0;
    int numOfNonEmptyLines = 0;
    int numOfEmptyLines = 0;
};
