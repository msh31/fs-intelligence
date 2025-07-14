#pragma once

#include "includes.hpp"

class fs_utils
{
    public:
        std::vector<std::string> enumerateFolder(REFKNOWNFOLDERID folderId);
        std::vector<std::string> filterFilesByType(const std::vector<std::string>& files, const std::vector<std::string>& extensions);

        std::string GetEnv(const char* varName);
};
