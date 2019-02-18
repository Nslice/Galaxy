#ifndef GALAXYMODELWIDGET_H_INCLUDED
#define GALAXYMODELWIDGET_H_INCLUDED

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QTimer>
#include <QList>
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
    QList<QPoint> list;

public:
    explicit GalaxyModelWidget(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent* event) override;

    QPoint rotate(double x, double y, double a);

    void drawEllipticalGalaxy();
    void drawAlmondShapedGalaxy();
    void drawSpiralGalaxy(int arms);

public slots:
    void nextModel();
    void rotateSpiralGalaxy(int ticks);
};


#endif // GALAXYMODELWIDGET_H_INCLUDED
