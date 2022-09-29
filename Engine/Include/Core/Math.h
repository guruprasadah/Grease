#ifndef CORE_MATH_H
#define CORE_MATH_H

#include <glm/glm.hpp>
#include <Core/Types.h>

namespace Grease {
    using FVector2 = glm::tvec2<F32>;
    using FVector3 = glm::tvec3<F32>;
    using FVector4 = glm::tvec4<F32>;

    using DVector2 = glm::tvec2<F64>;
    using DVector3 = glm::tvec3<F64>;
    using DVector4 = glm::tvec4<F64>;

    using IVector2 = glm::tvec2<I64>;
    using IVector3 = glm::tvec3<I64>;
    using IVector4 = glm::tvec4<I64>;

    using UVector2 = glm::tvec2<U64>;
    using UVector3 = glm::tvec3<U64>;
    using UVector4 = glm::tvec4<U64>;

    using BVec2 = glm::tvec2<Byte>;
    using BVec3 = glm::tvec3<Byte>;
    using BVec4 = glm::tvec4<Byte>;

    using FMatrix4 = glm::mat4x4;
    using DMatrix4 = glm::dmat4x4;
};

#endif