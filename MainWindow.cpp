#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    sliderTransX_(nullptr),
    sliderTransY_(nullptr),
    sliderTransZ_(nullptr),
    renderArea_(nullptr)
{
    ui->setupUi(this);

    // Get references to UI elements.
    renderArea_ = ui->renderArea;
    sliderTransX_ = ui->horizontalSliderTranslationX;
    sliderTransY_ = ui->horizontalSliderTranslationY;
    sliderTransZ_ = ui->horizontalSliderTranslationZ;

    // Set up the signals/slots for the sliders.
    connect(sliderTransX_, &QSlider::valueChanged, this, &MainWindow::updateScene);
    connect(sliderTransY_, &QSlider::valueChanged, this, &MainWindow::updateScene);
    connect(sliderTransZ_, &QSlider::valueChanged, this, &MainWindow::updateScene);


    // Setup the render area.
    updateScene();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateScene()
{
    Matrix model = Matrix::identity();
    model = Matrix::multiplyMatrix(model,
                                   Matrix::translate3d(
                                       sliderTransX_->value(),
                                       sliderTransY_->value(),
                                       sliderTransZ_->value()
                                       )
                                   );

    renderArea_->setModelMatrix(model);

    // Queue a redraw.
    renderArea_->update();
}
