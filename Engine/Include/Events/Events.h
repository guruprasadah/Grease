#ifndef EVENTS_EVENTS_H
#define EVENTS_EVENTS_H

#include <Core/Types.h>

#include <typeinfo>
#include <functional>

namespace Grease {
    namespace Events {
        /** Frame event */
        class OnFrameEvent {};
        /** Tick event */
        class OnTickEvent {};
        /** Hashmap of events to handlers. For internal use */
        extern HashMap<String, Array<std::function<void(void*)>>> EventSubMap;
        /** Subscribe to event
          * @param _Delegate Handler function pointer for event 
          */
        template <typename T>
        void Subscribe(std::function<void(void*)> _Delegate) {
            EventSubMap[typeid(T).name()].push_back(_Delegate);
        }
        /** Brodcast event
          @param _Data Instance of data to be brodcasted 
          */
        template<typename T>
        void Brodcast(T& _Data) {
            for(auto _Delegate : EventSubMap[typeid(T).name()]) {
                _Delegate(&_Data);
            }
        }
    };
};

#endif