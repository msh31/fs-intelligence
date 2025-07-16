#include "filesystem_utils.hpp"

std::vector<std::string> fs_utils::enumerateFolder(REFKNOWNFOLDERID folderId)
{
    std::vector<std::string> documentFiles;

    PWSTR path = NULL; //wchar_t string pointer
    HRESULT hr = SHGetKnownFolderPath(folderId, 0, NULL, &path);

    if (!SUCCEEDED(hr)) {
        std::cerr << "Failed to get folder path. HRESULT: " << hr << "\n";
        return documentFiles;
    }

    try {
        fs::path documentsPath = fs::path(path);

        CoTaskMemFree(path);

        if (!fs::exists(documentsPath) || !fs::is_directory(documentsPath)) {
            throw std::runtime_error("Folder path is invalid or not a directory.");
        }

        for (const auto& entry : fs::directory_iterator(documentsPath)) {
            documentFiles.push_back(entry.path().string());
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error enumerating folder path: " << e.what() << "\n";
    }

    return documentFiles;
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

std::vector<std::string> fs_utils::filterFilesByType(const std::vector<std::string>& files, const std::vector<std::string>& extensions)
{
    std::vector<std::string> filteredFiles;

    for (const auto& file : files) {
        fs::path filePath = file;
        std::string extension = filePath.extension().string();

        std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

        for (const auto& targetExt : extensions) {
            std::string lowerTargetExt = targetExt;
            std::transform(lowerTargetExt.begin(), lowerTargetExt.end(), lowerTargetExt.begin(), ::tolower);

            if (extension == lowerTargetExt) {
                filteredFiles.push_back(file);
                break;
            }
        }
    }

    return filteredFiles;
}

void fs_utils::detectCloudStorage(DocumentsReport& report)
{
    std::string userProfile = GetEnv("USERPROFILE");
    std::string localAppData = GetEnv("LOCALAPPDATA");
    std::string appData = GetEnv("APPDATA");

    std::vector<std::pair<std::string, std::string>> cloudPaths = {
        {"OneDrive", userProfile + "\\OneDrive"},
        {"Google Drive", userProfile + "\\Google Drive"},
        {"Dropbox", localAppData + "\\Dropbox"},
        {"Dropbox", appData + "\\Dropbox"}
    };

    std::uintmax_t totalSize = 0;

    for (const auto& [name, path] : cloudPaths) {
        if (fs::exists(path) && fs::is_directory(path)) {
            if (std::find(report.cloudStorageFound.begin(), report.cloudStorageFound.end(), name) == report.cloudStorageFound.end()) {
                report.cloudStorageFound.push_back(name);

                try {
                    for (const auto& entry : fs::recursive_directory_iterator(path)) {
                        if (entry.is_regular_file()) {
                            totalSize += entry.file_size();
                        }
                    }
                }
                catch (const std::exception&) {  }
            }
        }
    }

    if (totalSize > 1024 * 1024 * 1024) {  // GB
        report.cloudStorageSize = std::to_string(totalSize / (1024 * 1024 * 1024)) + " GB";
    }
    else if (totalSize > 1024 * 1024) {  // MB
        report.cloudStorageSize = std::to_string(totalSize / (1024 * 1024)) + " MB";
    }
    else {
        report.cloudStorageSize = std::to_string(totalSize / 1024) + " KB";
    }
}

fs_utils::DocumentsReport fs_utils::generateDocumentsReport()
{
    std::vector<std::string> valuableExtensions = { ".docx", ".pdf", ".txt", ".xlsx", ".pptx", ".zip" };

    std::vector<std::string> documents = enumerateFolder(FOLDERID_Documents);
    std::vector<std::string> desktop = enumerateFolder(FOLDERID_Desktop);
    std::vector<std::string> downloads = enumerateFolder(FOLDERID_Downloads);

    std::vector<std::string> valuableDocuments = filterFilesByType(documents, valuableExtensions);
    std::vector<std::string> valuableDesktop = filterFilesByType(desktop, valuableExtensions);
    std::vector<std::string> valuableDownloads = filterFilesByType(downloads, valuableExtensions);

    DocumentsReport report;

    report.valuableDesktopCount = valuableDesktop.size();
    report.valuableDownloadsCount = valuableDownloads.size();
    report.valuableDocumentsCount = valuableDocuments.size();

    report.totalValuables = report.valuableDesktopCount + report.valuableDownloadsCount + report.valuableDocumentsCount;

    detectCloudStorage(report);

    return report;
}