#ifndef MODEL_H
#define MODEL_H

#include <vector>

struct Vertex {
  float x, y, z;
};

class Model
{
public:
    Model();
    Model(std::vector<Vertex> v, std::vector<int> i);

    std::vector<Vertex> const& getVertices() const;
    std::vector<int> const& getIndexes() const;

private:
    std::vector<Vertex> vertices_;
    std::vector<int>    indexes_;
};

#endif // MODEL_H
