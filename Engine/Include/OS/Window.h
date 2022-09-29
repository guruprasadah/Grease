#ifndef OS_WINDOW_H
#define OS_WINDOW_H

#include <Core/Types.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Grease {
    namespace OS {
        /** Window abstraction class 
        */
        class Window {
        public:
            /**
             * Creates a window
             * @param _Width Desired width for window
             * @param _Height Desired height for window
             * @param _Title Desired title for window
             * \returns Newly created window
            */
            static Window Create(U16 _Width, U16 _Height, String _Title);
            /** Pointer to GLFW window. For internal use 
            */
            GLFWwindow* GLFWWindowPointer;
            /** Get window status
              * \returns Whether window is open or not 
              */
            Boolean Open();
            /** Process events
              * \returns Null, not useful for anything 
              */
            NULL_TYPE ProcessEvents();
            /** Swap window buffers 
              */
            NULL_TYPE SwapBuffer();
        };
    };
};

#endif