#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <filesystem>
#include <stdexcept> 
#include <shlobj.h>     // For SHGetKnownFolderPath
#include <algorithm>  // For std::transform
#include <cctype>     // For ::tolower

namespace fs = std::filesystem;