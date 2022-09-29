#include <GFX/Shader.h>

#include <Core/Types.h>
#include <Core/Log.h>
#include <Core/File.h>
#include <Core/Debug.h>

#include <glad/glad.h>

#include <fstream>
#include <sstream>

namespace Grease {
    namespace GFX {
        std::unordered_map<String, Shader> Shader::ShaderList;
        
        U32 CreateShader(String _Source, GLenum _Type) {
            U32 SID = glCreateShader(_Type);
            
            const char* SSRC = _Source.c_str();
            
            glShaderSource(SID, 1, &SSRC, NULL_POINTER);
            glCompileShader(SID);

            I32 Success;
            Byte InfoLog[512];
            glGetShaderiv(SID, GL_COMPILE_STATUS, &Success);

            if(!Success) {
                glGetShaderInfoLog(SID, 512, NULL_POINTER, InfoLog);
                Debug::Error("Unable to compile shader, printing log:\n" + String(InfoLog));
            }

            return SID;
        }

        U32 CreateProgram(const U32& _VS, const U32& _PS) {
            U32 PID = glCreateProgram();

            glAttachShader(PID, _VS);
            glAttachShader(PID, _PS);

            glLinkProgram(PID);

            I32 Success;
            Byte InfoLog[512];
            glGetProgramiv(PID, GL_LINK_STATUS, &Success);

            if(!Success) {
                glGetProgramInfoLog(PID, 512, NULL_POINTER, InfoLog);
                Debug::Error("Unable to link program, printing log:\n" + String(InfoLog));
            }

            return PID;
        }
        
        Shader Shader::Create(const String& _Name, const String& _Path) {
            String Source = File::Read(_Path);
            
            Log("Loading shader named " + _Name + " from path " + _Path);

            Shader s;
            
            String Type;
            String Line;

            String VSSource, PSSource;

            std::stringstream sstr;
            sstr << Source;
            while(getline(sstr, Line)) {
                if(Line.find("@Stage") != String::npos) {
                    if(Line.find("Vertex") != String::npos) {
                        Type = "Vertex";
                    } else if(Line.find("Pixel") != String::npos) {
                        Type = "Pixel";
                    }
                } else {
                    if(Type == "Vertex") {
                        VSSource += Line + "\n";
                    } else if(Type == "Pixel") {
                        PSSource += Line + "\n";
                    }
                }
            }

            s.VSID = CreateShader(VSSource, GL_VERTEX_SHADER);
            s.PSID = CreateShader(PSSource, GL_FRAGMENT_SHADER);

            s.PID = CreateProgram(s.VSID, s.PSID);

            ShaderList[_Name] = s;

            return s;
        }
    };
};