#include "Model.h"

#include <iostream>
#include <fstream>

/***************************
 *
 *      MODEL
 *
 ***************************/


Model::Model()
{
}

Model::Model(std::vector<Vertex> const& v, std::vector<int> const& i)
    : vertices_(v), indexes_(i)
{
}

Model& Model::operator = (Model const& m)
{
    vertices_ = m.vertices_;
    indexes_ = m.indexes_;

    return *this;
}

std::vector<Vertex> const& Model::getVertices() const
{
    return vertices_;
}

std::vector<int> const& Model::getIndexes() const
{
    return indexes_;
}

/***************************
 *
 *      MODEL LOADER
 *
 ***************************/

Model ModelLoader::loadModel(const std::string &modelPath)
{
    // Open the file.
    std::ifstream modelFile(modelPath);
    if(!modelFile.is_open()) {
        std::cerr << "Failed to open model: " << modelPath << std::endl;
        return Model();
    }

    std::cout << "BEGIN LOADING MODEL: " << modelPath << std::endl;

    // Get the number of vertices.
    std::size_t vertexCount = 0;
    modelFile >> vertexCount;

    std::cout << "Vertex count = " << vertexCount << std::endl;

    // Iterate through and load each vertex.
    std::vector<Vertex> vertices;

    for(std::size_t v = 0; v < vertexCount; v++) {

        Vertex vert;
        modelFile >> vert.x;
        modelFile >> vert.y;
        modelFile >> vert.z;

        vertices.push_back(vert);

        std::cout << "V: [" << vert.x << ' ' << vert.y << ' ' << vert.z << "]" << std::endl;
    }

    // Get the number of indexes.
    std::size_t indexCount = 0;
    modelFile >> indexCount;

    std::cout << std::endl << "Index count = " << indexCount << std::endl;

    // Iterate through and load the indexes.
    std::vector<int> indexes;

    for(std::size_t i = 0; i < indexCount; i++) {

        // Only supports indexing triangles at this point.
        std::size_t ic = 0;
        std::size_t i0 = 0, i1 = 0, i2 = 0;

        modelFile >> ic;
        modelFile >> i0 >> i1 >> i2;

        std::cout << "I: [" << i0 << ' ' << i1 << ' ' << i2 << ']' << std::endl;

        indexes.push_back(i0);
        indexes.push_back(i1);
        indexes.push_back(i2);
    }

    std::cout << "FINISHED LOADING MODEL: " << modelPath << std::endl;



    return Model(vertices, indexes);
}

