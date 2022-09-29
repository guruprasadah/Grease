#ifndef CORE_TYPES_H
#define CORE_TYPES_H

#include <cinttypes>
#include <cstddef>
#include <string>
#include <vector>
#include <unordered_map>

namespace Grease {
    using U8 = std::uint8_t;
    using U16 = std::uint16_t;
    using U32 = std::uint32_t;
    using U64 = std::uint64_t;

    using I8 = std::int8_t;
    using I16 = std::int16_t;
    using I32 = std::int32_t;
    using I64 = std::int64_t;

    using F32 = float;
    using F64 = double;

    using Boolean = bool;

    using Byte = char;

    using String = std::string;

    template <typename Type>
    using Array = std::vector<Type>;

    template <typename Key, typename Value>
    using HashMap = std::unordered_map<Key, Value>;

    constexpr auto NULL_POINTER = nullptr;
    using NULL_TYPE = std::nullptr_t;
}

#endif