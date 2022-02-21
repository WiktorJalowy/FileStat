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
        std::filesystem::current_path(std::filesystem::temp_directory_path());
        std::filesystem::create_directory(testDirectory);
        std::filesystem::current_path(std::filesystem::temp_directory_path().append(testDirectory));
    }
    ~FileWatcherFixture()
    {
        std::filesystem::remove_all(std::filesystem::temp_directory_path().append(testDirectory));
    }
};

TEST_F(FileWatcherFixture, ShouldNotThrowWhenPathExists)
{
    ASSERT_NO_THROW(FileWatcher(std::filesystem::temp_directory_path()));
}

TEST_F(FileWatcherFixture, ShouldThrowWhenPathDoesNotExist)
{

    ASSERT_THROW(FileWatcher{nonExistingDummyPath}, std::exception);
}

TEST_F(FileWatcherFixture, ShouldReturnZeroFilesZeroLinesZeroEmptyLinesWhenGivenFolderIsEmpty)
{
    FileWatcher fw(std::filesystem::current_path());
    EXPECT_EQ(0, std::get<0>(fw.GetStats()));
    EXPECT_EQ(0, std::get<1>(fw.GetStats()));
    EXPECT_EQ(0, std::get<2>(fw.GetStats()));
}

TEST_F(FileWatcherFixture, ShouldReturnOneFilesZeroLinesZeroEmptyLines)
{
    std::ofstream("asdfsf");
    FileWatcher fw(std::filesystem::current_path());
    EXPECT_EQ(1, std::get<0>(fw.GetStats()));
    EXPECT_EQ(0, std::get<1>(fw.GetStats()));
    EXPECT_EQ(0, std::get<2>(fw.GetStats()));
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

    FileWatcher fw(std::filesystem::current_path());
    EXPECT_EQ(2, std::get<0>(fw.GetStats())); // numOfFiles
    EXPECT_EQ(6, std::get<1>(fw.GetStats())); // numOfNonEmptyLines
    EXPECT_EQ(4, std::get<2>(fw.GetStats())); // numOfEmptyLines
}
