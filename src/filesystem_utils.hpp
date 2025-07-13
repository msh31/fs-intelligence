#pragma once

#include <windows.h>
#include <string>
#include <vector>
#include <filesystem>
#include <stdexcept> 

namespace fs = std::filesystem;

class fs_utils
{
    public:
        std::vector<std::string> getInstalledBrowsers();
        std::vector<std::string> getBrowserProfiles(const std::string& browserName);

        std::string GetEnv(const char* varName);
};
