#ifndef CORE_FILE_H
#define CORE_FILE_H

#include <Core/Types.h>

namespace Grease {
    /** Filesystem functions */
    namespace File {
        /** Read a file with specifier into string
          * @param _Path Desired file to read
          * \returns String with file contents 
          */
        String Read(const String& _Path);
        /** Expand a path with specifier 
          * @param _Path Path to be expanded
          * \returns String with expanded path
          */
        String ExpandPath(const String& _Path);
        /** Iterate through contents of a directory
          * @param _Path Path to desired directory to iterate
          * \returns Array of filename strings. (ONLY filename - Without the path) 
          */
        Array<String> Iterate(const String& _Path);
    };
};

#endif