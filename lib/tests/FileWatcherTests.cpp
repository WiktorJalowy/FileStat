#include <gtest/gtest.h>

#include "lib/FileWatcher.hpp"

TEST(FileWatcher, ShouldNotThrowWhenPathExists)
{
    ASSERT_NO_THROW(FileWatcher(std::filesystem::temp_directory_path()));
}

TEST(FileWatcher, ShouldThrowWhenPathDoesNotExist)
{
    const std::string nonExistingDummyPath = "asdfsf";
    ASSERT_THROW(FileWatcher{nonExistingDummyPath}, std::exception);
}

TEST(FileWatcher, ShouldReturnZeroFilesZeroLinesZeroEmptyLinesWhenGivenFolderIsEmpty)
{
    std::filesystem::current_path(std::filesystem::temp_directory_path());
    std::filesystem::create_directory("FileWatcherTestFolder");

    FileWatcher fw(std::filesystem::temp_directory_path().append("FileWatcherTestFolder"));
    EXPECT_EQ(0, std::get<0>(fw.GetStats()));
    EXPECT_EQ(0, std::get<1>(fw.GetStats()));
    EXPECT_EQ(0, std::get<2>(fw.GetStats()));
    std::filesystem::remove_all(std::filesystem::temp_directory_path().append("FileWatcherTestFolder"));
}

TEST(FileWatcher, ShouldReturnOneFilesZeroLinesZeroEmptyLines)
{
    std::filesystem::current_path(std::filesystem::temp_directory_path());
    std::filesystem::create_directory("FileWatcherTestFolder");
    std::filesystem::current_path(std::filesystem::temp_directory_path().append("FileWatcherTestFolder"));

    std::ofstream("asdfsf");
    FileWatcher fw(std::filesystem::current_path());
    EXPECT_EQ(1, std::get<0>(fw.GetStats()));
    EXPECT_EQ(0, std::get<1>(fw.GetStats()));
    EXPECT_EQ(0, std::get<2>(fw.GetStats()));
    std::filesystem::remove_all(std::filesystem::temp_directory_path().append("FileWatcherTestFolder"));
}

TEST(FileWatcher, ShouldReturnCorrectAmountOfFilesAndLines)
{
    std::filesystem::current_path(std::filesystem::temp_directory_path());
    std::filesystem::create_directories("FileWatcherTestFolder/testA/b");
    std::ofstream file;
    file.open("FileWatcherTestFolder/testA/file.txt");
    file << "FirstLine\n\nSecond";
    file.close();

    file.open("FileWatcherTestFolder/testA/b/file.txt");
    file << "FirstLine\n\nSecond";
    file.close();

    FileWatcher fw(std::filesystem::temp_directory_path().append("FileWatcherTestFolder"));
    EXPECT_EQ(2, std::get<0>(fw.GetStats())); // numOfFiles
    EXPECT_EQ(4, std::get<1>(fw.GetStats())); // numOfNonEmptyLines
    EXPECT_EQ(2, std::get<2>(fw.GetStats())); // numOfEmptyLines
    std::filesystem::remove_all(std::filesystem::temp_directory_path().append("FileWatcherTestFolder"));
}
