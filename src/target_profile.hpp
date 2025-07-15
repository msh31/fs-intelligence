#include "includes.hpp"
#include "browser_intel.hpp"
#include "software_enum.hpp"
#include "filesystem_utils.hpp"

class target_profile
{
    public:
        void generateAssessment();

    private:
        browser_intel browserIntel;
        software_enum softwareEnum;
        fs_utils fsUtils;

        // Helper functions for analysis?
};