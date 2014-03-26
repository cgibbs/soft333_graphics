#include "MainWindow.h"
#include "ui_MainWindow.h"

static float const PI = 3.14159265359f;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    sliderFocus_(nullptr),
    sliderTransX_(nullptr),
    sliderTransY_(nullptr),
    sliderTransZ_(nullptr),
    renderArea_(nullptr)
{
    ui->setupUi(this);

    // Get references to UI elements.
    renderArea_ = ui->renderArea;
    sliderFocus_ = ui->horizontalSliderFocus;
    sliderTransX_ = ui->horizontalSliderTranslationX;
    sliderTransY_ = ui->horizontalSliderTranslationY;
    sliderTransZ_ = ui->horizontalSliderTranslationZ;
    sliderRotateX_ = ui->horizontalSliderRotateX;
    sliderRotateY_ = ui->horizontalSliderRotateY;
    sliderRotateZ_ = ui->horizontalSliderRotateZ;

    // Set up the signals/slots for the sliders.
    connect(sliderFocus_, &QSlider::valueChanged, this, &MainWindow::updateScene);
    connect(sliderTransX_, &QSlider::valueChanged, this, &MainWindow::updateScene);
    connect(sliderTransY_, &QSlider::valueChanged, this, &MainWindow::updateScene);
    connect(sliderTransZ_, &QSlider::valueChanged, this, &MainWindow::updateScene);
    connect(sliderRotateX_, &QSlider::valueChanged, this, &MainWindow::updateScene);
    connect(sliderRotateY_, &QSlider::valueChanged, this, &MainWindow::updateScene);
    connect(sliderRotateZ_, &QSlider::valueChanged, this, &MainWindow::updateScene);


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

    Matrix rotateModel = Matrix::rotateZ(sliderRotateZ_->value() * (PI / 180.0f));
    rotateModel = Matrix::multiplyMatrix(rotateModel, Matrix::rotateY(sliderRotateY_->value() * (PI / 180.0f)));
    rotateModel = Matrix::multiplyMatrix(rotateModel, Matrix::rotateX(sliderRotateX_->value() * (PI / 180.0f)));



    model = Matrix::multiplyMatrix(model,
                                   Matrix::translate3d(
                                       sliderTransX_->value(),
                                       sliderTransY_->value(),
                                       sliderTransZ_->value()
                                       )
                                   );

    model = Matrix::multiplyMatrix(model, rotateModel);


    renderArea_->setModelMatrix(model);

    // Set the perspective matrix.
    renderArea_->setPerspectiveMatrix(
                Matrix::perspective(sliderFocus_->value())
                );

    // Queue a redraw.
    renderArea_->update();
}
