#include "galaxymodelwidget.h"


GalaxyModelWidget::GalaxyModelWidget(QWidget* parent) : QWidget(parent)
{
    setFixedSize(SIDE, SIDE);
    rand = QRandomGenerator::system();
    center.setY(SIDE / 2);
    center.setX(SIDE / 2);
    modelNumber = 2;

    QPalette pal;
    QPixmap pix;
    pix.load(":/res/pic/g1.bmp");
    pix = pix.scaled(QSize(SIDE, SIDE), Qt::AspectRatioMode::IgnoreAspectRatio);
    pal.setBrush(backgroundRole(), QBrush(pix));


    //    pal.setColor(QPalette::Background, Qt::black);
    setPalette(pal);

    timer = new QTimer(this);
    //    connect(timer, SIGNAL(timeout()), this, SLOT(repaint()));
    timer->start(50);
    setAutoFillBackground(true);
}



void GalaxyModelWidget::paintEvent(QPaintEvent*)
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
        drawSpiralGalaxy();
        break;
    case 3:
    case 4:
    default:
        qDebug() << "wrong number";
    }

    //    ______drawEllipticalGalaxy();
    //    ______drawSpiralGalaxy();
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



void GalaxyModelWidget::drawSpiralGalaxy()
{
    QPainter paint(this);
    paint.setPen(QColor(qRgb(255, 255, 255)));
    paint.translate(LENGTH, LENGTH);

    std::function<double (double, double)> func = [](double d, double r)
    {
        double num = qPow(M_E, -qPow(d, 5) / qPow(r, 2));
        //        qDebug() << num
        return num;
    };


    double h = 30.0 / LENGTH;
    double len = 80.0 / LENGTH;

    for (int x = -LENGTH; x <= LENGTH; x++)
    {
        for (int y = -LENGTH; y <= LENGTH; y++)
        {
            double fx = (double) x / LENGTH;
            double fy = (double) y / LENGTH;

            double g = func(qPow(fx, 2), qPow(len, 2)) *
                    func(qPow(fy, 2), qPow(h, 2));

            if (rand->generateDouble() > g)
                continue;
            else
                paint.drawPoint(x, y);
        }
    }
    qDebug() << "GENERATED: Spiral Galaxy";
}





void GalaxyModelWidget::______drawSpiralGalaxy()
{
    QPainter paint(this);
    paint.setPen(QColor(qRgb(255, 255, 255)));
    //    paint.translate(width() / 2, height() / 2);

    std::function<double (double, double)> func = [](double d, double r)
    {
        double num = qPow(M_E, -qPow(d, 5) / qPow(r, 2)); //M_E = 2.71
        //        qDebug() << num
        return num;
    };

    double h = 30.0;
    double len = 80.0;
    qDebug() << " center: " << center;

    for (int x = 0; x < width(); x++)
    {
        for (int y = 0; y < height(); y++)
        {
            double g = func(qPow(x - center.x(), 2), qPow(len, 2));
            g *= func(qPow(y - center.y(), 2), qPow(h, 2));

            //            qDebug() << "G = " << g;
            if (rand->bounded(500) > g)
                continue;
            else
                paint.drawPoint(x, y);
        }
    }

    qDebug() << "GENERATED: Spiral Galaxy";

}



void GalaxyModelWidget::______drawEllipticalGalaxy()
{
    QImage background(size(), QImage::Format_ARGB32_Premultiplied);
    QRgb rgb = qRgb(255, 255, 255);

    std::function<double (double, double)> func = [](double distance, double radius)
    {
        double num = qPow(M_E, -(qPow(distance, 4) / qPow(radius, 2)));

        //        qDebug() << num;
        return num;
    };


    double radius = 0.07;

    qDebug() << rand->generateDouble();
    for (int x = 0; x < width(); x++)
    {
        for (int y = 0; y < height(); y++)
        {

            double distance = (qSqrt(qPow(x - center.x(), 2) + qPow(y - center.y(), 2)));
            distance /= 500.0;
            //            qDebug() << "DIST : " << distance;

            if (rand->generateDouble() > func(distance,  radius))
                continue;
            else
                background.setPixel(x, y, rgb);
        }
    }

    qDebug() << "GENERATED: Elliptical Galaxy";

    QPainter paint(this);
    paint.drawImage(0, 0, background);
}



void GalaxyModelWidget::nextModel()
{
    modelNumber = (modelNumber + 1) % 3;
    qDebug() << "modelNumber :" << modelNumber;
    QPainter paint(this);
    paint.eraseRect(0, 0, SIDE, SIDE);
//    paintEvent(nullptr);
}
