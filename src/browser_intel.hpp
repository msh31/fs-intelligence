#pragma once

#include "includes.hpp"

class browser_intel
{
    public:
        std::vector<std::string> getInstalledBrowsers();
        std::vector<std::string> getBrowserProfiles(const std::string& browserName);
        std::vector<std::string> getBrowserDataFiles(const std::string& profilePath, const std::string& browserName);
};