#ifndef GFX_RENDERER_H
#define GFX_RENDERER_H

#include <glad/glad.h>

#include <OS/Window.h>

namespace Grease {
    namespace GFX {
        /** Main renderer class */
        class Renderer {
        public:
            /** Creates a renderer
            * @param _Window Reference to created window object
            * \returns Newly created renderer */
            static Renderer Create(const Grease::OS::Window& _Window);
            /** Begins new renderer frame */
            NULL_TYPE NewFrame();
        private:
            Renderer();
        };
    }
};

#endif