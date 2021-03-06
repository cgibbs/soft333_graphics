#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSlider>
#include "RenderArea.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    /**
     * @brief updateScene Updates the transformation matrices and queues the RenderArea to be redrawn.
     */
    void updateScene();

    /**
     * @brief loadModel
     */
    void loadModel();

private:
    Ui::MainWindow *ui;

    QSlider *sliderFocus_;

    QSlider *sliderTransX_;
    QSlider *sliderTransY_;
    QSlider *sliderTransZ_;

    QSlider *sliderRotateX_;
    QSlider *sliderRotateY_;
    QSlider *sliderRotateZ_;

    QSlider *sliderScaleX_;
    QSlider *sliderScaleY_;
    QSlider *sliderScaleZ_;

    // Ambient Lighting.
    QSlider *sliderIa_;
    QSlider *sliderKa_;

    // Diffuse Lighting.
    QSlider *sliderIi_;
    QSlider *sliderKd_;

    // Light Vector.
    QSlider *sliderLx_;
    QSlider *sliderLy_;
    QSlider *sliderLz_;

    RenderArea *renderArea_;
};

#endif // MAINWINDOW_H
