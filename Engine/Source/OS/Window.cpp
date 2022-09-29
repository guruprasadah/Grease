#include "GLFW/glfw3.h"
#include <OS/Window.h>
#include <Core/Debug.h>

namespace Grease {
    namespace OS {
        Window Window::Create(U16 _Width, U16 _Height, String _Title) {
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            Window w;
            w.GLFWWindowPointer = glfwCreateWindow(_Width, _Height, _Title.c_str(), NULL_POINTER, NULL_POINTER);

            if(w.GLFWWindowPointer == NULL_POINTER) {
                Debug::Error("Window creation failed");
            }

            glfwMakeContextCurrent(w.GLFWWindowPointer);

            return w;
        }

        Boolean Window::Open() {
            return !glfwWindowShouldClose(this->GLFWWindowPointer);
        }

        NULL_TYPE Window::ProcessEvents() {
            glfwPollEvents();
            return NULL_POINTER;
        }

        NULL_TYPE Window::SwapBuffer() {
            glfwSwapBuffers(this->GLFWWindowPointer);
            return NULL_POINTER;
        }
    }
};