#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPainter>
#include <QColor>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = nullptr);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    enum ShapeType {Astroid, Cycloid,
                 HuygensCycloid, HypoCycloid,
                   Line};

    void SetBackgroundColor(QColor color) { mBackgroundColor = color; }
    QColor GetBackgroundColor() const { return mBackgroundColor; }

    void SetShape(ShapeType shape) { mShape = shape; on_shape_changed();}
    ShapeType GetShape() const {return mShape; }

    void SetScale(float scale) { mScale = scale; repaint (); }
    float GetScale() const { return mScale; }

    void SetIntervalLength(float intLength) { mIntervalLength = intLength; repaint();}
    float GetIntervalLength() const { return mIntervalLength; }

    void SetStepCount(int stepCount) { mStepCount = stepCount; repaint(); }
    int GetStepCount() const { return mStepCount; }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QColor mBackgroundColor;
    QColor mShapeColor;
    ShapeType mShape;

    float mIntervalLength;
    float mScale;
    int mStepCount;

private:
    QPointF compute(float); // dispatch function based on mShape type
    void on_shape_changed();
    QPointF compute_astroid(float);
    QPointF compute_cycloid(float);
    QPointF compute_huygens(float);
    QPointF compute_hypo(float);
    QPointF compute_line(float);

signals:

};

#endif // RENDERAREA_H
