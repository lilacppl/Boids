#include "vertices.hpp"
#include "glm/gtx/transform.hpp"
#define TINYOBJLOADER_IMPLEMENTATION
#include "glm/glm.hpp"
#include "tiny_obj_loader.h"

std::vector<glimac::ShapeVertex> tiny_vertice()
{
    // load obj
    std::string              inputfile = "../assets/fish_color.obj";
    tinyobj::ObjReaderConfig reader_config;
    reader_config.mtl_search_path = "../assets"; // Path to material files

    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(inputfile, reader_config))
    {
        if (!reader.Error().empty())
        {
            std::cerr << "TinyObjReader: " << reader.Error();
        }
        exit(1);
    }

    if (!reader.Warning().empty())
    {
        std::cout << "TinyObjReader: " << reader.Warning();
    }
    auto& attrib    = reader.GetAttrib();
    auto& shapes    = reader.GetShapes();
    auto& materials = reader.GetMaterials();

    std::vector<glimac::ShapeVertex> vertices;
    for (const auto& shape : shapes)
    {
        for (const auto& index : shape.mesh.indices)
        {
            glimac::ShapeVertex v;
            v.position = glm::vec3{attrib.vertices[3 * index.vertex_index], attrib.vertices[3 * index.vertex_index + 1], attrib.vertices[3 * index.vertex_index + 2]};
            v.normal   = glm::vec3{attrib.normals[3 * index.vertex_index], attrib.normals[3 * index.vertex_index + 1], attrib.normals[3 * index.vertex_index + 2]};
            vertices.push_back(v);
            v.texCoords = glm::vec2{attrib.texcoords[2 * size_t(index.texcoord_index) + 0], attrib.texcoords[2 * size_t(index.texcoord_index) + 1]};
        }
    }
    return vertices;
}
