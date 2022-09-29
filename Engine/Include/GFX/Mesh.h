#ifndef GFX_MESH_H
#define GFX_MESH_H

#include <Core/Types.h>

namespace Grease {
    namespace GFX {
        class Mesh {
        public:
            static Mesh Create(const String& _Path);
        private:
            U32 VertexBuffer = 0, IndexBuffer = 0, VertexArray = 0;
        };
    };
};

#endif