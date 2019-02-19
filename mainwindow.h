#ifndef MAIN_WINDOW_H_INCLUDED
#define MAIN_WINDOW_H_INCLUDED

#include <QMainWindow>
#include <QPushButton>
#include <QSlider>

#include "galaxymodelwidget.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow* ui;
    GalaxyModelWidget* model;
    QPushButton* nextButton;
    QSlider* slider;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void blockSlider();
};


#endif // MAIN_WINDOW_H_INCLUDED
