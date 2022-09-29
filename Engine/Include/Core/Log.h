#ifndef CORE_LOG_H
#define CORE_LOG_H

#include <Core/Types.h>
#include <Core/Math.h>

#include <mutex>
#include <cstdio>
#include <string>

namespace Grease {
    extern std::mutex __mutex;

    
    inline void Log(const std::string& _Message) {
        __mutex.lock();
        std::printf("\x1b[31;49m[GREASE] \x1b[37;49m%s\n", _Message.c_str());
        __mutex.unlock();
    }


    inline void Log(const double& _Message) {
        __mutex.lock();
        std::printf("\x1b[31;49m[GREASE] \x1b[37;49m%f\n", _Message);
        __mutex.unlock();
    }

    inline void Log(const FVector2& _Message) {
        __mutex.lock();
        std::printf("\x1b[31;49m[GREASE] \x1b[37;49m X: %f Y: %f\n", _Message.x, _Message.y);
        __mutex.unlock();
    }

    inline void Log(const FVector3& _Message) {
        __mutex.lock();
        std::printf("\x1b[31;49m[GREASE] \x1b[37;49m X: %f Y: %f Z: %f\n", _Message.x, _Message.y, _Message.z);
        __mutex.unlock();
    }

    inline void Log(const FVector4& _Message) {
        __mutex.lock();
        std::printf("\x1b[31;49m[GREASE] \x1b[37;49m X: %f Y: %f Z: %f W: %f\n", _Message.x, _Message.y, _Message.z, _Message.w);
        __mutex.unlock();
    }

    inline void Log(const DVector2& _Message) {
        __mutex.lock();
        std::printf("\x1b[31;49m[GREASE] \x1b[37;49m X: %f Y: %f\n", _Message.x, _Message.y);
        __mutex.unlock();
    }

    inline void Log(const DVector3& _Message) {
        __mutex.lock();
        std::printf("\x1b[31;49m[GREASE] \x1b[37;49m X: %f Y: %f Z: %f\n", _Message.x, _Message.y, _Message.z);
        __mutex.unlock();
    }

    inline void Log(const DVector4& _Message) {
        __mutex.lock();
        std::printf("\x1b[31;49m[GREASE] \x1b[37;49m X: %f Y: %f Z: %f W: %f\n", _Message.x, _Message.y, _Message.z, _Message.w);
        __mutex.unlock();
    }

    inline void Log(const IVector2& _Message) {
        __mutex.lock();
        std::printf("\x1b[31;49m[GREASE] \x1b[37;49m X: %lld Y: %lld\n", _Message.x, _Message.y);
        __mutex.unlock();
    }

    inline void Log(const IVector3& _Message) {
        __mutex.lock();
        std::printf("\x1b[31;49m[GREASE] \x1b[37;49m X: %lld Y: %lld Z: %lld\n", _Message.x, _Message.y, _Message.z);
        __mutex.unlock();
    }

    inline void Log(const IVector4& _Message) {
        __mutex.lock();
        std::printf("\x1b[31;49m[GREASE] \x1b[37;49m X: %lld Y: %lld Z: %lld W: %lld\n", _Message.x, _Message.y, _Message.z, _Message.w);
        __mutex.unlock();
    }

    inline void Log(const UVector2& _Message) {
        __mutex.lock();
        std::printf("\x1b[31;49m[GREASE] \x1b[37;49m X: %lld Y: %lld\n", _Message.x, _Message.y);
        __mutex.unlock();
    }

    inline void Log(const UVector3& _Message) {
        __mutex.lock();
        std::printf("\x1b[31;49m[GREASE] \x1b[37;49m X: %lld Y: %lld Z: %lld\n", _Message.x, _Message.y, _Message.z);
        __mutex.unlock();
    }

    inline void Log(const UVector4& _Message) {
        __mutex.lock();
        std::printf("\x1b[31;49m[GREASE] \x1b[37;49m X: %lld Y: %lld Z: %lld W: %lld\n", _Message.x, _Message.y, _Message.z, _Message.w);
        __mutex.unlock();
    }
};

#endif