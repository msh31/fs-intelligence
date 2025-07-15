#include "software_enum.hpp"

std::vector<std::string> software_enum::getInstalledSoftware()
{
    std::vector<std::string> softwareList;

    HKEY hkey = HKEY_LOCAL_MACHINE;
    HKEY uninstallKey;

    char buffer[512];
    DWORD dataSize = sizeof(buffer);

    const std::string& subKey = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall";

    if (RegOpenKeyExA(hkey, subKey.c_str(), 0, KEY_READ, &uninstallKey) == ERROR_SUCCESS)
    {
        DWORD index = 0;
        char keyName[256];
        DWORD keyNameSize = sizeof(keyName);

        while (RegEnumKeyExA(uninstallKey, index, keyName, &keyNameSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
        {
            HKEY appKey;
            if (RegOpenKeyExA(uninstallKey, keyName, 0, KEY_READ, &appKey) == ERROR_SUCCESS)
            {
                char displayName[512];
                DWORD size = sizeof(displayName);
                DWORD type = 0;

                if (RegQueryValueExA(appKey, "DisplayName", NULL, &type, (LPBYTE)displayName, &size) == ERROR_SUCCESS)
                {
                    if (type == REG_SZ) { softwareList.emplace_back(displayName); }
                }

                RegCloseKey(appKey);
            }

            index++;
            keyNameSize = sizeof(keyName);
        }

        RegCloseKey(uninstallKey);
    } 

    return softwareList;
}

bool software_enum::isDebugger(const std::string& softwareName)
{
    std::string lowerName = softwareName;
    std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

    static const std::vector<std::string> debuggerKeywords = {
        "dbg", "debug", "debugger", "ida"
    };

    return containsKeyword(lowerName, debuggerKeywords);
}

bool software_enum::isAntiVirus(const std::string& softwareName)
{
    std::string lowerName = softwareName;
    std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

    static const std::vector<std::string> antiVirusNames = {
        "mcafee", "bitdefender", "norton", "avg", "avast", "kaspersky", "malwarebytes"
    };

    return containsKeyword(lowerName, antiVirusNames);
}

bool software_enum::containsKeyword(const std::string& text, const std::vector<std::string>& keywords)
{
    for (const auto& keyword : keywords) {
        if (text.find(keyword) != std::string::npos) {
            return true;
        }
    }
    return false;
}

software_enum::SoftwareReport software_enum::generateSoftwareReport()
{
    SoftwareReport report;

    std::vector<std::string> software = getInstalledSoftware();
    std::vector<std::string> detectedThreats;

    for (const auto& app : software)
    {
        if (isAntiVirus(app)) {
            report.hasAntivirus = true;
            report.threats.push_back(app);
        }
        if (isDebugger(app)) {
            report.hasDebugger = true;
            report.threats.push_back(app);
        }
    }

    return report;
}