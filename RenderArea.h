#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>

#include "Matrix.h"
#include "Vector.h"
#include "Model.h"

struct Triangle {
    Vertex vertices[3];
};

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = 0);

public:

    /**
     * @brief setModel
     * @param model
     */
    void setModel(Model const& model);

    /**
     * @brief setModelMatrix
     * @param modelMat
     */
    void setModelMatrix(Matrix const& modelMat);

    /**
     * @brief setViewMatrix
     * @param viewMat
     */
    void setViewMatrix(Matrix const& viewMat);

    /**
     * @brief setPerspectiveMatrix
     * @param perspectiveMat
     */
    void setPerspectiveMatrix(Matrix const& perspectiveMat);

private:
    void paintEvent(QPaintEvent *event) override;

    /**
     * @brief drawTriangle Render a single triangle to the screen.
     * @param triangle Vertex array containing the vertices of the triangle in screen space.
     */
    void drawTriangle(std::vector<Vertex> const& triangle, QPainter& painter);

    /**
     * @brief drawTriangle
     * @param triangle
     * @param painter
     */
    void drawTriangle(Triangle const& triangle, QPainter& painter);

private:

    // Transformation matrices.
    Matrix modelMatrix_;
    Matrix viewMatrix_;
    Matrix perspectiveMatrix_;

    // Model to render.
    Model renderModel_;
};

#endif // RENDERAREA_H
