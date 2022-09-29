#ifndef GFX_SHADER_H
#define GFX_SHADER_H

#include <Core/Types.h>

#include <unordered_map>

namespace Grease {
    namespace GFX {
        class Shader {
        public:
            static Shader Create(const String& _Name, const String& _Path);
        private:    
            U32 VSID = 0, PSID = 0;
            U32 PID;

            static std::unordered_map<String, Shader> ShaderList;
        };
    };
};

#endif