#include "vertices.hpp"
#include "glm/gtx/transform.hpp"
#define TINYOBJLOADER_IMPLEMENTATION
#include "glm/glm.hpp"
#include "p6/p6.h"
#include "tiny_obj_loader.h"

// return un verteur de vertex
std::vector<glimac::ShapeVertex> tiny_vertice(const std::string inputfile)
{
    // load obj
    // std::string              inputfile = "../assets/fish_color.obj";
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
            // v.normal   = glm::vec3{attrib.normals[3 * index.vertex_index], attrib.normals[3 * index.vertex_index + 1], attrib.normals[3 * index.vertex_index + 2]};
            vertices.push_back(v);
            v.texCoords = glm::vec2{attrib.texcoords[2 * size_t(index.texcoord_index) + 0], attrib.texcoords[2 * size_t(index.texcoord_index) + 1]};
        }
    }
    return vertices;
}

img::Image loadTextureFromMTL(const std::string& mtlFilePath, const std::string& objFilePath)
{
    tinyobj::MaterialFileReader materialReader(mtlFilePath);
    tinyobj::ObjReaderConfig    readerConfig;
    readerConfig.mtl_search_path = mtlFilePath.substr(0, mtlFilePath.find_last_of("/\\") + 1); // Chemin pour la recherche des fichiers MTL

    tinyobj::ObjReader reader;
    if (!reader.ParseFromFile(objFilePath, readerConfig))
    {
        if (!reader.Error().empty())
        {
            std::cerr << "TinyObjReader: " << reader.Error();
        }
        exit(1);
    }

    auto materials = reader.GetMaterials();

    // Parcourir les matériaux et extraire le nom de la texture
    std::string textureFilePath;
    for (const auto& material : materials)
    {
        if (!material.diffuse_texname.empty())
        {
            textureFilePath = readerConfig.mtl_search_path + material.diffuse_texname;
            break;
        }
    }

    // Charger l'image à partir du fichier de texture
    if (!textureFilePath.empty())
    {
    }
    else
    {
        std::cerr << "No texture defined in the MTL file." << std::endl;
        exit(1);
    }
    img::Image textureImage = p6::load_image_buffer(textureFilePath);

    return textureImage;
}
