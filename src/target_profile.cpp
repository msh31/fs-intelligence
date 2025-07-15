#include "target_profile.hpp"

fs_utils fsUtils;
browser_intel browserIntel;
software_enum softwareEnum;

void target_profile::generateAssessment()
{
    software_enum::SoftwareReport softwareReport = softwareEnum.generateSoftwareReport();
    browser_intel::BrowserReport browserReport = browserIntel.generateBrowserReport();
    fs_utils::DocumentsReport documentsReport = fsUtils.generateDocumentsReport();


    std::cout << "=== SOFTWARE INTELLIGENCE ===\n";
    if (softwareReport.hasAntivirus) { std::cout << "An anti-virus was found on the system: " << "\n\n"; }
    if (softwareReport.hasDebugger) { std::cout << "A debugger was found on the system: " << "\n"; }

    for (const auto& entry : softwareReport.threats) {
        std::cout << entry << "\n";
    }


    std::cout << "\n=== BROWSER DETECTION ===\n";
    std::cout << "credentials found: " << browserReport.credentialFiles << "\n";


    std::cout << "\n=== DOCUMENT INTELLIGENCE ===\n";
    std::cout << "Total valuable documents: " << documentsReport.totalValuables << "\n";
    std::cout << "Documents: " << documentsReport.valuableDocumentsCount << " | Desktop: " << documentsReport.valuableDesktopCount << " | Downloads: " << documentsReport.valuableDownloadsCount << "\n";
}