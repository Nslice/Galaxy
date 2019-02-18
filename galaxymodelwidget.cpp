#include "galaxymodelwidget.h"


GalaxyModelWidget::GalaxyModelWidget(QWidget* parent) : QWidget(parent)
{
    QSize size(LENGTH * 2, LENGTH * 2);
    setFixedSize(size);
    setAutoFillBackground(true);

    QPalette pal;
    QPixmap pix;
    pix.load(":/res/pic/g1.bmp");
    pix = pix.scaled(size, Qt::AspectRatioMode::IgnoreAspectRatio);
    pal.setBrush(backgroundRole(), QBrush(pix));


//        pal.setColor(QPalette::Background, Qt::black);
    setPalette(pal);

    rand = QRandomGenerator::system();
    modelNumber = 2;

    //    timer = new QTimer(this);
    //    connect(timer, SIGNAL(timeout()), this, SLOT(repaint()));
    //    timer->start(50);
}



void GalaxyModelWidget::paintEvent(QPaintEvent* event)
{
    switch (modelNumber)
    {
    case 0:
        drawEllipticalGalaxy();
        break;
    case 1:
        drawAlmondShapedGalaxy();
        break;
    case 2:
        drawSpiralGalaxy(6);
        break;
    default:
        qDebug() << "wrong number";
    }
    QWidget::paintEvent(event);
}



QPoint GalaxyModelWidget::rotate(double x, double y, double a)
{
    return QPointF(x * cos(a) + y * sin(a), -x * sin(a) + y * cos(a)).toPoint();
}



void GalaxyModelWidget::drawEllipticalGalaxy()
{
    std::function<double (double, double)> func = [](double distance, double radius)
    {
        distance *= 0.15;
        return qExp(-(qPow(distance, 4) / qPow(radius, 2)));
    };

    QPainter painter(this);
    painter.setPen(QColor(qRgb(255, 255, 255)));
    painter.translate(LENGTH, LENGTH); //перемещение начала координат в центр

    int radius = 350;

    for (int x = -LENGTH; x <= LENGTH; x++)
    {
        for (int y = -LENGTH; y <= LENGTH; y++)
        {
            double distance = qSqrt(qPow(x, 2) + qPow(y, 2));
            painter.setPen(QColor(qRgb(255, static_cast<int>(distance * 1.4), 0)));
            if (rand->generateDouble() <= func(distance, radius))
                painter.drawPoint(x, y);
        }
    }
    qDebug() << "GENERATED: Elliptical Galaxy";
}



void GalaxyModelWidget::drawAlmondShapedGalaxy()
{
    std::function<double (double)> func = [](double p)
    {
        return qExp(-qPow(p, 1.2));;
    };

    QPainter painter(this);
    painter.setPen(QColor(qRgb(255, 255, 255)));
    painter.translate(LENGTH, LENGTH);

    int a = 30;
    int b = 120;

    double angle = 2.2 / M_PI ;

    for (int x = -LENGTH; x <= LENGTH; x++)
    {
        for (int y = -LENGTH; y <= LENGTH; y++)
        {
            double p = qPow(x, 2) / qPow(a, 2) + qPow(y, 2) / qPow(b, 2);
            if (rand->generateDouble() <= func(p))
                painter.drawPoint(rotate(x, y, angle));
        }
    }
    qDebug() << "GENERATED: Almond Galaxy";
}



void GalaxyModelWidget::drawSpiralGalaxy(int arms)
{
    std::function<double (double, double)> func = [](double d, double r)
    {
        d *= 0.15;
        return qExp(-qPow(d, 3) / qPow(r, 2));
    };

    QPainter painter(this);
    painter.setPen(QColor(qRgb(255, 255, 255)));
    painter.translate(LENGTH, LENGTH);

    list.clear();

    int h = 10;  //ширина рукава
    int l = 500; //длина рукава

    double b = M_PI * 0.2 * LENGTH;
    double angle = M_PI / arms;

    for (int x = -LENGTH; x <= LENGTH; x++)
    {
        for (int y = -LENGTH; y <= LENGTH; y++)
        {
            double distance = qPow(x * x + y * y , 0.5);
            if ((rand->generateDouble() * 2.5) <= (func(x * x, l * l) * func(y * y, h * h)))
            {
                painter.setPen(QColor(qRgb(static_cast<int>(-distance), 154, 175)));
                QPoint point = rotate(x, y, b / distance);
                list.push_back(point);
                painter.drawPoint(point);
                for (int i = 0; i < arms; i++)
                {
                    point = rotate(point.x(), point.y(), angle * i);
                    painter.drawPoint(point);
                }
            }
        }
    }
    qDebug() << "GENERATED: Spiral Galaxy";
    qDebug() << "List size: " << list.size();
}



void GalaxyModelWidget::nextModel()
{
    modelNumber = (modelNumber + 1) % 3;
    qDebug() << "modelNumber: " << modelNumber;
    qDebug() << "List size: " << list.size();
    update();
}



void GalaxyModelWidget::rotateSpiralGalaxy(int ticks)
{
    qDebug() << "TICKS: " << ticks;
    if (modelNumber == 2)
    {
        double angle = M_PI / 5;
        QPainter paint(this);
        paint.setPen(QColor(qRgb(0, 0, 0)));
        paint.translate(LENGTH, LENGTH);

        double b = M_PI * 0.2 * LENGTH;
        paint.setPen(QColor(qRgb(255, 255, 255)));
        foreach (QPoint p, list)
        {
            double d = qPow(p.x() * p.x() + p.y() * p.y(), 0.5);
            QPoint point = rotate(p.x(), p.y(), b / d);
            point = rotate(point.x(), point.y(), angle + ticks);
            paint.drawPoint(point);
            update();
        }

    }
}
