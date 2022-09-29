#include <Core/Time.h>
#include <chrono>
#include <thread>

namespace Grease {
    namespace Time {
        Instant Now() {
            return std::chrono::high_resolution_clock::now();
        }

        void Sleep(U64 _Interval) {
            Instant i = Now() + std::chrono::milliseconds(_Interval);
            std::this_thread::sleep_until(i);
        }

        void Sleep(Instant _Instant) {
            std::this_thread::sleep_until(_Instant);
        }
    };
};