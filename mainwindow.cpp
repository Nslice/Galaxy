#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new GalaxyModelWidget(this);
    nextButton = new QPushButton("next", this);
    connect(nextButton, &QPushButton::clicked, model, &GalaxyModelWidget::nextModel);
    connect(nextButton, &QPushButton::clicked, this, &MainWindow::blockSlider);

    slider = new QSlider(Qt::Orientation::Horizontal, this);
    slider->setRange(0, 20);
    slider->setValue(0);
    connect(slider, &QSlider::valueChanged, model, &GalaxyModelWidget::rotateSpiralGalaxy);

    QHBoxLayout* hlayout = new QHBoxLayout(this);
    hlayout->setContentsMargins(10, 0, 10, 5);
    hlayout->addWidget(slider);
    hlayout->addWidget(nextButton);

    ui->mainVBoxLayout->setMargin(0);
    ui->mainVBoxLayout->addWidget(model);
    ui->mainVBoxLayout->addLayout(hlayout);

    setFixedWidth(model->width());
    setFixedHeight(model->height() + nextButton->height());
    setAutoFillBackground(true);


    nextButton->setStyleSheet(
                "QPushButton {\n"
                "  background-color: #2E16B1;\n"
                "  color: white; \n"
                "}\n"
                "QPushButton:pressed {\n"
                "  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
                "                    stop: 0 #6C31AC, stop: 1 #3F3CB2);\n"
                "}"
                );
    dumpObjectTree();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::blockSlider()
{
    slider->setDisabled(model->getModelNumber() != 2);
}
