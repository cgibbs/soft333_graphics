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

    /**
     * @brief setLightVector
     * @param lv
     */
    void setLightVector(Vector const& lv);

    void setAmbientIntensity(float Ia);
    void setAmbientReflectivity(float Ka);

    void setDiffuseIntensity(float Ii);
    void setDiffuseReflectivity(float Kd);

    void setGlossiness(int n);
    void setSpecularReflectivity(float Ks);

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
    void drawTriangle(Triangle const& triangle, QPainter& painter, QColor const& colour);

private:

    // Transformation matrices.
    Matrix modelMatrix_;
    Matrix viewMatrix_;
    Matrix perspectiveMatrix_;

    // Model to render.
    Model renderModel_;

    // Light source.
    Vector L_; // Vector representing direction of light rays.

    // Diffuse Lighting
    float  Ii_; //Intensity of the light source.
    float  Kd_; //Light reflectivity of the surface.

    // Ambient Lighting.
    float Ia_; // Intensity of the ambient light.
    float Ka_; // Ambient light reflectivity.

    // Specular lighting
    float Ks_;  // Specular coefficient.
    int glossiness_; // Glossiness. Large values give a more mirror like shine.
};

#endif // RENDERAREA_H
