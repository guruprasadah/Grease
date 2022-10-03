#ifndef GFX_SHADER_H
#define GFX_SHADER_H

#include <Core/Types.h>

namespace Grease {
    namespace GFX {
        class Shader {
        public:
            static Shader Create(const String& _Name, const String& _Path);
            static Shader& Get(const String& _Name);
        private:    
            U32 VSID = 0, PSID = 0;
            U32 PID;

            static HashMap<String, Shader> ShaderList;
        };
    };
};

#endif