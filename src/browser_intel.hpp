#pragma once

#include "includes.hpp"
#include "filesystem_utils.hpp"

class browser_intel
{
    public:
        struct BrowserReport {
            //int totalBrowsers;
            //int totalProfiles;
            int credentialFiles = 0;
        };

        BrowserReport generateBrowserReport();

    private:
        fs_utils fsUtils;

        std::vector<std::string> getInstalledBrowsers();
        std::vector<std::string> getBrowserProfiles(const std::string& browserName);
        std::vector<std::string> getBrowserDataFiles(const std::string& profilePath, const std::string& browserName);
};