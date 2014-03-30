#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>

static float const PI = 3.14159265359f;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    sliderFocus_(nullptr),
    sliderTransX_(nullptr),
    sliderTransY_(nullptr),
    sliderTransZ_(nullptr),
    sliderScaleX_(nullptr),
    sliderScaleY_(nullptr),
    sliderScaleZ_(nullptr),
    renderArea_(nullptr)
{
    setAttribute(Qt::WA_DeleteOnClose, true);

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
    sliderScaleX_ = ui->horizontalSliderScaleX;
    sliderScaleY_ = ui->horizontalSliderScaleY;
    sliderScaleZ_ = ui->horizontalSliderScaleZ;

    sliderIa_ = ui->horizontalSliderAmbientIntensity;
    sliderKa_ = ui->horizontalSliderAmbientReflect;

    sliderIi_ = ui->horizontalSliderDiffuseIntensity;
    sliderKd_ = ui->horizontalSliderDiffuseReflect;

    sliderLx_ = ui->horizontalSliderLx;
    sliderLy_ = ui->horizontalSliderLy;
    sliderLz_ = ui->horizontalSliderLz;

    // Set up the signals/slots for the sliders.
    connect(sliderFocus_, &QSlider::valueChanged, this, &MainWindow::updateScene);
    connect(sliderTransX_, &QSlider::valueChanged, this, &MainWindow::updateScene);
    connect(sliderTransY_, &QSlider::valueChanged, this, &MainWindow::updateScene);
    connect(sliderTransZ_, &QSlider::valueChanged, this, &MainWindow::updateScene);
    connect(sliderRotateX_, &QSlider::valueChanged, this, &MainWindow::updateScene);
    connect(sliderRotateY_, &QSlider::valueChanged, this, &MainWindow::updateScene);
    connect(sliderRotateZ_, &QSlider::valueChanged, this, &MainWindow::updateScene);
    connect(sliderScaleX_, &QSlider::valueChanged, this, &MainWindow::updateScene);
    connect(sliderScaleY_, &QSlider::valueChanged, this, &MainWindow::updateScene);
    connect(sliderScaleZ_, &QSlider::valueChanged, this, &MainWindow::updateScene);

    connect(sliderIa_, &QSlider::valueChanged, this, &MainWindow::updateScene);
    connect(sliderKa_, &QSlider::valueChanged, this, &MainWindow::updateScene);
    connect(sliderIi_, &QSlider::valueChanged, this, &MainWindow::updateScene);
    connect(sliderKd_, &QSlider::valueChanged, this, &MainWindow::updateScene);
    connect(sliderLx_, &QSlider::valueChanged, this, &MainWindow::updateScene);
    connect(sliderLy_, &QSlider::valueChanged, this, &MainWindow::updateScene);
    connect(sliderLz_, &QSlider::valueChanged, this, &MainWindow::updateScene);

    // Set up actions.
    connect(ui->actionLoad_Model, &QAction::triggered, this, &MainWindow::loadModel);
    connect(ui->actionClose, &QAction::triggered, this, &MainWindow::close);


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

    model = Matrix::multiplyMatrix(model,
                                   Matrix::scale3d(
                                       sliderScaleX_->value(),
                                       sliderScaleY_->value(),
                                       sliderScaleZ_->value()));


    renderArea_->setModelMatrix(model);

    // Set the perspective matrix.
    renderArea_->setPerspectiveMatrix(
                Matrix::perspective(sliderFocus_->value())
                );

    // Set the ambient lighting.
    renderArea_->setAmbientIntensity(
                (float)sliderIa_->value() / 100.0f
                );
    renderArea_->setAmbientReflectivity(
                (float)sliderKa_->value() / 100.0f
                );

    // Set the diffuse lighting.
    renderArea_->setDiffuseIntensity(
                (float)sliderIi_->value() / 100.0f
                );
    renderArea_->setDiffuseReflectivity(
                (float)sliderKd_->value() / 100.0f
                );

    // Set the lighting vector.
    Vector lv(
                (float)sliderLx_->value() / 100.0f,
                (float)sliderLy_->value() / 100.0f,
                (float)sliderLz_->value() / 100.0f,
                0.0f);

    renderArea_->setLightVector(lv);

    // Queue a redraw.
    renderArea_->update();
}

void MainWindow::loadModel()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open Model File");
    if(!filename.isEmpty()) {

        // Load the model file.
        Model m = ModelLoader::loadModel(filename.toStdString());
        renderArea_->setModel(m);
        renderArea_->update();

    }
}
