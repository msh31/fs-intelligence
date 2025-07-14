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

    // TODO: loop through files
    // extract extension from each file
    // cvheck if extension matches any in the extensions list

    return filteredFiles;
}