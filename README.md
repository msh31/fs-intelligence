# 📁 File System Intelligence - Educational Malware Sample

**Part of the [Malware Analysis Learning Course](https://github.com/msh31/malware-analysis) - Challenge 1B**

Educational demonstration of Windows file system reconnaissance and data discovery techniques used by advanced malware for target assessment and attack planning.

## ⚠️ Educational Purpose Only

This code demonstrates file system intelligence gathering techniques for cybersecurity education in controlled environments.

## 🎯 Learning Objectives

This project teaches advanced malware file system reconnaissance techniques:

### **Browser Data Discovery**
- **Chrome/Edge profile enumeration** - Login Data, cookies, bookmarks location mapping
- **Firefox profile discovery** - logins.json, key4.db, browsing data identification  
- **Session intelligence** - Active browser sessions and saved credential detection

### **Document Intelligence**
- **User directory enumeration** - Desktop, Documents, Downloads exploration
- **File type targeting** - Potetional high-value document discovery (.docx, .pdf, .xlsx, credentials)
- **Cloud storage detection** - OneDrive, Dropbox, Google Drive folder identification
- **Recent file analysis** - Windows Recent folder enumeration

### **Software Intelligence**
- **Registry-based software enumeration** - Installed programs via registry analysis
- **Advanced security software detection** - AV/EDR identification beyond process lists
- **Development tools discovery** - IDEs, databases, administrative tools
- **Attack surface mapping** - Potential exploitation targets and lateral movement tools

## 🔧 Techniques Implemented

### **File System APIs**
- `std::filesystem::exists()` - Modern C++20 file existence checking
- `std::filesystem::directory_iterator` - Directory traversal and enumeration
- `std::filesystem::is_directory()` - Directory validation and filtering
- `GetEnvironmentVariableA()` - Environment variable retrieval (%APPDATA%, %LOCALAPPDATA%)
- Browser profile discovery - Chrome/Edge/Firefox installation and data location mapping
- SQLite database detection - Browser credential and session data identification

### **Why These Techniques?**
Real malware uses these exact methods because:
- **Browser credentials** provide account access and financial data
- **Document enumeration** identifies valuable intellectual property
- **Software intelligence** reveals attack surface and security posture
- **File system mapping** enables targeted data exfiltration

## 🛠️ Compilation & Usage

### **Requirements**
- **Platform:** Windows 10/11
- **Compiler:** Visual Studio 2022 or MinGW-w64
- **Dependencies:** Windows API (shell32.lib, advapi32.lib)

### **Build Instructions**

**Visual Studio 2022:**
```bash
# Open solution file
start fs-intelligence.sln

# Build in Release mode for analysis
Build → Configuration Manager → Release → Build Solution
```

### **Safe Execution**
```bash
# Run in isolated VM only
./fs-intelligence.exe

# Output saved to fs_intel.txt
```

## 📊 Sample Output

```
=== FILE SYSTEM INTELLIGENCE ===
Browser Profiles Found: 2 (Chrome, Firefox)
Stored Passwords: 23 entries detected
Financial Sites: 3 banking bookmarks found
Document Analysis: 47 business documents discovered
Cloud Storage: OneDrive synchronized (2.3GB)

=== SOFTWARE INTELLIGENCE ===
Installed Programs: 127 detected
Security Software: Windows Defender, Malwarebytes  
Development Tools: Visual Studio 2022, Git
Administrative Tools: PuTTY, Remote Desktop

=== ENHANCED TARGET ANALYSIS ===
Target Classification: HIGH-VALUE BUSINESS USER
Primary Threats: Financial credentials, business documents
Recommended Action: CREDENTIAL_HARVESTING + DOCUMENT_STAGING
Security Posture: MODERATE (consumer-grade protection)
Exfiltration Priority: Browser passwords, recent documents
```

## 🔬 Malware Analysis Value

### **Real-World Applications**
This technique pattern appears in:
- **APT reconnaissance** - Advanced persistent threat intelligence gathering
- **Ransomware preparation** - File enumeration before encryption targeting
- **Banking trojans** - Credential store discovery and financial data mapping
- **Data theft malware** - Document location mapping for exfiltration

### **Blue Team Learning**
- **File system monitoring** for reconnaissance pattern detection
- **Browser security** understanding credential storage risks
- **Document protection** strategies for high-value data
- **Software inventory** security posture assessment

## 📖 References & Further Reading

- **[MITRE ATT&CK: File and Directory Discovery](https://attack.mitre.org/techniques/T1083/)**
- **[MITRE ATT&CK: Browser Bookmark Discovery](https://attack.mitre.org/techniques/T1217/)**
- **[MITRE ATT&CK: Software Discovery](https://attack.mitre.org/techniques/T1518/)**
- **[Windows File System API Reference](https://docs.microsoft.com/en-us/windows/win32/fileio/)**

---

**🎓 Educational Note:** This project demonstrates Phase 2 malware reconnaissance techniques used by advanced threat actors. Understanding file system intelligence gathering is essential for developing effective data protection and monitoring systems.