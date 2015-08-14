#ifndef VERSIONDEFS_H
#define VERSIONDEFS_H

// This is a centralized location to store all version information. Make sure
// to update this file before making a new tag or a new release.
//
// NOTE:
// This file defines the version data but it SHOULD NOT be used to access this
// data. To prevent unnecessary recompilations of huge amount of files
// everytime the version changes, all information should be accessed
// using the class defined in 'version.h' file.
//
// This file should only by included by following files:
// - version.cpp
// - windows.rc

// Info used by version.cpp
#define VERSION_STRING "1.0"

// Info used by windows.rc
#define FILEVERSION_DEF 1,0,0,0
#define PRODUCTVERSION_DEF 1,0,0,0
#define FILEVERSION_STR_DEF "1.0.0.0"
#define PRODUCTVERSION_STR_DEF "1.0.0.0"
#define LEGALCOPYRIGHT_DEF "Zalewa 2015"

#endif
