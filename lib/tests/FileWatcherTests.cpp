#include "lib/FileWatcher.hpp"
#include <gtest/gtest.h>

TEST(FileWatcher, ShouldNotThrowWhenPathExists)
{
    ASSERT_NO_THROW(FileWatcher(std::filesystem::temp_directory_path().c_str()));
}

TEST(FileWatcher, ShouldThrowWhenPathDoesNotExist)
{
    const std::string nonExistingDummyPath = "asdfsf";
    ASSERT_THROW(FileWatcher{nonExistingDummyPath}, std::exception);
}

TEST(FileWatcher, ShouldReturnZeroFilesZeroLinesZeroEmptyLinesWhenGivenFolderIsEmpty)
{
    FileWatcher fw(std::filesystem::temp_directory_path().c_str());
    EXPECT_EQ(0, std::get<0>(fw.GetStats()));
    EXPECT_EQ(0, std::get<1>(fw.GetStats()));
    EXPECT_EQ(0, std::get<2>(fw.GetStats()));
}
