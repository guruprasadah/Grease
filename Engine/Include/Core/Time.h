#ifndef CORE_TIME_H
#define CORE_TIME_H

#include <Core/Types.h>
#include <Core/Log.h>

#include <chrono>
#include <thread>

namespace Grease {
    namespace Time {
        /** Simple typedef around std::chrono::time_point */
        using Instant = std::chrono::time_point<std::chrono::high_resolution_clock>;
        /** Get current time
          \returns An instant with respect to the system high-resolution clock 
          */
        Instant Now();
        /** Sleep for N milliseconds 
          @param _Interval Interval to sleep for 
          */
        void Sleep(U64 _Interval);
        /** Sleep until an Instant 
          * @param _Instant Instant to sleep till
          */
        void Sleep(Instant _Instant);
        /** Ticker class. For calling a method at regular interval */
        template <typename T>
        class Ticker {
        public:
            Ticker(U64 _Interval, T* _Callback) {
                Log("Creating ticker with interval " + std::to_string(_Interval));
                std::thread([_Interval, _Callback] {
                    while(true) {
                        Instant Clk = Now() + std::chrono::milliseconds(_Interval);
                        _Callback();
                        Sleep(Clk);
                    }
                }).detach();
            }
        };
    };
};

#endif