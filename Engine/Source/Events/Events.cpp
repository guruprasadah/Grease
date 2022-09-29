#include <Events/Events.h>

namespace Grease {
    namespace Events {
        HashMap<String, Array<std::function<void(void*)>>> EventSubMap;
    };
};