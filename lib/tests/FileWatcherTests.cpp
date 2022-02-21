#include "lib/FileWatcher.hpp"
#include <filesystem>
#include <gtest/gtest.h>

TEST(FileWatcher, ShouldNotThrowWhenPathExists)
{
    ASSERT_NO_THROW(FileWatcher(std::filesystem::temp_directory_path().c_str()));
}
TEST(FileWatcher, ShouldThrowWhenPathDoesNotExist)
{
    ASSERT_THROW(FileWatcher("abc"), std::exception);
}
