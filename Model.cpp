#include "Model.h"

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
}

std::vector<Vertex> const& Model::getVertices() const
{
    return vertices_;
}

std::vector<int> const& Model::getIndexes() const
{
    return indexes_;
}
