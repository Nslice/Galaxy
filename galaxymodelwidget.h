#ifndef GALAXY_MODEL_WIDGET_H_INCLUDED
#define GALAXY_MODEL_WIDGET_H_INCLUDED

#include <QWidget>
#include <QPainter>
#include <QList>
#include <QtMath>
#include <QRandomGenerator>
#include <QDebug>

#include <functional>


class GalaxyModelWidget : public QWidget
{
    Q_OBJECT

public:
    const static int LENGTH = 250;

private:
    QRandomGenerator* rand;
    QList<QPoint> list;
    int modelNumber;

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


#endif // GALAXY_MODEL_WIDGET_H_INCLUDED
