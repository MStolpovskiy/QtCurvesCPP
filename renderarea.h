#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPainter>
#include <QColor>
#include <QPen>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = nullptr);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    enum ShapeType {Astroid, Cycloid,
                    HuygensCycloid, HypoCycloid,
                    Line, Circle, Ellipse,
                    Fancy, Starfish};

    void SetBackgroundColor(QColor color) { mBackgroundColor = color; repaint(); }
    QColor GetBackgroundColor() const { return mBackgroundColor; }

    void SetShapeColor(QColor color) { mPen.setColor(color); repaint(); }
    QColor GetShapeColor() const { return mPen.color(); }

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
    ShapeType mShape;
    QPen mPen;

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
    QPointF compute_circle(float);
    QPointF compute_ellipse(float);
    QPointF compute_fancy(float);
    QPointF compute_starfish(float);

signals:

};

#endif // RENDERAREA_H
