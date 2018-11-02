#pragma once

#ifdef WINDOWS
#include <filesystem>
namespace nStdFileSystem = std::filesystem;
#else
#include <experimental/filesystem>
namespace nStdFileSystem = std::experimental::filesystem;
#endif
