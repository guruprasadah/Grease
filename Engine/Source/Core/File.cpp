#include <Core/File.h>
#include <Core/Log.h>

#include <fstream>
#include <sstream>
#include <filesystem>

namespace Grease {
    namespace File {
        String Read(const String& _Path) {
            String Path = ExpandPath(_Path);

            Log("Loading file with path " + _Path);

            std::ifstream f(Path);
            std::stringstream s;
            s << f.rdbuf();

            return s.str();
        }

        String ExpandPath(const String& _Path) {
            String Specifier = _Path.substr(0, _Path.find_last_of("://") - 2);
            if(Specifier == "ASSET") {
                return "Assets\\" + _Path.substr(_Path.find_last_of("://"), _Path.length());
            }
            return _Path;
        }

        Array<String> Iterate(const String& _Path) {
            Array<String> Files;
            std::filesystem::directory_iterator it(ExpandPath(_Path));

            for(auto& Entry : it) {
                Files.push_back(Entry.path().string().substr(0, Entry.path().string().find_first_of("\\") + 1) + Entry.path().string().substr(Entry.path().string().find_first_of("/") + 1, Entry.path().string().length()));
            }

            return Files;
        }
    };
};