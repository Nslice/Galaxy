#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new GalaxyModelWidget(this);
    nextButton = new QPushButton("next", this);
    connect(nextButton, &QPushButton::clicked, model, &GalaxyModelWidget::nextModel);

    ui->mainVBoxLayout->addWidget(model);
    ui->mainVBoxLayout->addWidget(nextButton);



    resize(model->size());
    setAutoFillBackground(true);
    dumpObjectTree();
}


MainWindow::~MainWindow()
{
    delete ui;
}
