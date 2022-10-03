#include <GFX/Mesh.h>

#include <glad/glad.h>

#include <Core/File.h>
#include <Core/Log.h>
#include <Core/Math.h>

#include <fstream>
#include <cstddef>

namespace Grease {
    namespace GFX {
        struct ModelHeader {
        public:
            U32 Header;
            // IDLength. Not a member because string instantiation from file requires dynamic allocation
            // ID. Previous reason stated above
            U64 VertexCount;
            U64 IndexCount;
        };

        struct Vertex {
        public:
            FVector3 Position;
            FVector3 Normal;
            FVector2 Texcoords;
        };

        HashMap<String, Mesh> Mesh::MeshList;

        Mesh Mesh::Create(const String& _Path) {
            std::ifstream Stream(File::ExpandPath(_Path));

            ModelHeader Header;
            Stream.read(reinterpret_cast<char*>(&Header.Header), sizeof(U32));
            
            U32 IDLength;
            Stream.read(reinterpret_cast<char*>(&IDLength), sizeof(U32));

            Byte ID[IDLength];
            Stream.read(ID, IDLength);

            Stream.read(reinterpret_cast<char*>(&Header.VertexCount), sizeof(U64));
            Stream.read(reinterpret_cast<char*>(&Header.IndexCount), sizeof(U64));

            Array<Vertex> Vertices(Header.VertexCount);
            Stream.read(reinterpret_cast<char*>(Vertices.data()), sizeof(Vertex) * Header.VertexCount);

            Array<U64> Indices(Header.IndexCount);
            Stream.read(reinterpret_cast<char*>(Indices.data()), sizeof(U64) * Header.IndexCount);

            Mesh mesh = Mesh(String(ID));
            
            glGenVertexArrays(1, &mesh.VertexArray);
            glGenBuffers(1, &mesh.VertexBuffer);
            glGenBuffers(1, &mesh.IndexBuffer);

            glBindVertexArray(mesh.VertexArray);

            glBindBuffer(GL_ARRAY_BUFFER, mesh.VertexBuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), Vertices.data(), GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.IndexBuffer);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(U64) * Indices.size(), Indices.data(), GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(FVector3), 0);

            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(FVector3), reinterpret_cast<void*>(offsetof(Vertex, Normal)));

            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(FVector2), reinterpret_cast<void*>(offsetof(Vertex, Texcoords)));

            glBindVertexArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            
            MeshList.insert(std::make_pair(String(ID), mesh));
            
            return mesh;
        }

        Mesh& Mesh::Get(const String& _ID) {
            return MeshList.at(_ID);
        }
    };
};