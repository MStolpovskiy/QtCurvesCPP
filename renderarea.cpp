#include "renderarea.h"
#include <QtMath>

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    mBackgroundColor(QColor(0, 0, 255)),
    mShape(Astroid)
{
    mPen.setWidth(2);
    mPen.setColor(QColor(255, 255, 255));
    on_shape_changed();
}

QSize RenderArea::minimumSizeHint() const {
    return QSize(1000, 1000);
}

QSize RenderArea::sizeHint() const {
    return QSize(1000, 1000);
}

void RenderArea::on_shape_changed() {
    switch (mShape) {
    case RenderArea::Astroid:
        mScale = 90;
        mIntervalLength = 2 * M_PI;
        mStepCount = 256;
        break;
    case RenderArea::Cycloid:
        mScale = 10;
        mIntervalLength = 4 * M_PI;
        mStepCount = 128;
        break;
    case RenderArea::HuygensCycloid:
        mScale = 10;
        mIntervalLength = 2 * M_PI;
        mStepCount = 256;
        break;
    case RenderArea::HypoCycloid:
        mScale = 40;
        mIntervalLength = 2 * M_PI;
        mStepCount = 256;
        break;
    case RenderArea::Line:
        mScale = 100; // line length in pixels
        mIntervalLength = 1; // not really needed
        mStepCount = 2;
    case RenderArea::Circle:
        mScale = 100;
        mIntervalLength = 2 * M_PI;
        mStepCount = 128;
        break;
    case RenderArea::Ellipse:
        mScale = 75;
        mIntervalLength = 2 * M_PI;
        mStepCount = 128;
        break;
    case RenderArea::Fancy:
        mScale = 10;
        mIntervalLength = 12 * M_PI;
        mStepCount = 512;
        break;
    case RenderArea::Starfish:
        mScale = 25;
        mIntervalLength = 6 * M_PI;
        mStepCount = 256;
        break;
    case RenderArea::Cloud:
    case RenderArea::Star:
        mScale = 10;
        mIntervalLength = 28 * M_PI;
        mStepCount = 256;
        break;
    default:
        break;
    }
}

QPointF RenderArea::compute(float t) {
    switch (mShape) {
    case RenderArea::Astroid:
        return compute_astroid(t);
        break;
    case RenderArea::Cycloid:
        return compute_cycloid(t);
        break;
    case RenderArea::HuygensCycloid:
        return compute_huygens(t);
        break;
    case RenderArea::HypoCycloid:
        return compute_hypo(t);
        break;
    case RenderArea::Line:
        return compute_line(t);
        break;
    case RenderArea::Circle:
        return compute_circle(t);
        break;
    case RenderArea::Ellipse:
        return compute_ellipse(t);
        break;
    case RenderArea::Fancy:
        return compute_fancy(t);
        break;
    case RenderArea::Starfish:
        return compute_starfish(t);
        break;
    case RenderArea::Cloud:
        return compute_cloud(t, -1);
        break;
    case RenderArea::Star:
        return compute_cloud(t, +1);
        break;
    default:
        break;
    }
    return QPoint(0, 0);
}

QPointF RenderArea::compute_astroid(float t) {
    float cos_t = cos(t);
    float sin_t = sin(t);
    float x = 2 * cos_t * cos_t * cos_t;
    float y = 2 * sin_t * sin_t * sin_t;
    return QPointF(x, y);
}

QPointF RenderArea::compute_cycloid(float t) {
    return QPointF(
                1.5 * (1 - cos(t)), // X
                1.5 * (t - sin(t))  // Y
                );
}

QPointF RenderArea::compute_huygens(float t) {
    return QPointF(
                4 * (3 * cos(t) - cos(3 * t)), // X
                4 * (3 * sin(t) - sin(3 * t))  // Y
                );
}

QPointF RenderArea::compute_hypo(float t) {
    return QPointF(
                1.5 * (2 * cos(t) + cos(2 * t)), // X
                1.5 * (2 * sin(t) - sin(2 * t))  // Y
                );
}

QPointF RenderArea::compute_line(float t) {
    return QPointF(
                t, // X
                t  // Y
                );
}

QPointF RenderArea::compute_circle(float t) {
    return QPointF(
                cos(t), // X
                sin(t)  // Y
                );
}

QPointF RenderArea::compute_ellipse(float t) {
    float a = 2., b = 1.1;
    return QPointF(
                a * cos(t), // X
                b * sin(t)  // Y
                );
}

QPointF RenderArea::compute_fancy(float t) {
    float a = 11., b = 6.;
    float x = a * cos(t) - b * cos (a / b * t);
    float y = a * sin(t) - b * sin (a / b * t);
    return QPointF(x, y);
}

QPointF RenderArea::compute_starfish(float t) {
    float R = 5., r = 3., d = 5.;
    float x = (R - r) * cos(t) + d * cos ((R - r) / r * t);
    float y = (R - r) * sin(t) - d * sin ((R - r) / r * t);
    return QPointF(x, y);
}

QPointF RenderArea::compute_cloud(float t, int sign = -1) {
    float a = 14., b = 1.;
    float x = (a + b) * cos(t * b / a) + sign * b * cos ((a + b) / a * t);
    float y = (a + b) * sin(t * b / a) - b * sin ((a + b) / a * t);
    return QPointF(x, y);
}

void RenderArea::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(mBackgroundColor);
    painter.setPen(mPen);

    // drawing area
    painter.drawRect(this->rect());

    QPoint center = this->rect().center();
    float step = mIntervalLength / mStepCount;
    QPoint lastPixel;
    for (float t=0; t<mIntervalLength + step; t+=step) {
        QPointF point = compute(t);
        QPoint pixel;
        pixel.setX(point.x() * mScale + center.x());
        pixel.setY(point.y() * mScale + center.y());
        if (t == 0) {
            lastPixel = pixel;
            continue;
        }
//        painter.drawPoint(pixel);
        QLineF line(pixel, lastPixel);
        painter.drawLine(line);
        lastPixel = pixel;
    }
}
