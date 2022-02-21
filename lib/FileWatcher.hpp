#pragma once

#include <string>
#include <fstream>
#include <filesystem>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>

class FileWatcher
{
public:
    std::tuple<int, int, int> GetStats();
    void SetPath(std::filesystem::path path);

private:
    void UpdateStats();
    void ClearStats();
    void UpdateLineStats(const std::filesystem::directory_entry &dir_entry);
    void WaitForTasks();

    std::vector<std::thread> threads;
    int numOfFiles = 0;
    std::atomic<int> numOfNonEmptyLines = 0;
    std::atomic<int> numOfEmptyLines = 0;
};
