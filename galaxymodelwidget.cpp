#include "galaxymodelwidget.h"


GalaxyModelWidget::GalaxyModelWidget(QWidget* parent) : QWidget(parent)
{
    setFixedSize(SIDE, SIDE);
    rand = QRandomGenerator::system();
    center.setY(SIDE / 2);
    center.setX(SIDE / 2);
    modelNumber = 2;

    QPalette pal;
    //    QPixmap pix;
    //    pix.load(":/res/pic/g1.bmp");
    //    pix = pix.scaled(QSize(SIDE, SIDE), Qt::AspectRatioMode::IgnoreAspectRatio);
    //    pal.setBrush(backgroundRole(), QBrush(pix));


    pal.setColor(QPalette::Background, Qt::black);
    setPalette(pal);

    timer = new QTimer(this);
    //    connect(timer, SIGNAL(timeout()), this, SLOT(repaint()));
    timer->start(50);
    setAutoFillBackground(true);
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
        drawSpiralGalaxy(5);
        break;
    case 3:
    case 4:
    default:
        qDebug() << "wrong number";
    }

    QWidget::paintEvent(event);
}


QPoint GalaxyModelWidget::rotate(double x, double y, double a)
{
    return  QPointF(x * cos(a) + y * sin(a), -x*sin(a) + y*cos(a)).toPoint();
}


void GalaxyModelWidget::drawEllipticalGalaxy()
{
    QPainter paint(this);
    paint.setPen(QColor(qRgb(255, 255, 255)));
    paint.translate(LENGTH, LENGTH); //перемещение начала координат в центр

    std::function<double (double, double)> func = [](double distance, double radius)
    {
        double num = qPow(M_E, -(qPow(distance, 4) / qPow(radius, 2)));
        //        qDebug() << num;
        return num;
    };


    double radius = 70.0 / LENGTH;

    for (int x = -LENGTH; x <= LENGTH; x++)
    {
        for (int y = -LENGTH; y <= LENGTH; y++)
        {
            double distance = qSqrt(qPow(x, 2) + qPow(y, 2)) / LENGTH;
            //            qDebug() << "DISTANCE : " << distance;

            if (rand->generateDouble() > func(distance,  radius))
                continue;
            else
                paint.drawPoint(x, y);
        }
    }
    qDebug() << "GENERATED: Elliptical Galaxy";
}



void GalaxyModelWidget::drawAlmondShapedGalaxy()
{
    QPainter paint(this);
    paint.setPen(QColor(qRgb(255, 255, 255)));
    paint.translate(LENGTH, LENGTH);
    paint.rotate(-45.0);

    std::function<double (double)> func = [](double p)
    {
        double num = qPow(M_E, -qPow(p, 1.2));
        //        qDebug() << num;
        return num;
    };


    double a = 30.0 / LENGTH;
    double b = 140.0 / LENGTH;

    for (int x = -LENGTH; x <= LENGTH; x++)
    {
        for (int y = -LENGTH; y <= LENGTH; y++)
        {
            double fx = (double) x / LENGTH;
            double fy = (double) y / LENGTH;
            double p = qPow(fx, 2) / qPow(a, 2) + qPow(fy, 2) / qPow(b, 2);

            if (rand->generateDouble() > func(p))
                continue;
            else
                paint.drawPoint(x, y);
        }
    }
    qDebug() << "GENERATED: Almond Galaxy";
}



void GalaxyModelWidget::drawSpiralGalaxy(int arms)
{
    QPainter paint(this);
    paint.setPen(QColor(qRgb(255, 255, 255)));
    paint.translate(LENGTH, LENGTH);

    std::function<double (double, double)> func = [](double d, double r)
    {
        d *= 0.15;
        return qExp(-qPow(d, 3) / qPow(r, 2));
    };

    list.clear();

    int h = 10;  //ширина рукава
    int l = 500; //длина рукава

    double b = M_PI * 0.2 * LENGTH;

    double angle = M_PI / arms;
    for (int x = -LENGTH; x <= LENGTH; x++)
    {
        for (int y = -LENGTH; y <= LENGTH; y++)
        {
            double d = qPow(x * x + y * y , 0.5);

            if ((rand->generateDouble() * 2.5) > (func(x * x, l * l) * func(y * y, h * h)))
            {
                continue;
            }
            else
            {
                QPoint point = rotate(x, y, b / d);
                list.push_back(point);
                paint.drawPoint(point);

                for (int i = 0; i < arms; i++)
                {
                    point = rotate(point.x(), point.y(), angle * i);
                    paint.drawPoint(point);
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
    if (modelNumber == 2)
    {
        qDebug() << "TICKS: " << ticks;
        QPainter paint(this);
        paint.setPen(QColor(qRgb(0, 0, 0)));
        paint.translate(LENGTH, LENGTH);

        foreach (QPoint point, list)
        {
            paint.drawPoint(point.x(), point.y());
            paint.setPen(QColor(qRgb(255, 255, 255)));
            point = rotate(point.x(), point.y(), ticks);
            paint.drawPoint(point);
            update();
        }
    }

}
