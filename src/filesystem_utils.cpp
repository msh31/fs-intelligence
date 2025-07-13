#include "filesystem_utils.hpp"

std::vector<std::string> fs_utils::getInstalledBrowsers()
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

std::vector<std::string> fs_utils::getBrowserProfiles(const std::string& browserName)
{
    std::vector<std::string> profiles;
    std::string appdata = GetEnv("APPDATA");
    std::string localAppdata = GetEnv("LOCALAPPDATA");

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

std::string fs_utils::GetEnv(const char* varName)
{
    DWORD size = GetEnvironmentVariableA(varName, nullptr, 0);

    if (size == 0) { throw std::runtime_error("Environment variable not found"); }

    std::string value(size, '\0');
    GetEnvironmentVariableA(varName, &value[0], size);
    value.resize(size - 1);

    return value;
}