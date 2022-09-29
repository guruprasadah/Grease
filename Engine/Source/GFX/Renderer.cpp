#include <GFX/Renderer.h>
#include <GFX/Shader.h>

#include <Core/Debug.h>
#include <Core/File.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Grease {
    namespace GFX {
        Renderer Renderer::Create(const Grease::OS::Window &Window) {
            if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
                Debug::Error("Renderer creation failed.");
            }
            
            Renderer r;

            return r;
        }

        NULL_TYPE Renderer::NewFrame() {
            glClearColor(1, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            return NULL_POINTER;
        }

        Renderer::Renderer() {
            for(auto File : File::Iterate("ASSET://Shaders")) {
                Shader::Create(File.substr(0, File.find_last_of(".")), File);
            }
        }
    };
};