#ifndef GALAXY_MODEL_WIDGET_H_INCLUDED
#define GALAXY_MODEL_WIDGET_H_INCLUDED

#include <QWidget>
#include <QPainter>
#include <QList>
#include <QPair>
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
    QList<QPair<QPoint, QRgb>> list;
    int modelNumber;

public:
    explicit GalaxyModelWidget(QWidget* parent = nullptr);
    void paintEvent(QPaintEvent* event) override;
    QPoint rotate(double x, double y, double a);
    void drawEllipticalGalaxy();
    void drawAlmondShapedGalaxy();
    void drawSpiralGalaxy();

    int getModelNumber() const { return modelNumber; }

public slots:
    void nextModel();
    void rotateSpiralGalaxy(int ticks);

private:
    void generateSpiralGalaxy(int arms);
};


#endif // GALAXY_MODEL_WIDGET_H_INCLUDED
