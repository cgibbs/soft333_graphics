#include "RenderArea.h"

#include <QPen>
#include <QBrush>
#include <QPainter>

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

    std::cout << "RenderArea::paintEvent(): " << std::endl;


    // Draw the background.
    QPainter painter(this);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(0, 0, width() -1, height() -1);

    // Iterate through each triangle of the model.
    for(std::size_t t = 0; t < numTriangles; t++) {

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


    }

}

void RenderArea::drawTriangle(const std::vector<Vertex> &triangle, QPainter& painter)
{
    std::cout << triangle[0].x << ' ' << triangle[0].y << std::endl;
    std::cout << triangle[1].x << ' ' << triangle[1].y << std::endl;
    std::cout << triangle[2].x << ' ' << triangle[2].y << std::endl;

    QPointF const points[3] = {
        QPointF(triangle[0].x, triangle[0].y),
        QPointF(triangle[1].x, triangle[1].y),
        QPointF(triangle[2].x, triangle[2].y)
    };

    painter.save();

    QPen pen;
    pen.setColor(QColor(200, 50, 50));
    pen.setWidth(2);

    QBrush brush;
    brush.setColor(QColor(150,150,150));
    brush.setStyle(Qt::SolidPattern);

    painter.setBrush(brush);
    painter.setPen(pen);

    painter.drawPolygon(points, 3);

    painter.restore();


}
