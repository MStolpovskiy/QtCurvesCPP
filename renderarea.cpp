#include "renderarea.h"
#include <QtMath>

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    mBackgroundColor(QColor(0, 0, 255)),
    mShapeColor(QColor(255, 255, 255)),
    mShape(Astroid)
{
    on_shape_changed();
}

QSize RenderArea::minimumSizeHint() const {
    return QSize(100, 100);
}

QSize RenderArea::sizeHint() const {
    return QSize(400, 200);
}

void RenderArea::on_shape_changed() {
    switch (mShape) {
    case RenderArea::Astroid:
        mScale = 40;
        mIntervalLength = 2 * M_PI;
        mStepCount = 256;
        break;
    case RenderArea::Cycloid:
        break;
    case RenderArea::HuygensCycloid:
        break;
    case RenderArea::HypoCycloid:
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
    float cos_t = cos(t);
    float sin_t = sin(t);
    float x = 2 * cos_t * cos_t * cos_t;
    float y = 3 * sin_t * sin_t * sin_t;
    return QPointF(x, y);
}

QPointF RenderArea::compute_huygens(float t) {
    float cos_t = cos(t);
    float sin_t = sin(t);
    float x = 3 * cos_t * cos_t * cos_t;
    float y = 2 * sin_t * sin_t * sin_t;
    return QPointF(x, y);
}

QPointF RenderArea::compute_hypo(float t) {
    float cos_t = cos(t);
    float sin_t = sin(t);
    float x = 2 * cos_t * cos_t * cos_t;
    float y = 4 * sin_t * sin_t * sin_t;
    return QPointF(x, y);
}

void RenderArea::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(mBackgroundColor);
    painter.setPen(mShapeColor);

    // drawing area
    painter.drawRect(this->rect());

    QPoint center = this->rect().center();
    float step = mIntervalLength / mStepCount;
    for (float t=0; t<mIntervalLength; t+=step) {
        QPointF point = compute(t);
        QPoint pixel;
        pixel.setX(point.x() * mScale + center.x());
        pixel.setY(point.y() * mScale + center.y());
        painter.drawPoint(pixel);
    }
}
