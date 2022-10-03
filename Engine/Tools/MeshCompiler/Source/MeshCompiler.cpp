#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <tomlplusplus.h>

#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <vector>
#include <array>
#include <cinttypes>
#include <unordered_map>
#include <fstream>
#include <cstring>

using namespace std::string_view_literals;

struct Vertex {
public:
    std::array<float, 3> Position;
    std::array<float, 3> Normal;
    std::array<float, 2> Texcoords;

    bool operator == (const Vertex& other) const {
        return this->Position == other.Position && this->Normal == other.Normal && this->Texcoords == other.Texcoords;
    }
};

struct ModelHeader {
    std::uint32_t Header;

    std::uint64_t VertexCount;
    std::uint64_t IndexCount;
};

namespace std {
    template<class T, size_t N> 
    struct hash<std::array<T, N>> {
    auto operator() (const std::array<T, N>& key) const {
        std::hash<T> hasher;
        size_t result = 0;
        for(size_t i = 0; i < N; ++i) {
        result = result * 31 + hasher(key[i]); // ??
    }
    return result;
        }
    };

    template <> struct hash<Vertex> {
        size_t operator () (Vertex const& vertex) const {
            return ((hash<std::array<float, 3>>()(vertex.Position) ^
                   (hash<std::array<float, 3>>()(vertex.Normal) << 1)) >> 1) ^
                   (hash<std::array<float, 2>>()(vertex.Texcoords) << 1);
        }
    };
};

int main(int argc, char* argv[]) {
    if(argc != 3) {
        std::cout << "Incorrect number of arguments, only one is required. Specify ONLY directory name, then output directory name.\n";
        std::exit(10);
    }

    for(auto f : std::filesystem::recursive_directory_iterator(argv[1])) {
        if(!f.is_directory()) {
            std::string path = f.path().string();
            std::string dir = path.substr(0, path.find_last_of("\\"));
            if(path.substr(path.find_last_of('.'), path.length()) == ".toml") {
                auto Cfg = toml::parse_file(path);

                std::string_view ID = Cfg["Mesh"]["ID"].value_or(""sv);
                if(ID == ""sv) {
                    std::cout << "Mesh must have an ID!\n";
                    std::exit(11);
                }
                std::cout << "Mesh ID is " << ID << "... Working...\n";

                std::string_view ModelPath = Cfg["Mesh"]["Model"].value_or(""sv);
                if(ModelPath == ""sv) {
                    std::cout << "Mesh must have a model associated with it!\n";
                    std::exit(12);
                }
                std::cout << "Model path is " << dir + static_cast<std::string>(ModelPath) << "... Working...\n";

                tinyobj::attrib_t Attrib;
                std::vector<tinyobj::shape_t> Shapes;
                std::vector<tinyobj::material_t> Materials;
                std::string warn, err;

                if(!tinyobj::LoadObj(&Attrib, &Shapes, &Materials, &warn, &err, std::string(dir + "\\" + static_cast<std::string>(ModelPath)).c_str())) {
                    std::cout << warn << " " << err << "\n";
                    std::exit(13);
                }

                std::unordered_map<Vertex, std::uint64_t> UniqueVertices;
                
                std::vector<Vertex> Vertices;
                std::vector<std::uint64_t> Indices;

                for(const auto& Shape : Shapes) {
                    for(const auto& Index : Shape.mesh.indices) {
                        Vertex vertex{};
                        
                        vertex.Position[0] = Attrib.vertices[3 * Index.vertex_index + 0];
                        vertex.Position[1] = Attrib.vertices[3 * Index.vertex_index + 1];
                        vertex.Position[2] = Attrib.vertices[3 * Index.vertex_index + 2];

                        vertex.Normal[0] = Attrib.normals[3 * Index.normal_index + 0];
                        vertex.Normal[1] = Attrib.normals[3 * Index.normal_index + 1];
                        vertex.Normal[2] = Attrib.normals[3 * Index.normal_index + 2];

                        vertex.Texcoords[0] = Attrib.texcoords[2 * Index.texcoord_index + 0];
                        vertex.Texcoords[1] = Attrib.texcoords[2 * Index.texcoord_index + 1];

                        if(UniqueVertices.count(vertex) == 0) {
                            UniqueVertices[vertex] = Vertices.size();
                            Vertices.push_back(vertex);
                        }

                        Indices.push_back(UniqueVertices[vertex]);
                    }
                }

                ModelHeader Header;
                Header.Header = 0xDEADBEEF;
                Header.VertexCount = Vertices.size();
                Header.IndexCount = Indices.size();

                std::ofstream Stream(argv[2] + std::string("\\") + static_cast<std::string>(ID) + ".asset");
                //std::cout << argv[2] + static_cast<std::string>(ID) + ".asset" << std::endl;

                Stream.write(reinterpret_cast<char*>(&Header.Header), sizeof(std::uint32_t));

                char IDStr[ID.length()];
                for(int i = 0; i <= ID.length(); i++) {
                    IDStr[i] = ID[i];
                }

                std::uint32_t Length = ID.length();
                Stream.write(reinterpret_cast<char*>(&Length), sizeof(std::uint32_t));
                Stream.write(IDStr, Length);

                Stream.write(reinterpret_cast<char*>(&Header.VertexCount), sizeof(std::uint64_t));
                Stream.write(reinterpret_cast<char*>(&Header.IndexCount), sizeof(std::uint64_t));

                for(auto v : Vertices) {
                    Stream.write(reinterpret_cast<char*>(v.Position.data()), sizeof(float) * 3);
                    Stream.write(reinterpret_cast<char*>(v.Normal.data()), sizeof(float) * 3);
                    Stream.write(reinterpret_cast<char*>(v.Texcoords.data()), sizeof(float) * 2);
                }

                for(auto i : Indices) {
                    Stream.write(reinterpret_cast<char*>(&i), sizeof(std::uint64_t));
                }
            }
        }
    }
}