#include "RenderArea.h"

#include <QPen>
#include <QBrush>
#include <QPainter>

/**********************************************
 *
 *              RENDERAREA
 *
 *********************************************/

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent)
{
    QPalette pal;
    pal.setColor(QPalette::Background, Qt::black);

    this->setBackgroundRole(QPalette::Base);
    this->setPalette(pal);
    this->setAutoFillBackground(true);

    // Set matrices as identity.
    modelMatrix_ = Matrix::identity();
    viewMatrix_ = Matrix::identity();
    perspectiveMatrix_ = Matrix::identity();

    // Initialise the default model.
    std::vector<Vertex> vertices;
    vertices.push_back({-100.0f, -100.0f, 0.0f});
    vertices.push_back({-100.0f, 100.0f, 0.0f});
    vertices.push_back({100.0f, -100.0f, 0.0f});
    vertices.push_back({100.0f, 100.0f, 0.0f});

    std::vector<int> indexes;
    indexes.push_back(0); indexes.push_back(1); indexes.push_back(2);
    indexes.push_back(1); indexes.push_back(2); indexes.push_back(3);

    renderModel_ = Model(vertices, indexes);
}

void RenderArea::setModel(const Model &model)
{
    renderModel_ = model;
}

void RenderArea::setModelMatrix(const Matrix &modelMat)
{
    modelMatrix_ = modelMat;
}

void RenderArea::setViewMatrix(const Matrix &viewMat)
{
    viewMatrix_ = viewMat;
}

void RenderArea::setPerspectiveMatrix(const Matrix &perspectiveMat)
{
    perspectiveMatrix_ = perspectiveMat;
}

void RenderArea::paintEvent(QPaintEvent * /*event*/)
{
    // Iterate through each triangle in the model.
    std::size_t numTriangles = renderModel_.getIndexes().size() / 3;

    // Draw the background.
    QPainter painter(this);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(0, 0, width() -1, height() -1);

    // Build a list of triangles.
    std::vector<Triangle> triangleBuffer;
    triangleBuffer.reserve(numTriangles);

    // Iterate through each triangle inside the model.
    for(std::size_t t = 0; t < numTriangles; t++)
    {
        Triangle triangle;

        // Store the vertices.
        for(size_t i = 0; i < 3; i++)
        {
            std::size_t vertexIndex = renderModel_.getIndexes()[i + t*3];

            // Transform the vertices with the model transform first.
            Vector vert;
            vert.x_ = renderModel_.getVertices()[vertexIndex].x;
            vert.y_ = renderModel_.getVertices()[vertexIndex].y;
            vert.z_ = renderModel_.getVertices()[vertexIndex].z;
            vert.w_ = 1.0f;


            vert = Matrix::multiplyColumnVector(modelMatrix_, vert);

            triangle.vertices[i].x = vert.x_;
            triangle.vertices[i].y = vert.y_;
            triangle.vertices[i].z = vert.z_;
        }

        // Add the triangle.
        triangleBuffer.push_back(triangle);
    }

    // Sort the triangles.
    std::sort(triangleBuffer.begin(), triangleBuffer.end(), [](Triangle const& a, Triangle const& b)
    {
        // Find the furthest vertices for each triangle.
        float t0 = a.vertices[0].z;
        float t1 = b.vertices[0].z;

        for(std::size_t v = 1; v < 3; v++) {
            t0 = std::max(t0, a.vertices[v].z);
            t1 = std::max(t1, b.vertices[v].z);
        }

        return t0 > t1;
    });

    // Draw the triangles.
    for(std::size_t t = 0; t < triangleBuffer.size(); t++)
    {

        // Transform each vertex of the triangle against the remainder of the transform pipeline.
        for(std::size_t v = 0; v < 3; v++)
        {
            Vector vert;
            vert.x_ = triangleBuffer[t].vertices[v].x;
            vert.y_ = triangleBuffer[t].vertices[v].y;
            vert.z_ = triangleBuffer[t].vertices[v].z;
            vert.w_ = 1.0f;

            vert = Matrix::multiplyColumnVector(viewMatrix_, vert);
            vert = Matrix::multiplyColumnVector(perspectiveMatrix_, vert);

            // Perform the perspective transformation.
            vert.x_ = vert.x_ / vert.w_;
            vert.y_ = vert.y_ / vert.w_;
            vert.z_ = vert.z_ / vert.w_;
            vert.w_ = 1.0f;

            triangleBuffer[t].vertices[v].x = vert.x_;
            triangleBuffer[t].vertices[v].y = vert.y_;
            triangleBuffer[t].vertices[v].z = vert.z_;
        }

        drawTriangle(triangleBuffer[t], painter);

    }

    // Iterate through each triangle of the model.
    /*for(std::size_t t = 0; t < numTriangles; t++) {

        // Allocate memory for the triangle.
        std::vector<Vertex> triangle;
        triangle.resize(3);

        // Iterate through each vertex.
        for(size_t i = 0; i < 3; i++) {

            std::size_t index = renderModel_.getIndexes()[i + t*3];

            Vector vert;
            vert.x_ = renderModel_.getVertices()[index].x;
            vert.y_ = renderModel_.getVertices()[index].y;
            vert.z_ = renderModel_.getVertices()[index].z;
            vert.w_ = 1.0f;

            // Transform the vertex.
            vert = Matrix::multiplyColumnVector(modelMatrix_, vert);
            vert = Matrix::multiplyColumnVector(viewMatrix_, vert);
            vert = Matrix::multiplyColumnVector(perspectiveMatrix_, vert);

            // Perform the perspective transformation.
            vert.x_ = vert.x_ / vert.w_;
            vert.y_ = vert.y_ / vert.w_;
            vert.z_ = vert.z_ / vert.w_;
            vert.w_ = 1.0f;

            // Copy the vertex into the triangle vertex array.
            triangle[i].x = vert.x_;
            triangle[i].y = vert.y_;
            triangle[i].z = vert.z_;

        }

        drawTriangle(triangle, painter);


    }*/

}

void RenderArea::drawTriangle(Triangle const& triangle, QPainter& painter)
{
    QPointF const points[3] = {
        QPointF(triangle.vertices[0].x, triangle.vertices[0].y),
        QPointF(triangle.vertices[1].x, triangle.vertices[1].y),
        QPointF(triangle.vertices[2].x, triangle.vertices[2].y)
    };

    painter.save();

    QPen pen;
    pen.setColor(QColor(0, 0, 0));
    pen.setWidth(1);

    QBrush brush;
    brush.setColor(QColor(150,150,150));
    brush.setStyle(Qt::SolidPattern);

    painter.setBrush(brush);
    painter.setPen(pen);

    painter.drawPolygon(points, 3);

    painter.restore();
}

void RenderArea::drawTriangle(const std::vector<Vertex> &triangle, QPainter& painter)
{

    QPointF const points[3] = {
        QPointF(triangle[0].x, triangle[0].y),
        QPointF(triangle[1].x, triangle[1].y),
        QPointF(triangle[2].x, triangle[2].y)
    };

    painter.save();

    QPen pen;
    pen.setColor(QColor(0, 0, 0));
    pen.setWidth(1);

    QBrush brush;
    brush.setColor(QColor(150,150,150));
    brush.setStyle(Qt::SolidPattern);

    painter.setBrush(brush);
    painter.setPen(pen);

    painter.drawPolygon(points, 3);

    painter.restore();


}
