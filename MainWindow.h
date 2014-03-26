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
    void updateScene();

private:
    Ui::MainWindow *ui;

    QSlider *sliderTransX_;
    QSlider *sliderTransY_;
    QSlider *sliderTransZ_;

    RenderArea *renderArea_;
};

#endif // MAINWINDOW_H
