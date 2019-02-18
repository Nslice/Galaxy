#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSlider>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new GalaxyModelWidget(this);
    nextButton = new QPushButton("next", this);
    rotateButton = new QPushButton(">", this);
    connect(nextButton, &QPushButton::clicked, model, &GalaxyModelWidget::nextModel);
//    connect(nextButton, &QPushButton::clicked, model, &GalaxyModelWidget::nextModel);

    QSlider* slider = new QSlider(Qt::Orientation::Horizontal, this);
    slider->setRange(0, 360);
    slider->setValue(360 / 2);
    connect(slider, &QSlider::valueChanged, model, &GalaxyModelWidget::rotateSpiralGalaxy);

    ui->mainVBoxLayout->addWidget(model);
    ui->mainVBoxLayout->addWidget(nextButton);
    ui->mainVBoxLayout->addWidget(rotateButton);
    ui->mainVBoxLayout->addWidget(slider);


    setFixedSize(model->size() + nextButton->size() + rotateButton->size() + slider->size());
    setAutoFillBackground(true);
//    dumpObjectTree();
}


MainWindow::~MainWindow()
{
    delete ui;
}
