#include <Core/Debug.h>
#include <Core/Log.h>

#include <cstdlib>

namespace Grease {
    namespace Debug {
        void Error(const String &_Message) {
            Log(_Message);
            std::exit(3);
        }
    };
};