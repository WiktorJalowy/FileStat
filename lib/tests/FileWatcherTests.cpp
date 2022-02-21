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
