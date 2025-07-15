#include "browser_intel.hpp"

std::vector<std::string> browser_intel::getInstalledBrowsers()
{
    std::vector<std::string> browsers;

    std::string chromePath = "C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe";
    std::string firefoxPath = "C:\\Program Files\\Mozilla Firefox\\firefox.exe";
    std::string edgePath = "C:\\Program Files (x86)\\Microsoft\\Edge\\Application\\msedge.exe";

    if (fs::exists(chromePath)) { browsers.emplace_back("Chrome"); }
    if (fs::exists(firefoxPath)) { browsers.emplace_back("Firefox"); }
    if (fs::exists(edgePath)) { browsers.emplace_back("Edge"); }

    return browsers;
}

std::vector<std::string> browser_intel::getBrowserProfiles(const std::string& browserName)
{
    std::vector<std::string> profiles;
    std::string appdata = this->fsUtils.GetEnv("APPDATA");
    std::string localAppdata = this->fsUtils.GetEnv("LOCALAPPDATA");

    if (browserName == "Firefox") {
        std::string profilesRoot = appdata + "\\Mozilla\\Firefox\\Profiles";

        if (fs::exists(profilesRoot) && fs::is_directory(profilesRoot)) {
            for (const auto& entry : fs::directory_iterator(profilesRoot)) {
                if (fs::is_directory(entry.path())) {
                    profiles.emplace_back(entry.path().string());
                }
            }
        }
    }
    else if (browserName == "Edge") {
        std::string edgeProfile = localAppdata + "\\Microsoft\\Edge\\User Data\\Default";

        if (fs::exists(edgeProfile) && fs::is_directory(edgeProfile)) {
            profiles.emplace_back(edgeProfile);
        }
    }

    return profiles;
}

std::vector<std::string> browser_intel::getBrowserDataFiles(const std::string& profilePath, const std::string& browserName)
{
    std::vector<std::string> dataFiles;

    if (browserName == "Firefox") {
        std::vector<std::string> firefoxFiles = {
            "logins.json",      // encrypted saved passwords
            "key4.db",          // master key for decryption  
            "places.sqlite",    // bookmarks and history
            "cookies.sqlite"    // session cookies
        };

        for (const auto& entry : firefoxFiles) {
            std::string fullPath = profilePath + "\\" + entry;

            if (fs::exists(fullPath))
            {
                dataFiles.emplace_back(fullPath);
            }
        }
    }
    else if (browserName == "Edge") {
        std::vector<std::string> edgeFiles = {
            "Login Data",       // saved passwords (sqlite db)
            "Cookies",
            "Bookmarks",
            "History"
        };

        for (const auto& entry : edgeFiles) {
            std::string fullPath = profilePath + "\\" + entry;
            if (fs::exists(fullPath)) {
                dataFiles.emplace_back(fullPath);
            }
        }
    }

    return dataFiles;
}

browser_intel::BrowserReport browser_intel::generateBrowserReport()
{
    std::vector<std::string> browsers = getInstalledBrowsers();
    BrowserReport report;

    for (const auto& browser : browsers) {
        std::vector<std::string> profiles = getBrowserProfiles(browser);

        for (const auto& profile : profiles) {
            std::vector<std::string> dataFiles = getBrowserDataFiles(profile, browser);
            report.credentialFiles += dataFiles.size();  // Add count to total
        }
    }

    return report;
}