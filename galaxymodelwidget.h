#ifndef GALAXYMODELWIDGET_H_INCLUDED
#define GALAXYMODELWIDGET_H_INCLUDED

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QTimer>
#include <QtMath>
#include <QRandomGenerator>
#include <QDebug>

#include <functional>


class GalaxyModelWidget : public QWidget
{
    Q_OBJECT

public:
    const static int SIDE = 500;
    const static int LENGTH = 250;

private:
    QRandomGenerator* rand;
    QTimer* timer;
    QPoint center;
    int modelNumber;

public:
    explicit GalaxyModelWidget(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent*) override;

    void drawEllipticalGalaxy();
    void drawAlmondShapedGalaxy();
    void drawSpiralGalaxy();


    //без перемещения начала координат в центр виджета:
    void ______drawSpiralGalaxy();
    void ______drawEllipticalGalaxy();

public slots:
    void nextModel();
};


#endif // GALAXYMODELWIDGET_H_INCLUDED
