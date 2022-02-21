#include <gtest/gtest.h>

#include "lib/FileWatcher.hpp"
namespace
{
    const std::string testDirectory = "FileWatcherTestDirectory";
    const std::string nonExistingDummyPath = "asdfsf";
    const std::string testADirectory = "testA";
    const std::string testBDirectory = "/testB";
    const std::string dummyFileName = "/dummy.txt";
    const std::string dummyFileContentWithTwoEmptyAnd3NonEmptyLines = "\nFirst\nSecond\n\nThird";
    const std::string fileWatcherTestDummyDirectories = testADirectory + testBDirectory;
}

class FileWatcherFixture : public ::testing::Test
{
public:
    FileWatcherFixture()
    {
        fw.SetPath(std::filesystem::temp_directory_path());
        std::filesystem::current_path(std::filesystem::temp_directory_path());
        std::filesystem::create_directory(testDirectory);
        std::filesystem::current_path(std::filesystem::temp_directory_path().append(testDirectory));
    }
    ~FileWatcherFixture()
    {
        std::filesystem::remove_all(std::filesystem::temp_directory_path().append(testDirectory));
    }
    FileWatcher fw;
};

TEST_F(FileWatcherFixture, ShouldThrowWhenPathDoesNotExist)
{
    ASSERT_THROW(fw.SetPath(nonExistingDummyPath), std::exception);
}

TEST_F(FileWatcherFixture, ShouldReturnZeroFilesZeroLinesZeroEmptyLinesWhenGivenFolderIsEmpty)
{
    const auto result = fw.GetStats();
    EXPECT_EQ(0, std::get<0>(result));
    EXPECT_EQ(0, std::get<1>(result));
    EXPECT_EQ(0, std::get<2>(result));
}

TEST_F(FileWatcherFixture, ShouldReturnOneFilesZeroLinesZeroEmptyLines)
{
    std::ofstream("asdfsf");

    const auto result = fw.GetStats();
    EXPECT_EQ(1, std::get<0>(result));
    EXPECT_EQ(0, std::get<1>(result));
    EXPECT_EQ(0, std::get<2>(result));
}

TEST_F(FileWatcherFixture, ShouldReturnCorrectAmountOfFilesAndLines)
{
    std::filesystem::create_directories(fileWatcherTestDummyDirectories);
    std::ofstream file;
    file.open(testADirectory + dummyFileName);
    file << dummyFileContentWithTwoEmptyAnd3NonEmptyLines;
    file.close();

    file.open(testADirectory + testBDirectory + dummyFileName);
    file << dummyFileContentWithTwoEmptyAnd3NonEmptyLines;
    file.close();

    const auto result = fw.GetStats();
    EXPECT_EQ(2, std::get<0>(result)); // numOfFiles
    EXPECT_EQ(6, std::get<1>(result)); // numOfNonEmptyLines
    EXPECT_EQ(4, std::get<2>(result)); // numOfEmptyLines
}
