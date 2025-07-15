#include "includes.hpp"
#include "filesystem_utils.hpp"
#include "browser_intel.hpp"
#include "software_enum.hpp"
#include "target_profile.hpp"

int main()
{
    //fs_utils fsUtils;
    //browser_intel browserIntel;
    //software_enum softwareEnum;

    //std::vector<std::string> browsers = browserIntel.getInstalledBrowsers();
    //std::vector<std::string> browserProfiles;

    //std::vector<std::string> documents = fsUtils.enumerateFolder(FOLDERID_Documents);
    //std::vector<std::string> desktop = fsUtils.enumerateFolder(FOLDERID_Desktop);
    //std::vector<std::string> downloads = fsUtils.enumerateFolder(FOLDERID_Downloads);

    //std::vector<std::string> valuableExtensions = { ".docx", ".pdf", ".txt", ".xlsx", ".pptx", ".zip" };
    //std::vector<std::string> valuableDocuments = fsUtils.filterFilesByType(documents, valuableExtensions);
    //std::vector<std::string> valuableDesktop = fsUtils.filterFilesByType(desktop, valuableExtensions);
    //std::vector<std::string> valuableDownloads = fsUtils.filterFilesByType(downloads, valuableExtensions);

    //std::vector<std::string> installedSoftware = softwareEnum.getInstalledSoftware();


    //std::cout << "=== BROWSER DETECTION ===" << "\n";

    //if (browsers.empty()) { std::cout << "No browsers detected" << "\n"; }

    //std::cout << "Detected browsers: ";
    //for (const auto& browser : browsers) {
    //    std::cout << browser << " " << "\n";
    //}

    //std::cout << "=== BROWSER PROFILE DETECTION ===" << "\n";

    //for (const auto& browser : browsers) {
    //    std::vector<std::string> profiles = browserIntel.getBrowserProfiles(browser);

    //    std::cout << browser << " profiles found: " << profiles.size() << "\n";

    //    for (const auto& profile : profiles) {
    //        std::cout << "  " << profile << "\n";

    //        std::vector<std::string> dataFiles = browserIntel.getBrowserDataFiles(profile, browser);
    //        std::cout << "    Data files found: " << dataFiles.size() << "\n";

    //        for (const auto& dataFile : dataFiles) {
    //            std::cout << "      " << dataFile << "\n";
    //        }
    //    }
    //}

    //std::cout << "=== DOCUMENT INTELLIGENCE ===" << "\n";

    //std::cout << "Documents: " << documents.size() << " files\n";
    //std::cout << "Desktop: " << desktop.size() << " files\n";
    //std::cout << "Downloads: " << downloads.size() << " files\n";

    //std::cout << "Documents: " << documents.size() << " total, " << valuableDocuments.size() << " valuable\n";
    //std::cout << "Desktop: " << desktop.size() << " total, " << valuableDesktop.size() << " valuable\n";
    //std::cout << "Downloads: " << downloads.size() << " total, " << valuableDownloads.size() << " valuable\n";

    target_profile targetProfile;

    targetProfile.generateAssessment();


    return 0;
}