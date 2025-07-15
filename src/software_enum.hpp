#pragma once

#include "includes.hpp"

class software_enum
{
    public:
        struct SoftwareReport {
            //int totalSoftware;
            std::vector<std::string> threats = {};
            bool hasAntivirus = false;
            bool hasDebugger = false;
        };

        SoftwareReport generateSoftwareReport();

    private:
        bool containsKeyword(const std::string& text, const std::vector<std::string>& keywords);
        bool isAntiVirus(const std::string& softwareName);
        bool isDebugger(const std::string& softwareName);

        std::vector<std::string> getInstalledSoftware();       
};