#include <iostream>
#include "filesystem_utils.hpp"

int main()
{
    fs_utils utils;

    std::vector<std::string> browsers = utils.getInstalledBrowsers();
    std::vector<std::string> browserProfiles;

    std::cout << "=== BROWSER DETECTION ===" << "\n";

    if (browsers.empty()) { std::cout << "No browsers detected" << "\n"; }

    std::cout << "Detected browsers: ";
    for (const auto& browser : browsers) {
        std::cout << browser << " " << "\n";
    }

    std::cout << "=== BROWSER PROFILE DETECTION ===" << "\n";

    for (const auto& browser : browsers) {
        std::vector<std::string> profiles = utils.getBrowserProfiles(browser);

        std::cout << browser << " profiles found: " << profiles.size() << "\n";

        for (const auto& profile : profiles) {
            std::cout << "  " << profile << "\n";
        }
    }

    return 0;
}